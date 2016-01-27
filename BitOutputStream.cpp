#include "BitOutputStream.hpp"
#include <iostream>


void BitOutputStream::writeBit(int i) {
	//If the bit buffer is full, flush it
	if (nbits == 8) {
		flush();
	}
	// Write the least significant bit of i
	// to bit buffer at current index
	buffer = buffer | ( (i&1) << nbits);

	//increment bit buffer index
	nbits++;
}


void BitOutputStream::flush() {
	out.put(buffer);
	out.flush();
	buffer = nbits = 0;
	//clear buffer and bit counter
}