#!/bin/sh
g++ main.cpp -pthread --std=c++11 -o ~/server
chmod +x ~/server
~/server