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

    cout << "SIZE " << pqueue.size() << endl;

    while (pqueue.size() > 1) {
	    HCNode* leaf1 = pqueue.top();
	    pqueue.pop();

	    HCNode* leaf2 = pqueue.top();
	    pqueue.pop();
	    combine = leaf1->count + leaf2->count;
	    cout << combine << endl;
	    HCNode* newNode = new HCNode(combine,leaf1->symbol, leaf1, leaf2,0);
	    leaf1->p = newNode;
	    leaf2->p = newNode;
	    pqueue.push(newNode);

	    cout << "LEAF1 " << leaf1->symbol <<" " << leaf1->count << endl;
	    cout << "LEAF2 " << leaf2->symbol <<" " << leaf2->count << endl;
	    cout << "NEWNODE " << newNode->symbol <<" " << newNode->count << endl;

    }

    this->root = pqueue.top();
    pqueue.pop();
    //cout << root->symbol;
    //cout << root->count;

    cout << "END of build()" << endl;
}

/** Write to the given BitOutputStream
 *  the sequence of bits coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */

/*void HCTree::encode(byte symbol, BitOutputStream& out) const {
//TODO
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
int HCTree::decode(ifstream& in) const {
	char code;
	HCNode* node = root;
  
	if (!(root->c0) && !(root->c1)) {
		 return root->symbol; 
	}

	else {
     /*while(1){
      if (in.eof()){break;}
			code = in.get();
      cout << "value of code " << code << endl;
     }
     */
     
      code = in.get();
      //there needs to be a loop that traces it down to the leave
      //however I keep getting an infinite loop somehow
      //while (node->c1 && node->c2 != 0)
      //code = in.get()
			if ( (int)code == 1 ) { //why does this result in true when value of code is 0?
				node = node->c1;
        
        //std::cout<<"leaf1"<< endl;
			}
			else {
				node = node->c0;
        //std::cout<<"leaf0"<< endl;
			}
		

	}
	return node->symbol;

}
