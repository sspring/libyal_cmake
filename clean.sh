#! /bin/bash

cd libyal_libs
for dir in `ls`
do
    rm -rf "$dir/.deps"
    rm -rf "$dir/Makefile"
    rm -rf "$dir/Makefile.am"
    rm -rf "$dir/Makefile.in"
    rm -rf "$dir/*~"

done
