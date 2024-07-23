#!/bin/bash

#mkdir /tmp/varios

for i in `seq 1 3` 
do
	
	touch /tmp/varios/core$i

done

rm -v /tmp/varios/core* >> /tmp/listacores
