#!/bin/sh

# arguments:
# $1: path to directory that contains the source files (txt)
# $2: name of the output file

# prepare tmp dir
rm -rf tmp
mkdir tmp

# create postscript file for each file in the given folder
for f in $1/*
do
    echo "Generating postscript file for: $f"
    tmpName=$(basename $f)
    paps $f --header --landscape > "tmp/$tmpName.ps"
done

# combine postscript files to pdf
for f in tmp/*.ps
do
	echo "Creating pdf for: $f"
    ps2pdf $f "$f.pdf"
done

# combine pdfs
gs -dNOPAUSE -sDEVICE=pdfwrite -sOUTPUTFILE=$2.pdf -dBATCH tmp/*.pdf

# cleanup
rm -rf tmp
