#include <iostream>
#include "HCNode.hpp"

  /** Less-than comparison, so HCNodes will work in std::priority_queue
   *  We want small counts to have high priority.
   *  And we want to break ties deterministically.
   */
  bool operator<(const HCNode& other) {
  	//if not equal, return higher count
  	if (this->count != other.count) {
  		return count > other.count;
  	}

  	//if equal, compare symbols
  	else {
  		return this->symbol < other.symbol;
  	}
  }

  /** provide a compare function between HCNode* pointers
   *  so that priority comparison can be prioritized as appropriate
   *  Compare pointers to HCNode, to prioritize them.
   *  Dereference the pointers, and compare value.
   */
  bool comp(HCNode* one, HCNode* other); {
  	if (one != NULL && other != NULL) {
  		return *one < *other;
  	}

  	else {
  		return false;
  	}

  }
