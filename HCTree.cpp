#include <queue>
#include <vector>
#include <fstream>
#include "HCNode.hpp"
#include "HCNode.cpp"
//#include "BitInputStream.hpp"
//#include "BitOutputStream.hpp"
#include "HCTree.hpp"

using namespace std;


    /** Use the Huffman algorithm to build a Huffman coding trie.
     *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
     *  the frequency of occurrence of byte i in the message.
     *  POSTCONDITION:  root points to the root of the trie,
     *  and leaves[i] points to the leaf node containing byte i.
     */
    void HCTree::build(const vector<int>& freqs) {
    	
    	std:priority_queue<HCNode*,std::vector<HCNode*>,HCNodePtrComp> pqueue;
    	HCNode* leaf1 = new HCNode(0,0,0,0,0);
    	HCNode* leaf2 = new HCNode(0,0,0,0,0);
    	int combine = 0;
    	int i;
    	for ( i = 0; i < 256, i++) {
    		if ( freqs[i] != 0) {
    			HCNode* pointer = new HCNode(freqs[i], i, 0, 0, 0);
    			leaves[i] = pointer;
    			pqueue.push(pointer);
    		}
    	}

    	while (pqueue.size() > 1) {
    		leaf1 = pqueue.top();
    		pqueue.pop();
    		leaf2 = pqueue.top();
    		pqueue.pop();
    		combine = leaf1->count + leaf2->count;
    		HCNode* newNode = new HCNode(combine,0, leaf1, leaf2, 0);
    		leaf1->p = newNode;
    		leaf2->p = newNode;
    		pqueue.push(newNode);
    	}

    	this->root = pqueue.top();
    	cout << root->symbol;
    	cout << root->count;
    	pqueue.pop();

    }

    /** Write to the given BitOutputStream
     *  the sequence of bits coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
   	
   	void HCTree::encode(byte symbol, BitOutputStream& out) const {
		//TODO
    }

    /** Write to the given ofstream
     *  the sequence of bits (as ASCII) coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT 
     *  BE USED IN THE FINAL SUBMISSION.
     */
    void HCTree::encode(byte symbol, ofstream& out) const {
    	HCNode* current = leaves[symbol];
    	if (current->p) {
    		encode((current->p)->symbol, out);
    	}
    	else {
    		return;
    	}
    		
    	if ((current->p)->c0 == current) {
    		out.put('0');
    	}

    	else {
    		out.put('1');
    	}
    	
    }


    /** Return symbol coded in the next sequence of bits from the stream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    
    int HCTree::decode(BitInputStream& in) const {
		//TODO
    }

    /** Return the symbol coded in the next sequence of bits (represented as 
     *  ASCII text) from the ifstream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
     *  IN THE FINAL SUBMISSION.
     */
    int HCTree::decode(ifstream& in) const {
    	char code;
    	HCNode* node = root;

    	if (!(root->c0) && !(root->c1)) {
    		return root->symbol;
    	}

    	else {
    		code = in.get();
    		
    		if ( code == 1) {
    			node = node->c1;
    		}
    		else {
    			node = node->c0;
    		}
    	}
    	return node->symbol;
    	
    }