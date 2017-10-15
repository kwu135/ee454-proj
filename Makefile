all: jpegCompression.o 

jpegCompression.o : 
	g++ -o jpegCompression jpegCompression.cpp -O2 -lm -lpthread -I/usr/X11/include -L/usr/X11/lib -lm -lpthread -lX11
clean :
	rm -f *.o jpegCompression