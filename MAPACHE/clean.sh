#!/bin/bash
cd build/
$prefix_client make clean
cd ../ 
rm -r -f cgi-bin
rm -r -f arch-temp-cgi
rm -r -f build
rm -r -f Documentacion/Doxy
#mkdir -p $(BASEDIR)
#cp -r -f ../$(BASEDIR) ./