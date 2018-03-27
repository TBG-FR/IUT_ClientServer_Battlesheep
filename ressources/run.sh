#!/bin/sh
g++ -o ~/server main.cpp -pthread --std=c++11
chmod +x ~/server
~/server