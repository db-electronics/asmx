HOW TO BUILD asmx

The standard way to build asmx is using the makefile:

  make

This will create the asmx binary in the src sub-directory.
That's it.  Now you might want to copy it to your
/usr/local/bin or ~/bin directory, but that's your choice.

If you are using a unix-like OS such as Linux, OS X, or BSD, you
can also use:

  make install

This will install the binaries to ~/bin, unless you change the
makefile to install it somewhere else. Symbolic links are generated
so that each CPU assembler can be used with a separate command.

If you can't use the makefile, the simplest way is this:

  gcc *.c -o asmx

That's it.  Now you will might want to copy it to your
/usr/local/bin or ~/bin directory, but that's your choice.

Windows users should install Cygwin as the easiest way to get GCC.
