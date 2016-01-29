#include "BitInputStream.hpp"
#include <iostream>

int BitInputStream::readBit() {

	if ( nbits == 8 ) {
		fill();
	}

	int code = (buffer >> nbits ) & 1 ;
	std::cout << code ;
	nbits++;
	return code;
}

void BitInputStream::fill() {
	buffer = in.get();
	nbits = 0;
}