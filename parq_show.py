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
    data = infile.read(12)
    version, filetype, vstrlen = struct.unpack("=III", data)
    if version != 1:
        raise Exception("Unknown parq matrix file version.")
    if filetype == 1:
        filetype = 'integer'
    elif filetype == 2:
        filetype = 'double'
    else:
        raise Exception("Unknown file type.")
    if vstrlen > 0:
        githead = infile.read(vstrlen)
    else:
        githead = ""
    data = infile.read(48)
    min_particles, max_particles, n_particles, min_energy, max_energy, energy_bin_width, n_energy, volume = struct.unpack("=IIIdddId",data)
    data = infile.read(16)
    outer_cols, outer_rows, inner_cols, inner_rows = struct.unpack("IIII",data)
    data = {
        "version"       : version,
        "filetype"      : filetype,
        "githead"       : githead,
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
File: Version: ${version}  Type: ${filetype}
Towhee: ${githead}
Size: ${outer_cols}*${inner_cols} X ${outer_rows}*${inner_rows}
System:
  Particles: $min_particles - $max_particles | $n_particles
  Energy   : $min_energy - $max_energy | $n_energy | $energy_bin_width
  Volume   : $volume""")
        print templ.safe_substitute(data)
    return data

def showmat(opts, infile, filename):
    settings = mat_get_header(infile)
    inner_cols = settings["inner_cols"]
    inner_rows = settings["inner_rows"]
    entitysize = 8
    if settings["filetype"] == "integer":
        entitysize = 4
    if(opts.submatrix):
        off_x,off_y = opts.submatrix.split(',')
        subm = 2*int(off_x)+int(off_y)
        infile.seek(subm*inner_cols*inner_rows*entitysize,os.SEEK_CUR)
    data = infile.read(inner_cols*inner_rows*entitysize)
    if settings["filetype"] == "integer":
        arr = np.fromstring(data, dtype=np.int32)
    else:
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
    ii,ij = np.nonzero(arr)
    for k in xrange(0,ii.size):
        ei = ii[k]
        ej = ij[k]
        if arr[ei,ej] != 0:
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
    dt = np.float64
    es = 8
    mmtype = "real"
    if settings["filetype"] == "integer":
        dt = np.int32
        es = 4
        mmtype = settings["filetype"]
    for i in xrange(0,outer_cols):
        for j in xrange(max(i-1,0),min(i+2,outer_rows)):
            data = infile.read(inner_cols*inner_rows*es)
            arr = np.fromstring(data, dtype=dt)
            arr = np.reshape(arr, [inner_cols, inner_rows])
            count += to_sparse(file_str_3, file_str_4, arr, inner_rows, inner_cols, i, j)
            if i == j:
                for ei in xrange(0,inner_rows):
                    arr[ei,ei] -= 1
            count_mat += to_sparse(file_str_1, file_str_2, arr, inner_rows, inner_cols, i, j)
            prog.increment_amount()
            print prog, '\r',
            sys.stdout.flush()
    print "\n"
    filename = filename.rsplit('.')[0]
    out1 = open("%s-mat.mtx" % (filename), "w")
    out2 = open("%s-mat-t.mtx" % (filename), "w")
    out3 = open("%s-eig.mtx" % (filename), "w")
    out4 = open("%s-eig-t.mtx" % (filename), "w")
    work = [{"out":out1, "fs":file_str_1, "count":count_mat}, {"out":out2, "fs":file_str_2, "count":count_mat}, {"out":out3, "fs":file_str_3, "count":count}, {"out":out4, "fs":file_str_4, "count":count}]
    for cur in work:
        print "creating file %s" % (cur["out"].name)
        cur["out"].write("%%%%MatrixMarket matrix coordinate %s general\n" % (mmtype))
        cur["out"].write("%d %d %d\n" % (inner_cols*outer_cols, inner_rows*outer_rows, cur["count"]))
        cur["out"].write(cur["fs"].getvalue())


def main(argv):
    usage = "usage: %prog [options] files"
    opts = OptionParser(usage=usage)
    opts.add_option('--pdf', '', help="Create a PDF document instead of showing the graph.", action="store_true")
    opts.add_option('--submatrix', '', help="Submatrix to show. Default 0,0. ");
    options,arguments = opts.parse_args()

    command = 'show'
    filename = None
    if len(arguments) == 2:
        command,filename = arguments


    infile = open(filename, "rb")
    gziphead = ('\x1f', '\x8b', '\x08')
    bziphead = ('\x42', '\x5A', '\x68')
    test = struct.unpack('ccc', infile.read(3))
    infile.close()
    if test == gziphead:
        infile = gzip.open(filename, "rb")
    elif test == bziphead:
        infile = bz2.open(filename, "rb")
    else:
        infile = open(filename, "rb")

    globals()[command](options,infile, filename)
    

if __name__ == "__main__":
    main(sys.argv[1:])
# vim: set ts=4 sw=4 tw=0 expandtab :
