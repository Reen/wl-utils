#!/bin/bash

gp_command="splot '< zcat $1' w d;pause -1;"
echo "$gp_command" | gnuplot -persist -  
