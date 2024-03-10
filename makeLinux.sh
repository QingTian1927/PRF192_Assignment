#!/bin/bash

mkdirIfNotExist() {
    if [ ! -d "$1" ]; then
        mkdir "$1"
    fi
}

# This script can only be executed within the same directory
# as masterchefManager.c

src="$PWD"
build="$PWD/build"

binName="MasterchefsManager.bin"
bin="$build/$binName"

mkdirIfNotExist "$build"
mkdirIfNotExist "$build/objects"

libs="libs"

ins=(
    "masterchefManager.c"
    "$libs/cheflist/cheflist.c"
    "$libs/chefobject/chefobject.c"
    "$libs/database/database.c"
    "$libs/dateparser/dateparser.c"
    "$libs/stringformat/stringformat.c"
    "$libs/userinterface/userinterface.c"
)

outs=(
    "masterchefManager.o"
    "cheflist.o"
    "chefobject.o"
    "database.o"
    "dateparser.o"
    "stringformat.o"
    "userinterface.o"
)


for ((i = 0 ; i < ${#ins[@]} ; i++)); do
    in_file="$src/${ins[$i]}"
    out_file="$build/objects/${outs[$i]}"

    echo 'Compiling' $(basename "$in_file") '->' $(basename "$out_file")

    gcc -Wall -c "$in_file" -o "$out_file"
    outs[i]="$in_file"
done

echo ''
echo "Building $binName from object files"

gcc -Wall -o "$bin" "${outs[@]}"

echo ''
echo '-----------------------'
echo 'Finished all operations'