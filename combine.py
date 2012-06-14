#! /usr/bin/env python
"""
combine. py - A tool to calculate mean and variance of different data files.

How it works:

    File1:                File2:
    |   x    y    z|      |   x    y    z|

    becomes:
    error.dat:
    |   x    y    z_mean  z_var  z_min  z_max|

Limitations:
    - data files have to contain data marked up in columns
    - the columns must have a fixed width which may not vary between the
      different files, but is allowed to vary between the different columns
    - the data inside the columns has to be right aligned

Todo:
    - make it possible to work with left-aligned data by allowing the user to
      specify the column widths
    - make it possible to work with comma separated values
"""

import os
import sys
import re
import gzip
import bz2
from optparse import OptionParser

class Ddict(dict):
    def __init__(self, default=None):
        self.default = default

    def __getitem__(self, key):
        if not self.has_key(key):
            self[key] = self.default()
        return dict.__getitem__(self, key)

def add(x,y): return x+y

"""
compensated variance function from wikipedia
http://en.wikipedia.org/wiki/Algorithms_for_calculating_variance
"""
def compensated_variance(data):
    n = 0
    sum1 = 0
    for x in data:
        n = n + 1
        sum1 = sum1 + x
    mean = sum1/n
 
    sum2 = 0
    sum3 = 0
    for x in data:
        sum2 = sum2 + (x - mean)**2
        sum3 = sum3 + (x - mean)
    variance = (sum2 - sum3**2/n)/(n - 1)
    return ( mean,variance,n )

def main(argv):
    usage = "usage: %prog [options] files"
    opts = OptionParser(usage=usage)
    opts.add_option('--columns', '-c', help="Number of columns to use as key for combination, default is number of columns minus one.", type="int")
    opts.add_option('--data', '-d', help="Column number that should be combined, default is last.", type="int")
    opts.add_option('--out', '-o', help="Name of the output file, default is error.dat", type="string")
    opts.add_option('--required', '-r', help="Number of datapoints required for calculation of mean and variance, default is 2.", type="int")
    options,arguments = opts.parse_args()

    if len(arguments) < 2:
        opts.error("Please specify at least two files.")
        sys.exit()

    # defaults
    columns = -1
    data_col = None
    outfn = "error.dat"
    required_points = 2

    if options.columns:
        columns = options.columns

    if options.data:
        data_col = options.data

    if options.out:
        outfn = options.out

    if options.required:
        required_points = options.required

    #data = defaultdict(defaultdict([]))
    data = Ddict( lambda: Ddict ( list ) )
    column_re = re.compile(r"(\s+[-+]?[0-9]*\.?[0-9]+(?:[eE][-+]?[0-9]+)?)")
    column_width_calculated = False
    column_width = 0
    data_column_widths = []
    for file in arguments:
        print "Processing: ",file
        if not os.path.exists(file):
            sys.exit()
        infile = None
        if file[-2:] == 'gz':
            infile = gzip.open(file, "rb")
        elif file[-3:] == 'bz2':
            infile = bz2.open(file, "rb")
        else:
            infile = open(file, "r")
        if not column_width_calculated:
            firstline = ''
            for line in infile:
                if line.startswith('#'):
                    continue
                else:
                    firstline = line
                    break
            m = column_re.findall(firstline)
            if m:
                column_width = reduce(add, map(len,m[0:columns]))
                column_width_calculated = True
                for col in m[columns:]:
                    data_column_widths.append(len(col))
                infile.seek(0)
        #print data_column_widths
        for line in infile:
            if line.startswith('#'):
                continue
            #d = line.split()
            #data[d[0]][d[1]].append(d[2])
            key = line[0:column_width]
            start_index = column_width
            for col in range(len(data_column_widths)):
                next_index = start_index+data_column_widths[col]
                data[key][col].append(float(line[start_index:next_index].strip()))
                start_index = next_index
            #data[line[0:column_width]].append(line[column_width:].strip())
    #print data
    #sys.exit()
    outfile = open(outfn, "w")
    for k in sorted(data.iterkeys()):
        v = data[k]
        dataline = ''
        for kk,vv in v.items():
            try:
                mean, variance, count = compensated_variance(vv)
            except:
                continue;
                pass
            if count >= required_points:
                min_v = min(vv)
                max_v = max(vv)
                data[k] = [mean, variance, min_v, max_v]
                dataline += ('%20g%20g%20g%20g' % ( mean,variance,min_v,max_v ))
        if len(dataline) > 0:
            outfile.write('%s%s\n' % (k,dataline))

if __name__ == "__main__":
    main(sys.argv[1:])
