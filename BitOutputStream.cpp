#include "BitOutputStream.hpp"
#include <iostream>


void BitOutputStream::writeBit(int i) {
	if (nbits==8) flush();
    buffer = buffer | ( (i & 1) << nbits);
    nbits++;
}
