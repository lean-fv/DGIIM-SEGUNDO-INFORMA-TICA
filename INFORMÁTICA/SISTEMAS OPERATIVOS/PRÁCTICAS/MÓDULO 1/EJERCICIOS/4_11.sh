#!/bin/bash

head -n 10 /tmp/listacores > /tmp/temporal
rm /tmp/listacores
mv /tmp/temporal /tmp/listacores
