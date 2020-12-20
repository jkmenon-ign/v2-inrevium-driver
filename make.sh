#!/bin/sh


cd libsrc/gpio_v4_0/src/
make clean
make
cd ../../../

cd libsrc/iic_v3_1/src/
make clean
make
cd ../../../

cd libsrc/spi_v4_1/src
make clean
make
cd ../../../

cd libsrc/uartlite_v3_0/src
make clean
make
cd ../../../

cd test
make clean
make
cd ../
 
