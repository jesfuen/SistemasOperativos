#!/bin/sh

usage(){
	echo "Usage: $0" 1>&2
}

nofiles(){
	echo error no files 1>&2
}

listfiles(){
	ls -la | egrep '^-' | awk '{print $5, $9}'
}



if [ $# -ne 0 ]; then
	usage
fi


if ! [ $(ls -la | egrep '^-' | wc -l) -ne 0 ]; then
	nofiles
fi

cmd=listfiles

files=$($cmd | sort -nr | awk '{print $2}')

biggest=''

for f in $files
do
	biggest=$(realpath $f)
	break
done

echo "mv $biggest $biggest.old"














