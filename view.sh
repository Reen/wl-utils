#!/bin/bash -e
args=("$@")
command="splot "
last=`expr $# - 1`
style="dots"

function getMimeType {
  echo $(file -b --mime-type $1)
  return 0
}

function getNumCols {
  dezip=""
  file=""
  if [ "$2" == "" ]
  then
    dezip="cat "
    file=$1
  else
    dezip=${1:1}
    file=$2
  fi
  echo $($dezip $file | grep -v '#' | awk '{print NF}' | sort -nu | tail -1)
  return 0
}

for (( i=0; i<${#args[@]}; i++ )); do
  file="${args[${i}]}"
  if ! [ -e "${file}" ]
  then
    echo "File ${file} not found."
    exit
  fi
  dezip=""
  mimeType=$(getMimeType $file)
  case "$mimeType" in
    "application/x-gzip" )
      dezip="<gzip -cd "
      ;;
    "application/x-bzip2" )
      dezip="<bzip2 -cd "
      ;;
  esac

  if [ $i -eq 0 ]
  then
    numCols=$(getNumCols "$dezip" "$file")
    if (( numCols < 3 ))
    then
      command="plot "
      style="points"
    fi
  fi

  command="${command} '${dezip}${file}' w $style t \"$file\""
  if (( $i < $last && $# > 1 )); then
    command="${command}, "
  fi
  if (( $i == $last )); then
    command="${command}; pause -1"
  fi
done
echo $command
gnuplot -e "$command"
