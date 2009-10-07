#! /usr/bin/env python
# -*- Mode: Python; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
import os
import sys
import struct
import time
import gzip
import bz2
import numpy as np
import matplotlib.colors
import matplotlib.pyplot as plt
from optparse import OptionParser

row_length = 24

def show(opts, infile):
    line = infile.read(24)
    while line:
        n1, n2, e1, e2 = struct.unpack('iidd', line)
        line = infile.read(24)
        print n1, n2, e1, e2

def histogram(opts, infile):
    global row_length
    read = 0
    skip = 0
    if opts.read:
        read = int ( opts.read )
    if opts.skip:
        skip = int ( opts.skip )
    
    infile.seek(24*skip)
    data = np.zeros( (read), dtype=float )
    bytes_to_read = 2*row_length
    for i in range(0, read, 2):
        line = infile.read(bytes_to_read)
        n1, n2, e1, e2, m1, m2, f1, f2 = struct.unpack('iiddiidd', line)
        #print n1, n2, e1, e2
        data[i] = e1
        data[i+1] = f1
    n,bins,patches = plt.hist(data, 50, normed=1, facecolor='g', alpha=0.75)
    plt.show()

def grid(opts, infile):
    global row_length
    read, skip = 0, 0
    emin, emax = -1.0, 3.0
    bins = 200
    if opts.read:
        read = int( opts.read )
    else:
        read = sys.maxint
    if opts.skip:
        skip = int( opts.skip )
    if opts.bins:
        bins = int( opts.bins )
    bin_width = (emax-emin)/bins
    infile.seek(24*skip)
    data = np.ones( (bins,bins), dtype=np.uint32)
    start_time = time.time()
    bytes_to_read = 2*row_length
    line = infile.read(bytes_to_read)
    while len(line) == bytes_to_read and read > 0:
        read -= 2
        n1, n2, e1, e2, m1, m2, f1, f2 = struct.unpack('iiddiidd', line)
        ei1 = (e1-emin)/bin_width
        ei2 = (e2-emin)/bin_width
        if ei1 >= 0 and ei1 < bins and ei2 >= 0 and ei2 < bins:
            data[ei1,ei2] += 1
        ei1 = (f1-emin)/bin_width
        ei2 = (f2-emin)/bin_width
        if ei1 >= 0 and ei1 < bins and ei2 >= 0 and ei2 < bins:
            data[ei1,ei2] += 1
        line = infile.read(bytes_to_read)
    print "finished reading after %.2f seconds" % (time.time() - start_time)
    # set all fields to one to allow for logarithmic plot
    #data[data==0] =1 
    x = np.linspace(emin, emax, bins+1)
    X,Y = np.meshgrid(x,x)
    start_time = time.time()
    #plt.pcolor(X, Y, data, norm=matplotlib.colors.LogNorm())
    # matshow is around 10x faster for 200bins and does not scale O(N^2)
    # thus plotting at 500 bins takes nearly the same amount of time as 200 bins
    plt.matshow(data, norm=matplotlib.colors.LogNorm(), origin='lower', extent=(emin, emax, emin, emax))
    print "finished plotting after %.2f seconds" % (time.time() - start_time)
    plt.colorbar()
    plt.xlabel("Energy from")
    plt.ylabel("Energy to")
    plt.show()

def timecorr(opts, infile):
    read = 0
    mean_data = []
    var_data = []
    num_combine = 10000
    struct_str = num_combine*'d'
    combine_range = range(num_combine)
    num_combine = float(num_combine)
    infile.seek(8, os.SEEK_CUR)
    previous_E = struct.unpack('d', infile.read(8))
    previous_E = previous_E[0]
    infile.seek(16, os.SEEK_CUR)
    eof_reached = False
    while True:
        line = ""
        for i in combine_range:
            tmp = infile.read(8)
            if not tmp:
                eof_reached = True
                break
            line+=tmp
            infile.seek(16, os.SEEK_CUR)
            read+=1
        if eof_reached:
            break;
        E = struct.unpack(struct_str, line)
        meanAcc = 0
        varAcc = 0
        for e in E:
            tmp = previous_E-e
            meanAcc += tmp
            varAcc  += tmp*tmp
            previous_E = e
        mean = meanAcc / num_combine
        mean_data.append(mean)
        var_data.append(varAcc/num_combine - mean*mean)
        if read > 100000000:
            break
    #print mean_data
    plt.plot(mean_data)
    #plt.plot(var_data)
    plt.show()
    pass

def main(argv):
    usage = "usage: %prog [options] files"
    opts = OptionParser(usage=usage)
    opts.add_option('--read', '-r', help="Number of rows to read", type="int")
    opts.add_option('--skip', '-s', help="Number of rows to skip", type="int")
    opts.add_option('--bins', '-b', help="Number of bins", type="int")
 
    options,arguments = opts.parse_args()

    command = 'show'
    filename = None
    if len(arguments) == 2:
        command,filename = arguments


    infile = None
    if filename[-2:] == 'gz':
        infile = gzip.open(filename, "rb")
    elif filename[-3:] == 'bz2':
        infile = bz2.open(filename, "rb")
    else:
        infile = open(filename, "rb")

    globals()[command](options,infile)
    

if __name__ == "__main__":
    main(sys.argv[1:])
