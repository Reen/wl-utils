#! /usr/bin/env python
import os
import sys
import re
import subprocess

def get_final_dos(path):
    files = os.listdir(path)
    re_dos = re.compile(r"^dos")
    files = [elem for elem in files if re_dos.match(elem)]
    files.sort(reverse=True)
    return files[0]

#.sort(reverse=True)

def main():
    cwd = os.getcwd()
    towhee_input = cwd+"/towhee_input"
    parq_file = cwd+"/parq.dat.gz"
    parq_dir = cwd+"/parq"
    if not os.path.exists(towhee_input) or not os.path.exists(parq_file):
        sys.exit()
    if not os.path.exists(parq_dir):
        os.mkdir(parq_dir)
    re_wl_data = re.compile(r"wl_emin\n(?P<wl_emin>.+)\nwl_emax\n(?P<wl_emax>.+)\nwl_nmin\n(?P<wl_nmin>\d+)\nwl_nmax\n(?P<wl_nmax>\d+)\nwl_read\n(?P<wl_read>.+)\nwl_read_constrain\n(?P<wl_read_constrain>.+)\nwl_output_freq\n(?P<wl_output_freq>\d+)\nwl_refine_freq\n(?P<wl_refine_freq>\d+)\nwl_refine_crit\n(?P<wl_refine_crit>\d+)\nwl_refine_time\n(?P<wl_refine_time>\d+)")
    re_run_time = re.compile(r"nstep\n(\d+)")
    twh_inpt_file = file(towhee_input, "r")
    twh_inpt_content = twh_inpt_file.read()
    m = re_wl_data.search(twh_inpt_content)
    if m:
        #print m.groups()
        refine_time = int(m.group("wl_refine_time"))
        emin = float(m.group("wl_emin").replace('d', 'e'))
        emax = float(m.group("wl_emax").replace('d', 'e'))
        nmin = int(m.group("wl_nmin"))
        nmax = int(m.group("wl_nmax"))
    else:
        sys.exit()
    m = re_run_time.search(twh_inpt_content)
    run_time = int(m.group(1))
    #print refine_time, run_time
    re_double = re.compile(r"([-+]?[0-9]*\.?[0-9]+(?:[eE][-+]?[0-9]+)?)")
    re_dos_step = re.compile(r"^dos\.([0-9]+)")
    outfile = open('error.dat', 'w')
    outfile.write("# N_skip	N_read	error\n")
    for nread in range(100*refine_time, run_time, 100*refine_time):
        for nskip in range(0, run_time-nread, 100*refine_time):
            matrix_file = parq_dir+('/mat_%09d_%09d.dat' % (nskip,nread))
            workdir = parq_dir+('/work_%09d_%09d' % (nskip, nread))
            if not os.path.exists(matrix_file):
                command = ("/cluster2/rhab/p/wl-utils/matrix_convert "
                + "--read %(read)i --skip %(skip)i -o %(output)s "
                + "--volume 125 --emin %(emin)e --emax %(emax)e "
                + "--nEnergy 500 --nmin %(nmin)i --nmax %(nmax)i "
                + "%(parq_file)s") % {'read': nread, 'skip': nskip, 
                'output': matrix_file,
                'emin': emin, 'emax': emax, 'nmin': nmin, 'nmax': nmax,
                'parq_file': parq_file}
                print command
                p = subprocess.Popen(command, shell=True)
                sts = os.waitpid(p.pid, 0)
            if not os.path.exists(workdir+'/balance.dat'):
                command = ("/cluster2/rhab/p/wl-utils/matrix_balance "
                + "--load %(matrix_file)s -w %(workdir)s") % {
                'matrix_file' : matrix_file, 'workdir' : workdir}
                print command
                p = subprocess.Popen(command, shell=True)
                sts = os.waitpid(p.pid, 0)
            final_dos_file = get_final_dos(workdir)
            final_dos_step = 0
            command = ("/cluster2/rhab/p/wl-utils/error %(workdir)s/%(dosfile)s") % {
            'workdir' : workdir, 'dosfile' : final_dos_file }
            print command
            p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE)
            output = p.communicate()[0]
            m = re_dos_step.search(final_dos_file)
            if m:
                final_dos_step = float(m.group(1))
            m = re_double.search(output)
            if m:
                error = float(m.group(1))
            else:
                print "WARNING: Can't find error-value in this output:\n"+output
            outfile.write("%12d%12d%20.12f%12d\n" % (nskip, nread, error, final_dos_step))

if __name__ == "__main__":
    main()
