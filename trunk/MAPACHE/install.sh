#!/bin/bash
mkdir -p cgi-bin
mkdir -p arch-temp-cgi
mkdir -p build
mkdir -p Documentacion/Doxy
cd build/
$prefix_client cmake [CMAKE_BUILD_TYPE:STRING=RELEASE] ../
$prefix_client make