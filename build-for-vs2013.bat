@echo off

set bfolder=b_vs2013
set genfor="Visual Studio 12 2013"

if not exist %bfolder% mkdir %bfolder%
cd %bfolder%

cmake -G %genfor% ..

pause