#!/bin/bash
for filename in `find . | egrep '\src\.cpp'`; 
do 
  gcov -n -o . $filename > /dev/null; 
done
