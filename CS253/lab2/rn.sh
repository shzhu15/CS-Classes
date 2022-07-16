#! /bin/bash

old_suffix=$1
new_suffix=$2

if [ $# -eq 0 ]
  then
    std::err "Not enough arguements"
if [ $# \> 2 ]
  then
    echo "Too many arugements"

for f in *.$old_suffix
do
   new_name=${f%.*}.$new_suffix
   echo Rename $f to $new_name
done
