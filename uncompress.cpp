#include "HCTree.hpp"



int main (int argc, char** argv) {

    //Open the input file for reading.
			ifstream inputFile;
			ofstream outputFile;

			unsigned char nextChar;
			HCTree tree;
	
			inputFile.open(argv[1]);

			if (!inputFile.is_open()) {
				cout << "FILE NOT OPEN" << endl;
	  		return -1;	
			}

			vector<int> freqs = vector<int>(256,0);

			while(1) {
				nextChar = (unsigned char) inputFile.get();
			}



    //Read the file header at the beginning of the input file, and reconstruct the Huffman coding tree. 
    //Open the output file for writing.
    //Using the Huffman coding tree, decode the bits from the input file into the appropriate sequence of bytes, writing them to the output file.
    //Close the input and output files.

	return 0;
}
