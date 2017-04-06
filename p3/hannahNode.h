/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  s357kim @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2017
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

        Leftist_node *merge_nodes(Leftist_node *, Leftist_node *) const;
        Leftist_node *second_merge_nodes(Leftist_node *, Leftist_node *) const;
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
Leftist_node<Type> *Leftist_node<Type>::left() const {
    return this->left_tree;
}

template <typename Type>
Leftist_node<Type> *Leftist_node<Type>::right() const {
    return this->right_tree;
}

template <typename Type>
int Leftist_node<Type>::count( Type const &obj ) const {
    if (this == 0)
        return 0;
    int noOfObjs = (this->element == obj) ? 1 : 0;

    if (this->left_tree != 0)
        noOfObjs += this->left_tree->count(obj);
    if (this->right_tree != 0)
        noOfObjs += this->right_tree->count(obj);

    return noOfObjs;
}

template <typename Type>
int Leftist_node<Type>::null_path_length() const {
    if (this == 0)
        return -1;
    //  a node with no children (a leaf node) or a node with exactly one child has a null-path length of 0
    else if (this->left_tree==0 || this->right_tree==0)
        return 0;
    return 1 + std::min(this->left_tree->null_path_length(), this->right_tree->null_path_length());
}

template <typename Type>
Leftist_node<Type> *Leftist_node<Type>::merge_nodes(Leftist_node *node1, Leftist_node *node2) const {
    if (node1 == 0) {
        return node2;
    }
    if (node2 == 0) {
        return node1;
    }
    if (node1->element <= node2->element) {
        return second_merge_nodes(node1, node2);
    } else {
        return second_merge_nodes(node2, node1);
    }
}

template <typename Type>
Leftist_node<Type> *Leftist_node<Type>::second_merge_nodes(Leftist_node *node1, Leftist_node *node2) const {
    if (node1->left_tree == 0) {
        node1->left_tree = node2;
    } else {
        node1->right_tree = merge_nodes(node1->right_tree, node2);
        if (node1->left_tree->heap_null_path_length < node1->right_tree->heap_null_path_length) {
            // swap trees
            Leftist_node *left = node1->left_tree;
            node1->left_tree = node1->right_tree;
            node1->right_tree = left;
            // update heap null path length
            node1->heap_null_path_length = node1->null_path_length();
        }
    }
    return node1;
}

template <typename Type>
void Leftist_node<Type>::push( Leftist_node *new_heap, Leftist_node *&ptr_to_this ) {
    //If the new heap is null, return. Otherwise, insert the new_heap into this heap: i) if this is null, set the pointer to this to be the new heap and return, ii) if the current node is storing a value less-than-or- equal-to the value stored in the root of the new heap, push the new node onto the right sub-tree with right_tree. Now, update the null-path length and if the left-sub-tree has a smaller null-path length than the right sub-tree, swap the two sub-trees, iii) otherwise, set the pointer to this to be the new heap and push this node into the new heap (with an appropriate second argument)

    ptr_to_this = merge_nodes(new_heap, ptr_to_this);
}

template <typename Type>
void Leftist_node<Type>::clear() {
    if (this == 0)
        return;
    this->element = nullptr;
    this->left_tree -> clear();
    this->right_tree -> clear();
    delete this;
    heap_null_path_length = 0;
}


#endif
