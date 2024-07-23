#!/bin/bash 
#echo "" >> salida.dat
i=1
while [ "$i" -le 20 ]
do
        ./Generador/generador ./bb/salida.dat $i
 	./bb/bb ./bb/salida.dat >> ./bb/bb_c1.dat
        i=$(( $i + 1 ))
done
      
