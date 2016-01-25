/*Name: Trang Thai Van Nguyen A91104612
 *Name: 	Wei Jen Huang 	A99045410
 *Date: 1/25/2016
 *Assignment: PA2
 *File name: HCNode.cpp
 *Description: Allows us to compare one node to another by overloading
 *operators
 */
#include <iostream>
#include "HCNode.hpp"

  /** Less-than comparison, so HCNodes will work in std::priority_queue
   *  We want small counts to have high priority.
   *  And we want to break ties deterministically.
   */
  bool HCNode::operator<(const HCNode& other) {
  	//if not equal, return higher count
  	if (count != other.count) {
  		return count > other.count;
  	}

  	//if equal, compare symbols
  	else {
  		return symbol < other.symbol;
  	}
  }

  /** provide a compare function between HCNode* pointers
   *  so that priority comparison can be prioritized as appropriate
   *  Compare pointers to HCNode, to prioritize them.
   *  Dereference the pointers, and compare value.
   */
  bool comp(HCNode* one, HCNode* other) {
  	if (one != NULL && other != NULL) {
  		return *one < *other;
  	}

  	else {
  		return false;
  	}
  }
