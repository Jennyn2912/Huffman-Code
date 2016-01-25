/*Name: Trang Thai Van Nguyen A91104612
 *Name: 	Wei Jen Huang 	A99045410
 *Date: 1/25/2016
 *Assignment: PA2
 *File name: HCTree.cpp
 *Description: The actual implementations of the tree. Including 
 *the encoding and decoding of the text
 */
#include <vector>
//#include "BitInputStream.hpp"
//#include "BitOutputStream.hpp"
#include "HCTree.hpp"

using namespace std;

HCTree::~HCTree() {
	deleteAll(root);
}


void HCTree::deleteAll(HCNode* node) {
	if ( node == NULL) {	return; }
	else {
		deleteAll(node->c0);
		deleteAll(node->c1);
		delete node;
	}

}

/** Use the Huffman algorithm to build a Huffman coding trie.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the trie,
 *  and leaves[i] points to the leaf node containing byte i.
 */
void HCTree::build(const vector<int>& freqs) {

std:priority_queue<HCNode*,std::vector<HCNode*>,HCNodePtrComp> pqueue;
    int combine = 0;
    int i;

    for ( i = 0; i < 256; i++) {
	    if ( freqs[i] > 0) {
		    HCNode* pointer = new HCNode(freqs[i], i, 0, 0,0);
		    leaves[i] = pointer;
		    pqueue.push(pointer);
	    }
    }

    if (pqueue.size() == 0) {
	    cout << "File is empty" << endl;
	    return;
    }

    while (pqueue.size() > 1) {
	    HCNode* leaf1 = pqueue.top();
	    pqueue.pop();

	    HCNode* leaf2 = pqueue.top();
	    pqueue.pop();
	    combine = leaf1->count + leaf2->count;
	    HCNode* newNode = new HCNode(combine,leaf1->symbol, leaf1, leaf2,0);
	    leaf1->p = newNode;
	    leaf2->p = newNode;
	    pqueue.push(newNode);
    }

    this->root = pqueue.top();
    pqueue.pop();

}

/** Write to the given BitOutputStream
 *  the sequence of bits coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */

/*void HCTree::encode(byte symbol, BitOutputStream& out) const {
}*/

/** Write to the given ofstream
 *  the sequence of bits (as ASCII) coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT 
 *  BE USED IN THE FINAL SUBMISSION.
 */
void HCTree::encode(byte symbol, ofstream& out) const {
	HCNode* current = leaves[symbol];
	if (!current->p) {
		out << '0';
		return;
	}
	encodeRecursion(current, out);
}

void HCTree::encodeRecursion(HCNode* node, ofstream& out) const {
	//base case
	if (!node->p) {
		return;
	}
	//recursive cases
	else {
		encodeRecursion(node->p,out);
	}

	//from top of tree to bottom
	if((node->p)->c0 == node) {
		out << '0';
	}

	else {
		out << '1';
	}
}

/** Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
//int decode(BitInputStream& in) const;

/** Return the symbol coded in the next sequence of bits (represented as 
 *  ASCII text) from the ifstream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
 *  IN THE FINAL SUBMISSION.
 */
int HCTree::decode(ifstream& in  ) const {
	unsigned char code;
	HCNode* node = root;
  
	if (!(root->c0) && !(root->c1)) {
     in.get();
		 return root->symbol; 
	}

	else {
     //while not at the leaves
     while((node->c0)&&(node->c1)){ 
      code = in.get();
      if (in.eof()){break;}
			if ( code == '1' ) { 
				node = node->c1;
			}
			else {
				node = node->c0;
			}
   }
	return node->symbol;
	
	
  }
}
