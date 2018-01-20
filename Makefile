# this makefile just passes the buck to src/Makefile

.PHONY: all
all:
	cd src && $(MAKE) all

.PHONY: asmx
asmx:
	cd src && $(MAKE) asmx

.PHONY: strip
strip:
	cd src && $(MAKE) strip

.PHONY: install
install:
	cd src && $(MAKE) install

.PHONY: install-strip
install-strip:
	cd src && $(MAKE) install-strip

.PHONY: uninstall
uninstall:
	cd src && $(MAKE) uninstall

.PHONY: it
it:
	cd src && $(MAKE) it

.PHONY: zip
zip:
	cd src && $(MAKE) zip

.PHONY: test
test:
	cd src && $(MAKE) test

.PHONY: clean
clean:
	cd src && $(MAKE) clean
