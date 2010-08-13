# Makefile - top level makefile
# 

CC = gcc
CFLAGS = -c -g -O2 -Wall -Wno-unused-function -I./
RANLIB = ranlib
#DEFS = -DHAVE_CONFIG_H
DEFS = 
STATIC = 
LDFLAGS =  $(STATIC)
TARGET = libds.a
OUTDIR=obj

DS_OBJS = sll.o ds.o graph.o heap.o queue.o
ALGO_OBJS = is_sort.o

all: $(TARGET)

$(TARGET): $(DEPS) $(DS_OBJS) $(ALGO_OBJS)
	@echo Building dslib
	rm -f $@
	$(AR) cr $@ $(DS_OBJS) $(ALGO_OBJS)
	$(RANLIB) $@

clean:
	rm -f $(DS_OBJS) $(ALGO_OBJS) $(TARGET) 
