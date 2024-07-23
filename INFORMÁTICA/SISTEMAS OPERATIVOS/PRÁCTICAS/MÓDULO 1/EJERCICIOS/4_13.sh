#!/bin/bash

echo "SHELL=/bin/sh" > crontab-reducelista
echo "PATH="`pwd`"/:$HOME/SO:"$PATH >> crontab-reducelista
echo "* * * * * /home/leandrofdez/Escritorio/LEANDRO/INFORMATICA/2/SO/ACTIVIDADES/4_11.sh" >> crontab-reducelista
