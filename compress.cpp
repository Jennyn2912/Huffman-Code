/*Name: Trang Thai Van Nguyen A91104612
 *Name: 	Wei Jen Huang 	A99045410
 *Date: 1/25/2016
 *Assignment: PA2
 *File name: compress.cpp
 *Description: Takes a file and compresses it 
 *open the input file
 *count the frequency and store them in a vector<int> freqs
 *pass the freqs into the build() function to build the tree
 *write the freqs out to the OUTPUT file - implement the HEADER so TREES can be recreated.
 *the first position corresponds to the ASCII value of 0, 64th position corresponding 'a' 
 *and the count corresponds to the frequency. HEADER of the uncompressed
 *call encode on the input file, write it out the output file.
 */
#include <vector>
#include <fstream>
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include "HCTree.hpp"

using namespace std;

int main (int argc, char** argv) {
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
		if (inputFile.eof()) { break;}
		freqs[nextChar]++;
	}

	inputFile.close();

	outputFile.open(argv[2]);

	tree.build(freqs);

	int i;
	for ( i = 0; i < freqs.size(); i++) {
		outputFile << freqs[i] << endl;
	}

	inputFile.open(argv[1]);
	while(1) {
		nextChar = (unsigned char) inputFile.get();
		if (inputFile.eof()) {break;}
		tree.encode(nextChar, outputFile);	
	}

	inputFile.close();
	outputFile.close();

	return 0;

}



