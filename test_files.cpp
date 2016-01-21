#include <queue>
#include <vector>
#include <fstream>
#include "HCNode.hpp"
#include "HCNode.cpp"
#include "HCTree.hpp"
#include "HCTree.cpp"

using namespace std;
int main() {
	vector<int> freqs = vector<int>(256);
	freqs[65] = 2;
	freqs[66] = 1;
	freqs[67] = 4;

	build(freqs);

	ofstream out ("test.txt");
	
	if (out.is_open()) {
		encode(a,out);
		encode(b,out);
		encode(c,out);
		out.close();
	}
	
 }