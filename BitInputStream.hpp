#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>

class BitInputStream {
	private:
		char buffer; //one byte byffer of bits
		int nbits;	//how many bits have been written to the buffer
		std::istream & in; //reference to the input stream to use	
	public:
		/** Initialize a BitInputStream that will use the given
 			* istream for input
			*/
		BitInputStream(std::istream & is) : in(is) {
			//clear buffer and bit counter
			buffer = 0;
			nbits = 8;
		}

		/** Fill the buffer from the input
		  */
		void fill();
		
		/** Read the next bit from the bit buffer.
		  * Fill the buffer from the input stream first if needed.
			* Return 1 if the bit read is 1;
			* Return 0 if the bit read is 0;
			*/
		int readBit();
			//If all bits in the buffer are read, fill the buffer first
			// Get the bit at the appropriate locataion in the bit
			// buffer and return the appropriate int
			// Increment the index
		
};
#endif
