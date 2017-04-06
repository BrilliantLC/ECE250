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

#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Leftist_node.h"

template <typename Type>
class Leftist_heap {
	private:
		Leftist_node<Type> *root_node;
		int heap_size;

	public:
		Leftist_heap();
		~Leftist_heap();

		void swap( Leftist_heap &heap );


		bool empty() const;
		int size() const;
		int null_path_length() const;
		Type top() const;
		int count( Type const & ) const;

		void push( Type const & );
		Type pop();
		void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Leftist_heap<T> const & );
};

// some sample functions are given

template <typename Type>
Leftist_heap<Type>::Leftist_heap():
root_node( nullptr ),
heap_size( 0 ) {
	// does nothing
}



template <typename Type>
Leftist_heap<Type>::~Leftist_heap() {
	clear();  // might as well use it...
}

template <typename Type>
void Leftist_heap<Type>::swap( Leftist_heap<Type> &heap ) {
	std::swap( root_node, heap.root_node );
	std::swap( heap_size, heap.heap_size );
}



// Your implementation here
// STRONG HINT:  Write a default definition of each function, even if
// it only returns the default value (false, 0, or Type()).
//
// Once you have done this, you can proceed and implement the member functions
// one at a time.  If you do not, and just start implementing the member
// functions so that you can't compile and test your function, good luck. :-)


template <typename Type>
bool Leftist_heap<Type>::empty() const {
    return size() == 0 ? true : false;
}

template <typename Type>
int Leftist_heap<Type>::size() const {
    return heap_size;
}

template <typename Type>
int Leftist_heap<Type>::null_path_length() const {
    return root_node->null_path_length();
}

template <typename Type>
Type Leftist_heap<Type>::top() const {
    if (empty())
        throw underflow();
    return root_node->retrieve();
}

template <typename Type>
int Leftist_heap<Type>::count( Type const &obj ) const {
    return root_node->count(obj);
}

template <typename Type>
void Leftist_heap<Type>::push( Type const &obj ) {
    // Insert the new element into the heap by creating a new leftist node and calling push on the root node using root_node as a second argument. Increment the heap size
    Leftist_node<Type> *newLeftistNode = new Leftist_node<Type>(obj);
    /*if (root_node != 0 && newLeftistNode->retrieve() < root_node->retrieve()) {
        Leftist_node<Type> *swapRoot = root_node;
        root_node = newLeftistNode;
        root_node->push(swapRoot, root_node);
        heap_size++;
        return;
    }*/
    root_node->push(newLeftistNode, root_node);
    heap_size++;
}

template <typename Type>
Type Leftist_heap<Type>::pop() {
    // Pop the least element in the heap and delete its node (extracts min from the heap). If the tree is empty, this function throws an underflow exception. Otherwise, the left sub-tree of the root node is made the root node and the right-sub tree of the original root node is pushed into the new root node. Return the element in the popped node and decrement the heap size
    if (empty())
        throw underflow();

    Type element = root_node->retrieve();
    // delete the least element
    Leftist_node<Type> *oldRoot = root_node;
    // handle empty case
    if (root_node->right() == 0 || root_node->left() == 0 ||
        root_node->left()->retrieve() <= root_node->right()->retrieve()) {
        root_node = root_node->merge_nodes(root_node->right(), root_node->left());
    } else {
        root_node = root_node->merge_nodes(root_node->left(), root_node->right());
    }
    delete oldRoot;
    heap_size--;

    return element;
}

template <typename Type>
void Leftist_heap<Type>::clear() {
    if ( root_node != 0)
    {
        root_node->clear();
        //delete root_node;
        root_node = 0;
        heap_size = 0;
    }
}


// You can modify this function however you want:  it will not be tested

template <typename Type>
std::ostream &operator<<( std::ostream &out, Leftist_heap<Type> const &heap ) {
    out << heap.top() << std::endl;
 	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
