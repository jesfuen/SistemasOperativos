#!/bin/sh

# Esta forma es mas avanzada, el pipe es complejo y mas dificil de leer usar un bucle en su lugar.

# Funcion usage

usage(){
	echo "Usage: $0 dir" 1>&2  # Redireccion a salida de error
}

# Condicional para comprobar si se pasa el argumento correctamente y si el directorio existe
if [ $# -ne 1 ] || ! [ -d "$1" ]; then
	usage
fi

directorio="$1"

# Ejecutamos en un subshell para no afectar a la shell actual

# Aqui estoy en mi directorio de trabajo
echo $(pwd)
(
	# Aqui cambio a otro directorio
	cd $directorio
	# Se cambia de directorio en la subshell, al cerrar parentesis se vuelve a la shell original que mantiene el directorio de trabajo
	echo $(pwd)


	# El parentesis pequeño engloba al primer caracter del nombre de la cadena, en este caso es el grupo 2, el grupo 1 es el parentesis primero
	# Se sustituye la cadena por la primera letra del nombre del fichero, esto se pasa a print
	# awk print imprime variable, las comas se sustituyen por espacios
	# sort -u elimina los duplicados
	# sh ejecuta el texto recibido como un comando
	ls *.txt | sed -E 's/((.).*\.txt$)/ rm -f \2.output/' | \
		awk '{print $1, $2, tolower($3)}' | sort -u | sh

	ls *.txt | sort | sed -E 's/((.).*\.txt$)/cat \1>> \2.output/' | \
		awk '{print $1, $2, tolower($3)}' | sh

)

# Aqui estoy en mi directorio de trabajo
echo $(pwd)

# No utilizan exit 0 ya que se sale con el estado del ultimo comando ejecutado en el script

# $NF contenido de ultima columna