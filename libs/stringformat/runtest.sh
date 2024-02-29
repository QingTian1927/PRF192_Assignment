#!/bin/bash

mkdirIfNotExist() {
    if [ ! -d "$1" ]; then
        mkdir "$1"
    fi
}

name="stringFormat"
testName="stringFormat_Test"

outputDir="$PWD/temp"
mkdirIfNotExist "$outputDir"
bin="$outputDir/$testName.bin"

testedSrc="$PWD/$name.c"
testSrc="$PWD/$testName.c"

gcc -Wall -o "$bin" "$testSrc" "$testedSrc"

"$bin"

rm -r "$outputDir"