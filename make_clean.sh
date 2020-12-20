#!/bin/sh


cd libsrc/gpio_v4_0/src/
make clean
cd ../../../

cd libsrc/iic_v3_1/src/
make clean
cd ../../../

cd libsrc/spi_v4_1/src
make clean
cd ../../../

cd libsrc/uartlite_v3_0/src
make clean
cd ../../../

cd test
make clean
cd ../

rm lib/* 
