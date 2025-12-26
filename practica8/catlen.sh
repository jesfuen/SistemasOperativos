#!/bin/sh

usage(){
	echo "usage: $0 dir" 1>&2
	exit 1
}

notfound(){
	echo "directory not found: $1" 1>&2
	exit 1
}

if [ $# -ne 1 ] || ! [ -d "$1" ]; then
	usage
fi

dirname="$1"


cd "$dirname" || exit 1

if ! ls *.txt > /dev/null 2>&1; then
	echo "$0: no *.txt files"
	exit 1
fi

rm -f *.output

for archivo in $(ls *.txt | sort -f)
do
	long=$(echo -n "$archivo" | wc -c)
	
	cat "$archivo" >> "$long.output"
done



