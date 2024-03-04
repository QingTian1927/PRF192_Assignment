#!/bin/bash

mkdirIfNotExist() {
    if [ ! -d "$1" ]; then
        mkdir "$1"
    fi
}

name="stringformat"
testName="stringformat_test"

outputDir="$PWD/temp"
mkdirIfNotExist "$outputDir"
bin="$outputDir/$testName.bin"

testedSrc="$PWD/$name.c"
testSrc="$PWD/$testName.c"

gcc -Wall -o "$bin" "$testSrc" "$testedSrc"

"$bin"

rm -r "$outputDir"
