#!/bin/sh

# Solucionar problema con ficheros y directorios que contienen espacios

usage(){
	echo "usage: $0 collection_dir dir1 [dir2 dir3 ...]" 1>&2
	exit 1
}

if [ $# -lt 2 ]; then
	usage
fi

dirname="$1"
shift

# Fichero de collecion, si no existe se crea, si existe se borra el contenido
if ! [ -d "$dirname" ]; then
	mkdir "$dirname"
else
	# Borra el contenido de manera silenciosa
	rm -f "$dirname"/*
fi 

# Comprobacion de que todos los directorios existan
for i in "$@"
do
	if ! [ -d "$i" ]; then
		echo "error: dir $i not found" 1>&2
		rm -r "$dirname"
		exit 1
	fi
done

# Obtiene todos los ficheros indicados en el enunciado y con awk nos quedamos con el path a esos ficheros
cmd=$(du -a | egrep -i '\.(jpe?g|png|tiff)$' | awk '{print $2}')

for line in $cmd
do
	line=$(echo "$line" | tr ' ' '_')
	echo "$line"
	# Nombre de fichero
	filename=$(basename "$line")
	# Nombre del directorio
	directory=$(dirname "$line" | sed -E 's/.*\/([a-zA-Z0-9 ]+)/\1/g')
	# Obtencion de la extension
	extension=$(echo "$filename" | sed -E 's/.*\.([a-zA-Z]+)$/\1/g' | tr A-Z a-z )
	# Si la extension es jpeg se convierte a jpg
	if [ $extension = jpeg ]; then
		extension=jpg
	fi

	# Nombre del fichero sin extension
	name=$(echo "$filename" | sed -E 's/(.*)\.([a-zA-Z]+)$/\1/g')
	echo "$name"
done






