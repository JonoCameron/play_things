#!/bin/bash

make clean
make
sudo insmod kern_mod.ko
