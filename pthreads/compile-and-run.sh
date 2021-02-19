set -e

if [ ! -f "$1" ]; then 
	echo "Provide a single existing source"
	exit
fi

TARGET="$(echo "$1" | cut -d'.' -f1)"

gcc -o $TARGET $1 -lpthread 
./$TARGET
