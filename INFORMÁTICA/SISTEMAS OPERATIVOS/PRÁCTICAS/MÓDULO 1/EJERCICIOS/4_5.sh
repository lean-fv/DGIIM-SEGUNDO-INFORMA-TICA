#!/bin/bash

nombrearchivo=`date +%Y-%j-%T`

ps -ef > $nombrearchivo
echo Mi PID = $$ >> $nombrearchivo
