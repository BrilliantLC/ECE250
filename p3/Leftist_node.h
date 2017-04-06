/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  c37liang @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Winter 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

#include <algorithm>
#include <iostream>
using namespace std;
// You may use std::swap and std::min

#ifndef nullptr
#define nullptr 0
#endif

template <typename Type>
class Leftist_node {
	private:
		Type element;
		Leftist_node *left_tree;
		Leftist_node *right_tree;
		int heap_null_path_length;

	public:
		Leftist_node( Type const & );

		Type retrieve() const;
		bool empty() const;
		Leftist_node *left() const;
		Leftist_node *right() const;
		int count( Type const & ) const;
		int null_path_length() const;

		void push( Leftist_node *, Leftist_node *& );
		void clear();
};

template <typename Type>
Leftist_node<Type>::Leftist_node( Type const &obj ):
element( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
heap_null_path_length( 0 ) {
	// does nothing
}

// You may need this

template <typename Type>
bool Leftist_node<Type>::empty() const {
	return ( this == nullptr );
}

// You must implement everything
template <typename Type>
Type Leftist_node<Type>::retrieve() const {
	return this->element;
}

template <typename Type>
Leftist_node<Type>* Leftist_node<Type>::left() const {
	return this->left_tree;
}

template <typename Type>
Leftist_node<Type>* Leftist_node<Type>::right() const {
	return this->right_tree;
}

template <typename Type>
int Leftist_node<Type>::null_path_length() const {
	if (!this) {
		return -1;
	} else {
		int length = 1 + std::min(left()->null_path_length(), right()->null_path_length());
		return length;
	}
}

template <typename Type>
int Leftist_node<Type>::count(const Type &obj) const {
	if (!this) {
		return 0;
	}
	int count = 0;
	if (this->element == obj) {
		count = 1;
	}
	if (left() != NULL) {
		count += left()->count(obj);
	}
	if (right() != NULL) {
		count += right()->count(obj);
	}
	return count;

}

template <typename Type>
void Leftist_node<Type>::push(Leftist_node *new_heap, Leftist_node *&ptr_to_this) {
	// return if new_heap is null
	if (new_heap == nullptr) {
		return;
	}
	// if this is null, set point to new heap;
	if (empty()) {
		ptr_to_this = new_heap;
		return;
	} else if (ptr_to_this->element <= new_heap->element) {
		right()->push(new_heap, right_tree);
		++ptr_to_this->heap_null_path_length;
		if (ptr_to_this->left()->null_path_length() < ptr_to_this->right()->null_path_length()) {
			// swap left and right subtree
			Leftist_node<Type> *newleft1 = left_tree;
			left_tree = right_tree;
			right_tree = newleft1;
		}
	} else {
		ptr_to_this = new_heap;
		new_heap->right()->push(ptr_to_this, new_heap);
		++ptr_to_this->heap_null_path_length;
		if (new_heap->left()->null_path_length() < new_heap->right()->null_path_length()){
			// swap left with right subtree in new heap
			Leftist_node<Type> *newleft2 = new_heap->left();
			new_heap->left_tree = new_heap->right();
			new_heap->right_tree = newleft2;
		}
	}
	if (empty()) {
		heap_null_path_length = -1;
	} else {
		heap_null_path_length = std::min(ptr_to_this->left_tree->null_path_length(), ptr_to_this->right_tree->null_path_length()) + 1;
	}
	return;

}

template <typename Type>
void Leftist_node<Type>::clear() {
	if (this == nullptr) {
		return;
	}
	left()->clear();
	right()->clear();
	delete this;
	return;
}


#endif
