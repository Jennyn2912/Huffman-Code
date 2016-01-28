#include "BitInputStream.hpp"
#include <iostream>

int BitInputStream::readBit() {
	if ( nbits == 8 ) {
		fill();
	}

	if ( ((buffer >> nbits) & 1) == 1) {
		return 1;
	}
	 else {
	 	return 0;
	 }

	 nbits++;
}

void BitInputStream::fill() {
	buffer = in.get();
	nbits = 0;
}