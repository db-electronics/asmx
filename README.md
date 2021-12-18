# ASMX
ASMX is originally a cross-assembler developped by Bruce Tomlin. His original work can found in this repository under [release 2.0b5](https://github.com/db-electronics/asmx/releases/tag/2.0b5). This repository contains a fork of Bruce's original work licensed under GPLv3.

Pull requests welcomed!

# Modifications By Others
The fine people over at [Retrotechnology.com](https://www.retrotechnology.com/memship/asmx.html) have published several fixes to asmx. These have been incorporated into this repository. I kept all markers (changes are initialed with "HRJ" or "Herb" or other's initials) where possible to denote this and to attribute their work. 

# Build the Project
ASMX builds under Linux and Windows, I have not tested it on MAC. Just run make.
* Add the gcc/gdb path to the system PATH environment variable
    * ex: __'C:/msys64/mingw64/bin'__

Else you can build ASMX directly from the command line rather simply with the following command.
```
gcc *.c -O2 -o asmx
```
# Options
* --                  
    * end of options
* -C cputype          
    * specify default CPU type (currently no default)
* -b [base[-end]]
    * output object file as binary with optional base/end addresses
* -e
    * show errors to screen
* -w                  
    * show warnings to screen
* -l [filename]       
    * make a listing file, default is srcfile.lst
* -o [filename]       
    * make an object file, default is srcfile.hex or srcfile.s9
* -d label[[:]=value] 
    * define a label, and assign an optional value
* -s9
    * output object file in Motorola S9 format (16-bit address)
* -s19                
    * output object file in Motorola S9 format (16-bit address)
* -s28
    * output object file in Motorola S9 format (24-bit address)
* -s37
    * output object file in Motorola S9 format (32-bit address)
* -t                  
    * output object file in TRSDOS executable format (implies -C Z80)
* -c                  
    * send object code to stdout

# Usage
*asmx [options] srcfile*

Assemble a Motorola 68000 asm file
```
asmx -C 68000 -e -w -b 0 -l out/rom.lst -o out/rom.bin -- main.68k
```