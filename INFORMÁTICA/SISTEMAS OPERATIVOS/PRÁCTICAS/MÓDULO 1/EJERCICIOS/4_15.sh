#!/bin/bash

find ~ -mtime 1 | cpio -pmduv /tmp/salvados$HOME
