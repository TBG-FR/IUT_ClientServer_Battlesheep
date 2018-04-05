#!/bin/sh
#cp ~/battlesheep ~/battlesheep.old
g++ main.cpp -pthread --std=c++11 -o ~/battlesheep
chmod +x ~/battlesheep
#~/battlesheep server