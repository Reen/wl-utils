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
    read_max = sys.maxint
    num_combine = 1
    if opts.read:
        read_max = int( opts.read )
    if opts.combine:
        num_combine = opts.combine
    read = 0
    energy1_data = np.zeros( (read_max), dtype=float )
    energy2_data = np.zeros( (read_max), dtype=float )
    struct_str = num_combine*'dd'
    combine_range = range(num_combine)
    num_combine = float(num_combine)
    infile.seek(8, os.SEEK_CUR)
    eof_reached = False
    if num_combine == 1:
        while read < read_max:
            tmp = infile.read(16)
            if not tmp:
                eof_reached = True
                break
            infile.seek(8, os.SEEK_CUR)
            if eof_reached:
                break;
            E1,E2 = struct.unpack(struct_str, tmp)
            energy1_data[read] = E1
            energy2_data[read] = E2
            read+=1
            if read > 100000000:
                break
    else:
        return
    
    plt.subplot(221)
    plt.plot(energy1_data)
    plt.subplot(222)
    plt.hist(energy1_data, orientation='horizontal', bins=100, range=(-1.0,3.0), log=True)
    plt.subplot(223)
    plt.plot(energy2_data)
    plt.subplot(224)
    plt.hist(energy2_data, orientation='horizontal', bins=100, range=(-1.0,3.0), log=True)
    
    plt.show()
    pass

def showmat(opts, infile):
    data = infile.read(48)
    min_particles, max_particls, n_particles, min_energy, max_energy, energy_bin_width, n_energy, volume = struct.unpack("IIIdddId",data)
    data = infile.read(16)
    outer_cols, outer_rows, inner_cols, inner_rows = struct.unpack("IIII",data)
    print min_particles, max_particls, n_particles, min_energy, max_energy, energy_bin_width, n_energy, volume
    print outer_cols, outer_rows, inner_cols, inner_rows
    data = infile.read(inner_cols*inner_rows*8)
    arr = np.fromstring(data, dtype=float)
    arr[arr==0] = min(arr[arr!=0])/10.0
    plt.matshow(np.reshape(arr, [inner_cols,inner_rows]), norm=matplotlib.colors.LogNorm(), origin='lower', extent=(min_energy, max_energy, min_energy, max_energy))
    plt.colorbar()
    plt.xlabel("Energy from")
    plt.ylabel("Energy to")
    plt.show()

def main(argv):
    usage = "usage: %prog [options] files"
    opts = OptionParser(usage=usage)
    opts.add_option('--read', '-r', help="Number of rows to read", type="int")
    opts.add_option('--skip', '-s', help="Number of rows to skip", type="int")
    opts.add_option('--bins', '-b', help="Number of bins", type="int")
    opts.add_option('--combine', '-c', help="Number of values to combine to one value", type="int")
 
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
