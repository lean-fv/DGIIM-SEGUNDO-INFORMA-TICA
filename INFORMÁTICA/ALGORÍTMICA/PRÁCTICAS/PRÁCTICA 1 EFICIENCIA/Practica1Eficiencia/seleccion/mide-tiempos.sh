#!/bin/bash 
#echo "" >> salida.dat
i=5000
while [ "$i" -le 125000 ]
do
    ./seleccion_p_so $i >> ./seleccion_p_so.dat
      i=$(( $i + 5000 ))
done
      
