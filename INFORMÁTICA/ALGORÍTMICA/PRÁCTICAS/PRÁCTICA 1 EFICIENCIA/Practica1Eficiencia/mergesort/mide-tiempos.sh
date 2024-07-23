#!/bin/bash 
#echo "" >> salida.dat
i=50000
while [ "$i" -le 1250000 ]
do
    ./mergesort_p_so $i >> ./mergesort_p_so.dat
      i=$(( $i + 50000 ))
done
      
