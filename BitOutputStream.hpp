#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>

class BitOutputStream {
	private:
		char buffer; //one byte buffer of bits
		int nbits;	//how many bits have been written to the buffer
		std::ostream & out; //reference to the input stream to use	
	public:
		/** Initialize a BitInputStream that will use the given
 			* istream for input
			*/
		BitOutputStream(std::ostream& os) : out (os) {
			//clear buffer and bit counter
			buffer = 0;
			nbits = 0;
		}

		/** Write the least significant bit of the argument to the 
		   * bit buffer and increment the buffer index.
		   * Flush the buffer first if it is full
		   */
		void writeBit(int i);

	
		/** Send the buffer to the output and clear it
		   */
		void flush() {
			out.put(buffer);
			out.flush();
			buffer = nbits = 0;
		}

};
#endif
