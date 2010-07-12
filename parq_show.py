#! /usr/bin/env python
# -*- Mode: Python; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
import os
import re
import sys
import struct
import time
import gzip
import bz2
import numpy as np
import matplotlib
import matplotlib.colors
import matplotlib.pyplot as plt
from optparse import OptionParser

row_length = 24

def mat_get_header(infile, do_print = True):
    data = infile.read(48)
    min_particles, max_particles, n_particles, min_energy, max_energy, energy_bin_width, n_energy, volume = struct.unpack("IIIdddId",data)
    data = infile.read(16)
    outer_cols, outer_rows, inner_cols, inner_rows = struct.unpack("IIII",data)
    data = {
        "min_particles" : min_particles,
        "max_particles" : max_particles,
        "n_particles"   : n_particles,
        "min_energy"    : min_energy,
        "max_energy"    : max_energy,
        "energy_bin_width" : energy_bin_width,
        "n_energy"      : n_energy,
        "volume"        : volume,
        "outer_cols"    : outer_cols,
        "outer_rows"    : outer_rows,
        "inner_cols"    : inner_cols,
        "inner_rows"    : inner_rows
    }
    if do_print:
        from string import Template
        templ = Template("""Matrix Informationen:
Size: ${outer_cols}*${inner_cols} X ${outer_rows}*${inner_rows}
System:
  Particles: $min_particles - $max_particles | $n_particles
  Energy   : $min_energy - $max_energy | $n_energy | $energy_bin_width
  Volume   : $volume""")
        print templ.safe_substitute(data)
    return data

def show(opts, infile, filename):
    line = infile.read(24)
    while line:
        n1, n2, e1, e2 = struct.unpack('iidd', line)
        line = infile.read(24)
        print n1, n2, e1, e2

def histogram(opts, infile, filename):
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

def grid(opts, infile, filename):
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

def timecorr(opts, infile, filename):
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

def showmat(opts, infile, filename):
    settings = mat_get_header(infile)
    outer_cols = settings["outer_cols"]
    outer_rows = settings["outer_rows"]
    inner_cols = settings["inner_cols"]
    inner_rows = settings["inner_rows"]
    if(opts.submatrix):
        off_x,off_y = opts.submatrix.split(',')
        subm = 2*int(off_x)+int(off_y)
        infile.seek(subm*inner_cols*inner_rows*8,os.SEEK_CUR)
    data = infile.read(inner_cols*inner_rows*8)
    arr = np.fromstring(data, dtype=np.float64)
    min_arr = arr[arr!=0]
    if(len(min_arr) > 0):
        arr[arr==0] = min(min_arr)/10.0
    if(opts.pdf):
        matplotlib.rcParams['font.family'] = "serif"
        matplotlib.rcParams['font.serif'] = "Latin Modern Roman"
        matplotlib.rcParams['figure.figsize'] = 10,7
    arr = np.reshape(arr, [inner_cols,inner_rows])
    plt.matshow(arr, norm=matplotlib.colors.LogNorm(), origin='lower', extent=(settings["min_energy"], settings["max_energy"], settings["min_energy"], settings["max_energy"]))
    plt.colorbar()
    plt.xlabel("Energy from")
    plt.ylabel("Energy to")
    plt.title(filename)
    if(opts.pdf):
        plt.savefig(re.sub(r"\/", "_", filename)+".pdf", format="pdf", dpi=300, papertype="A4")
    else:
        plt.show()


def to_sparse(file_str1, file_str2, arr, inner_rows, inner_cols, i, j):
    count = 0
    for ei in range(0,inner_rows):
        for ej in range(0, inner_cols):
            if(arr[ei,ej] != 0):
                i1 = str(j*inner_rows+ej+1) # +1 for 1 based indices
                i2 = str(i*inner_cols+ei+1) # +1 for 1 based indices
                val = "%.12g" % (arr[ei,ej])
                file_str1.write("%s %s %s\n" %(i1, i2, val))
                file_str2.write("%s %s %s\n" %(i2, i1, val))
                count+=1
    return count

def convertmat(opts, infile, filename):
    from cStringIO import StringIO
    from progress_bar import ProgressBar
    file_str_1 = StringIO()
    file_str_2 = StringIO()
    file_str_3 = StringIO()
    file_str_4 = StringIO()
    settings = mat_get_header(infile)
    outer_cols = settings["outer_cols"]
    outer_rows = settings["outer_rows"]
    inner_cols = settings["inner_cols"]
    inner_rows = settings["inner_rows"]
    count = 0
    count_mat = 0
    prog = ProgressBar(0, outer_cols*3-2, 77, mode='fixed', char='#')
    for i in range(0,outer_cols):
        for j in range(max(i-1,0),min(i+2,outer_rows)):
            data = infile.read(inner_cols*inner_rows*8)
            arr = np.fromstring(data, dtype=float)
            arr = np.reshape(arr, [inner_cols, inner_rows])
            count += to_sparse(file_str_3, file_str_4, arr, inner_rows, inner_cols, i, j)
            if i == j:
                for ei in range(0,inner_rows):
                    arr[ei,ei] -= 1
            count_mat += to_sparse(file_str_1, file_str_2, arr, inner_rows, inner_cols, i, j)
            prog.increment_amount()
            print prog, '\r',
            sys.stdout.flush()
    print "\n"
    filename = filename.rsplit('.')[0]
    out1 = open("%s-mat.sparse" % (filename), "w")
    out2 = open("%s-mat-t.sparse" % (filename), "w")
    out3 = open("%s-eig.sparse" % (filename), "w")
    out4 = open("%s-eig-t.sparse" % (filename), "w")
    work = [{"out":out1, "fs":file_str_1, "count":count_mat}, {"out":out2, "fs":file_str_2, "count":count_mat}, {"out":out3, "fs":file_str_3, "count":count}, {"out":out4, "fs":file_str_4, "count":count}]
    for cur in work:
        print "creating file %s" % (cur["out"].filename)
        cur["out"].write("%%MatrixMarket matrix coordinate real general\n")
        cur["out"].write("%d %d %d\n" % (inner_cols*outer_cols, inner_rows*outer_rows, cur["count"]))
        cur["out"].write(cur["fs"].getvalue())


def main(argv):
    usage = "usage: %prog [options] files"
    opts = OptionParser(usage=usage)
    opts.add_option('--read', '-r', help="Number of rows to read", type="int")
    opts.add_option('--skip', '-s', help="Number of rows to skip", type="int")
    opts.add_option('--bins', '-b', help="Number of bins", type="int")
    opts.add_option('--combine', '-c', help="Number of values to combine to one value", type="int")
    opts.add_option('--pdf', '', help="Create a PDF document instead of showing the graph.", action="store_true")
    opts.add_option('--submatrix', '', help="Submatrix to show. Default 0,0. ");
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

    globals()[command](options,infile, filename)
    

if __name__ == "__main__":
    main(sys.argv[1:])
