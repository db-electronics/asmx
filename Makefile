#
# Compiler flags
#
CC = gcc
CFLAGS = -Wall --std=gnu99
LDFLAGS = 

#
# Project files
#
EXT = .c
SRCDIR = src
SRCS = $(wildcard $(SRCDIR)/*$(EXT))

#
# Debug build settings
#
DBGDIR = debug
DBGEXE = $(addprefix $(DBGDIR)\, $(APPNAME))
DBGOBJS = $(SRCS:$(SRCDIR)/%$(EXT)=$(DBGDIR)/%.o)
DBGCFLAGS = -ggdb -O0

#
# Release build settings
#
RELDIR = release
RELEXE = $(addprefix $(RELDIR)\, $(APPNAME))
RELOBJS = $(SRCS:$(SRCDIR)/%$(EXT)=$(RELDIR)/%.o)
RELCFLAGS = -O2

ifeq ($(OS),Windows_NT)
RM = del /Q /F /S
APPNAME = asmx.exe
# thanks for being dumb mkdir on windows
MKDIRDBG = @dir $(DBGDIR) >nul 2>nul || @mkdir $(DBGDIR) >nul 2>nul
MKDIRREL = @dir $(RELDIR) >nul 2>nul || @mkdir $(RELDIR) >nul 2>nul
else
RM = rm -rf
APPNAME = asmx
MKDIRDBG = @mkdir -p $(DBGDIR)
MKDIRREL = @mkdir -p $(RELDIR)
endif

.PHONY: all clean debug release

# Default build
all: release

#
# Debug rules
#

debug: $(DBGEXE)
$(DBGEXE): $(DBGOBJS)
	$(CC) -o $(DBGEXE) $^ $(DBGCFLAGS) $(CFLAGS)

$(DBGDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(MKDIRDBG)
	$(CC) -o $@ -c $< $(DBGCFLAGS) $(CFLAGS)

#
# Release rules
#
release: $(RELEXE)
$(RELEXE): $(RELOBJS)
	$(CC) -o $(RELEXE) $^ $(RELCFLAGS) $(CFLAGS)

$(RELDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(MKDIRREL)
	$(CC) -o $@ -c $< $(RELCFLAGS) $(CFLAGS)

#
# Other rules
#

remake: clean all

ifeq ($(OS),Windows_NT)
DELOBJS = $(addprefix $(RELDIR)\, *.o)
DELOBJS += $(addprefix $(DBGDIR)\, *.o)
else
DELOBJS = $(RELOBJS)
DELOBJS += $(DBGOBJS)
endif

clean:
	$(RM) $(RELEXE) $(DBGEXE) $(DELOBJS)