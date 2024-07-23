#!/bin/bash 
#echo "" >> salida.dat
i=500
while [ "$i" -le 12500 ]
do
    ./dyv $i >> ./dyv2.dat
      i=$(( $i + 500 ))
done
      
