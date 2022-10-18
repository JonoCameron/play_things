#!/bin/bash

sudo rmmod kern_mod.ko
make clean
make
