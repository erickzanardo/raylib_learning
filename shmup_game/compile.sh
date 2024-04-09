#!/bin/bash

eval cc game.c $(pkg-config --libs --cflags raylib) -o game
