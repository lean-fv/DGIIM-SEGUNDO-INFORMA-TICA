#!/bin/bash 
#echo "" >> salida.dat
i=5000
while [ "$i" -le 125000 ]
do
    ./insercion_p_so $i >> ./insercion_p_so.dat
      i=$(( $i + 5000 ))
done
      
