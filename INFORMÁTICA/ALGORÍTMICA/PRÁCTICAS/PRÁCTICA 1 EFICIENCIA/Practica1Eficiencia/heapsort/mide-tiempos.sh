#!/bin/bash 
#echo "" >> salida.dat
i=50000
while [ "$i" -le 1250000 ]
do
    ./heapsort_p_so $i >> ./heapsort_p_so.dat
      i=$(( $i + 50000 ))
done
      
