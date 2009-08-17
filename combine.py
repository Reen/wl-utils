#! /usr/bin/env python
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

def main(argv):
    opts = OptionParser()
    opts.add_option('--columns', '-c', help="Number of columns to use as key for combination, default is number of columns minus one.", type="int")
    opts.add_option('--data', '-d', help="Column number that should be combined, default is last.", type="int")
    options,arguments = opts.parse_args()

    # defaults
    columns = -1
    data_col = None

    if options.columns:
        columns = options.columns

    if options.data:
        data_col = options.data

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
    outfile = open("error.dat", "w")
    for k,v in data.items():
        outfile.write('%s' % k)
        for kk,vv in v.items():
            mean = 0.0
            varianceAcc = 0.0
            count = 0
            for vvv in vv:
                mean += vvv
                varianceAcc += (vvv*vvv)
                count+=1
            if count > 1:
                mean /= count
                variance = varianceAcc/(count-1)-(mean*mean)
                data[k] = [mean, variance]
                #print '%10s%10s%20g%20g' % ( k,kk,mean,variance )
                outfile.write('%20g%20g' % ( mean,variance ))
        outfile.write('\n')

if __name__ == "__main__":
    main(sys.argv[1:])
