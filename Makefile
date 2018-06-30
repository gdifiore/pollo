#
# Makefile - build pollo
#
# (c) 2018 gdifiore <difioregabe@gmail.com>
#      

VERSION = 1.0.0
PKGNAME = io.github.gdifiore.pollo
CC = gcc
TARGET = pollo

all : $(TARGET)

$(TARGET) : src/pollo.c
	$(CC) src/pollo.c -o $(TARGET)
	@echo Successfully built $(TARGET)