all: jpegCompression.o 

jpegCompression.o : 
	g++ -o jpegCompression jpegCompression.cpp -O2 -lm -lpthread -I/usr/X11/include -L/usr/X11/lib -lm -lpthread -lX11
	g++ -o fullCompression fullCompression.cpp bmplib.cpp Huffman.cpp
clean :
	rm -f *.o jpegCompression
	rm -f fullCompression
