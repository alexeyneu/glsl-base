CC=c++ -c
CFLAGS=-c -DSTRICT -G3 -Ow -W3 -Zp -Tp
CFLAGSMT=-std=c++11 `pkg-config --cflags  gtk+-3.0 epoxy`
LINKER=c++
GUILIBS=`pkg-config --libs  gtk+-3.0 epoxy`

docks : trail op opzero

op : build/t.o build/libtarga.o
	$(LINKER) $(GUIFLAGS)  build/t.o build/libtarga.o  $(GUILIBS) -o op

opzero : build/tzero.o build/libtarga.o
	$(LINKER) build/tzero.o build/libtarga.o $(GUILIBS) -o opzero
	 
trail :
ifeq ($(wildcard build/.),)
	@mkdir build
endif
 build/tzero.o : tzero.c libtarga.h 
	$(CC) $(CFLAGSMT) tzero.c -o build/tzero.o

 build/libtarga.o : libtarga.cpp libtarga.h
	$(CC) $(CFLAGSMT) libtarga.cpp -o build/libtarga.o

 build/t.o : t.c libtarga.h
	$(CC) $(CFLAGSMT) t.c -o build/t.o

