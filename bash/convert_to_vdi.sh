#!/bin/bash

printf "Enter Input File's PATH: "
read IFILE
printf "Enter Output File's PATH: "
read OFILE

rm -f $OFILE

VBoxManage convertdd $IFILE $OFILE
echo "Successfully converted $IFILE into a VBox disk image at: $OFILE"
