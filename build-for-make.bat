@echo off

set bfolder=b_make
set genfor="MinGW Makefiles"

if not exist %bfolder% mkdir %bfolder%
cd %bfolder%

cmake -G %genfor% ..
cd ..
