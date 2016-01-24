#include "HCTree.hpp"
#include <fstream>
//#include "BitInputStream.hpp"
//#include "BitOutputStream.hpp"
#include "HCTree.hpp"

using namespace std;

int main (int argc, char** argv) {

	//Open the input file for reading.
	ifstream inputFile;
	ofstream outputFile;

	unsigned char nextChar;
	HCTree tree;

	inputFile.open(argv[1]);
	outputFile.open(argv[2]);
	if (!inputFile.is_open()) {
		cout << "FILE NOT OPEN" << endl;
		return -1;	
	}

	vector<int> freqs = vector<int>(256,(int)0);
	string t;
	for (int i = 0; i < 256; i++){
	getline(inputFile,t);
	freqs[i]=stoi(t);
	}
	//assign the frequency 
	tree.build(freqs);
	//at this point input file should be at the encoded message

	while(1) {
		int ascii =tree.decode(inputFile); //get ascii value from tree
		if (inputFile.eof()) {break;}
		outputFile << ascii; //append to outputfile

	}
	inputFile.close();
	outputFile.close();


	//Read the file header at the beginning of the input file, and reconstruct the Huffman coding tree. 
	//Open the output file for writing.
	//Using the Huffman coding tree, decode the bits from the input file into the appropriate sequence of bytes, writing them to the output file.
	//Close the input and output files.

	return 0;
}
