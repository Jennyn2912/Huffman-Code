/*Name: Trang Thai Van Nguyen A91104612
 *Name: 	Wei Jen Huang 	A99045410
 *Date: 1/25/2016
 *Assignment: PA2
 *File name: uncompress.cpp  
 *Description: Reads an input file and uncompresses the encoded
 *message according to the header which is 1024 bytes large. The frequency
 *of each ASCII code has its own line. The encoded message follows
 *right after the header.
 *Read the file header at the beginning of the input file, and reconstruct the Huffman coding tree. 
 *Open the output file for writing. Using the Huffman coding tree, 
 *decode the bits from the input file into the appropriate sequence of bytes, writing them to the output file.
 *Close the input and output files.
 */
#include "HCTree.hpp"
#include <fstream>
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include "HCTree.hpp"

using namespace std;

int main (int argc, char** argv) {

	//Open the input file for reading.
	ifstream inputFile;
	ofstream outputFile;

	unsigned char nextChar;
	HCTree tree;

	inputFile.open(argv[1],ios::binary);
	outputFile.open(argv[2],ios::binary);
	if (!inputFile.is_open()) {
		cout << "FILE NOT OPEN" << endl;
		return -1;	
	}

	vector<int> freqs = vector<int>(256,(int)0);
	string t;
	int total;
	for (int i = 0; i < 256; i++){
		getline(inputFile,t);
		freqs[i]=stoi(t);
		if (freqs[i] > 0) {
			total = total + freqs[i];
		}

	}
	//assign the frequency 
	tree.build(freqs);
 
 	BitInputStream inStream(inputFile);
	//at this point input file should be at the encoded message
	while(total > 0) {	
		outputFile << (char)tree.decode(inStream); 
		total--;
	}
	inputFile.close();
	outputFile.close();




	return 0;
}
