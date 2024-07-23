#!/bin/bash 
#echo "" >> salida.dat
i=5000
while [ "$i" -le 125000 ]
do
    ./quicksort_p_so $i >> ./quicksort_p_so.dat
      i=$(( $i + 5000 ))
done
      
