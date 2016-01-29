/*Name: Trang Thai Van Nguyen A91104612
 *Name: 	Wei Jen Huang 	A99045410
 *Date: 1/25/2016
 *Assignment: PA2
 *File name: HCTree.cpp
 *Description: The actual implementations of the tree. Including 
 *the encoding and decoding of the text
 */
#include <vector>
#include <stack>
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include "HCTree.hpp"


using namespace std;

HCTree::~HCTree() {
	deleteAll(root);
}


void HCTree::deleteAll(HCNode* node) {
	if ( node == NULL) { return; }
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

void HCTree::encode(byte symbol, BitOutputStream& out) const {
	HCNode* current = leaves[symbol];
	//First in, Last Out
	stack<int> encodeString;
	if (current == this->root) {
		out.writeBit(0);
		return;
	}

	while (current->p){

		if((current->p)->c0 == current) {
			encodeString.push(0);
		}
		else {
			encodeString.push(1);
		}
		current = current->p;
	}

	while ( encodeString.size() > 0) {
		out.writeBit(encodeString.top());
		cout << encodeString.top() << endl;
		encodeString.pop();
	}
}


/** Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
int HCTree::decode(BitInputStream& in) const {
	int bit;
	HCNode* node = this->root;

	while ((node->c0)!= 0 && (node->c1) != 0 ) {
		bit = in.BitInputStream::readBit();

		if (bit == 1) {
			node = node->c1;
		}
		else {
			node = node->c0;
		}
	}
	return node->symbol;
}

