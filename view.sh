#!/bin/bash
args=("$@")
command="splot "
for (( i=0; i<${#args[@]}; i++ )); do
	file="${args[${i}]}"
	if ! [ -e "${file}" ]; then
		echo "File ${file} not found."
		exit
	fi
	dezip=""
	if [[ "${file}" =~ ".gz" ]]; then
		if which zcat &> /dev/null; then
			dezip="< zcat "
		fi
		if which gzcat &> /dev/null; then
			dezip="< gzcat "
		fi
	fi
	command="${command} '${dezip}${file}' w d"
	let last=$#-1
	if [ $i -ne $last -a $# -gt 1 ]; then
		command="${command}, "
	fi
	if [ $i -eq $last ]; then
		command="${command}; pause -1"
	fi
done
gnuplot -e "$command"
