#!/bin/bash

x=0

for i in `seq 1 $1` 
do
	
	sleep 1
	x=`expr $x + 1`

done

printf "El valor de la variable es $x.\n"


