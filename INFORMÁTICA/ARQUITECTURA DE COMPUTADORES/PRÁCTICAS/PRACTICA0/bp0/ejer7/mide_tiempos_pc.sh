#!/bin/bash

MIN=65536
MAX=16777216
mkdir -p tiempos_PC
echo -e ">> Tiempos para variable local PC"

for((N=$MIN ; N<=$MAX ; N=N*2)) do

	./LOCAL_SumaVectores $N >> ./tiempos_PC/tiempos_local_pc.txt
	
done

#The same for local and dynamic vectors.
