#!/bin/bash
rm -f configPorDefecto.xml

if [ -d "build/" ]
then
	echo "Borrando archivos de la aplicacion..."
	cd build/
	$prefix_client make clean
	cd ../ 
	rm -r -f build
fi

if [ -d "cgi-bin" ]
then
rm -r -f cgi-bin
fi

if [ -d "arch-temp-cgi" ]
then
rm -r -f arch-temp-cgi
fi

if [ -d "build/" ]
then
	echo "Borrando documentacion..."
	rm -r -f Documentacion/Doxy/
fi

#mkdir -p $(BASEDIR)
#cp -r -f ../$(BASEDIR) ./
