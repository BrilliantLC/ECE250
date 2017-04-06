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

#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Leftist_node.h"
#include "Exception.h"

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

// implementation
template <typename Type>
bool Leftist_heap<Type>::empty() const {
	return size() == 0;
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
int Leftist_heap<Type>::count( const Type &obj ) const {
	return root_node->count(obj);
}

template <typename Type>
Type Leftist_heap<Type>::top() const {
	if (empty()) {
		throw underflow();
	} else {
		return root_node->retrieve();
	}
}

template <typename Type>
void Leftist_heap<Type>::push(const Type &obj) {
	Leftist_node<Type> *newLeftistNode = new Leftist_node<Type>(obj);
	root_node->push(newLeftistNode, root_node);
	heap_size++;
}

// template <typename Type>
// Type Leftist_heap<Type>::pop() {
// 	if (empty()) {
// 		throw underflow();
// 	}
// 	if (heap_size == 1) {
// 		Type root = root_node->retrieve();
// 		clear();
// 		return root;
// 	}
//
// 	Type root = root_node->retrieve();
// 	Leftist_heap<Type> *newLeftistHeap = new Leftist_heap<Type>;
// 	root_node = root_node->left();
// 	root->push(root->right(), root_node);
// 	heap_size--;
// 	return root_node->retrieve();
// }

template <typename Type>
Type Leftist_heap<Type>::pop(){
    // If the heap is empty we throw an underflow exception.
    if (empty()) {
        throw underflow();
    }
    //If it is not empty we store the value of the root node in tmp.
    Type tmp = root_node->retrieve();
    //If the current heap size is 1 then we clear the heap and return tmp.
    if (heap_size == 1){
        clear();
        return tmp;
    }
    //Other wise we create a new node called tmpRoot, set it equal to the root node. We then make the left
    // subtree the new root node and push the right subtree on to it.
    //Finally, we delete our tmpRoot, decrement the heap size and return the value stored at tmp.
    Leftist_node<Type> *tmpRoot  = root_node;
    root_node = tmpRoot->left();
    root_node->push(tmpRoot->right(), root_node);
    delete tmpRoot;
    --heap_size;
    return tmp;
}

template <typename Type>
void Leftist_heap<Type>::clear() {
	root_node->clear();
	heap_size = 0;
	return;
}


// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Leftist_heap<T> const &heap ) {
	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
