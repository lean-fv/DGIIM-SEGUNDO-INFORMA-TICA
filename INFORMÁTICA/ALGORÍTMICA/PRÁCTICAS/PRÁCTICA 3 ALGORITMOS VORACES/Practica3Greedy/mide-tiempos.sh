#!/bin/bash 
#echo "" >> salida.dat
i=50
while [ "$i" -le 1500 ]
do
        ./generador-pvc ./salida.dat $i
 	./pvc1 ./salida.dat >> ./h1.dat
        i=$(( $i + 50 ))
done
      
