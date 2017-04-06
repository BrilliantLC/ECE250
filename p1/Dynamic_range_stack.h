/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  c37liang@uwaterloo.ca
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

#ifndef DYNAMIC_STACK_AS_ARRAY_H
#define DYNAMIC_STACK_AS_ARRAY_H

#ifndef nullptr
#define nullptr 0
#endif

#include <algorithm>
#include "Exception.h"

class Dynamic_range_stack {
	private:
		int entry_count;
		int max_count;
		int min_count;
		int initial_capacity;
		int current_capacity;

		int *stack_array;
		int *maximum_array;
		int *minimum_array;

    //temporary arrays for expansion
		int *new_stack_array;
		int *new_max_array;
		int *new_min_array;

	public:
		Dynamic_range_stack( int = 10 );
		Dynamic_range_stack( Dynamic_range_stack const & );
		~Dynamic_range_stack();

		int top() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		int maximum() const;
		int minimum() const;


		void push( int const & );
		int pop();
		void clear();


	// Friends

	friend std::ostream &operator<<( std::ostream &, Dynamic_range_stack const & );
};

Dynamic_range_stack::Dynamic_range_stack( int n ):
entry_count( 0 ),
min_count( 0 ),
max_count( 0 ),
initial_capacity( std::max( 1, n ) ),
current_capacity( initial_capacity ),
stack_array( new int[current_capacity] ),
maximum_array( new int[current_capacity] ),
minimum_array( new int[current_capacity] ) {
	// empty constructor
}

Dynamic_range_stack::~Dynamic_range_stack() {	//destructor
	delete[] stack_array;
	delete[] maximum_array;
	delete[] minimum_array;
}

int Dynamic_range_stack::top() const {
	if (!empty()) {
		return stack_array[entry_count - 1];
	} else {
		throw underflow();	//throws error if the stack is empty
	}
}

int Dynamic_range_stack::maximum() const {
	if (!empty()) {	//do not need to impose that max_count != 0 as it would be repetitive
		return maximum_array[max_count - 1];
	} else {
		throw underflow();
		//throws error if the stack empty, meaning the maximum_array is empty
		//because there will always be a max/min if the stack is not empty
	}
}

int Dynamic_range_stack::minimum() const {
	if (!empty()) {
		return minimum_array[min_count - 1];
	} else {
		throw underflow();	//throws error if empty
	}
}

int Dynamic_range_stack::size() const {
	return entry_count;	//returns number of entries, 0 if empty
}

bool Dynamic_range_stack::empty() const {
	return entry_count == 0;	//returns true if number of entries is 0, false otherwise
}

int Dynamic_range_stack::capacity() const {
	return current_capacity;	//returns the current capacity of the stack
}

void Dynamic_range_stack::push( int const &obj ) {
	//double the capacity if full by expanding all 3 arrays
	if (entry_count == current_capacity) {
		//create new temporary arrays
		int *new_stack_array = new int[current_capacity * 2];
		int *new_max_array = new int[current_capacity * 2];
		int *new_min_array = new int[current_capacity * 2];

		current_capacity *= 2;

		//copy current contents to the new arrays
		std::copy(stack_array, stack_array + entry_count, new_stack_array);
		std::copy(maximum_array, maximum_array + max_count, new_max_array);
		std::copy(minimum_array, minimum_array + min_count, new_min_array);
		/***************************************************************************
		****************************************************************************
		Above: copy pasted the second line but forgot to change new_max_array to
		new_min_array...
		****************************************************************************
		***************************************************************************/

		//delete the old arrays' addresses
		delete[] stack_array;
		delete[] maximum_array;
		delete[] minimum_array;

		//point to the new addresses
		stack_array = new_stack_array;
		maximum_array = new_max_array;
		minimum_array = new_min_array;
	}

	/*****************************************************************************
	******************************************************************************
	moved this following block down (was on top of array expansion block) as if all
	items pushed are max/min then pushing in new max/min would cause the array to
	be out of bound
	******************************************************************************
	*****************************************************************************/
	//ensure there is a max & a min as long as the stack is not empty
	if (empty()) {
		maximum_array[0] = obj;
		minimum_array[0] = obj;
		max_count = 1;
		min_count = 1;
	} else if (obj > maximum_array[max_count - 1]) {	//set new max if the entry is bigger than last stored max
		maximum_array[max_count] = obj;
		max_count ++;
	} else if (obj < minimum_array[min_count - 1]) {	//set new min
		minimum_array[min_count] = obj;
		min_count ++;
	}
	//push in the new element
	stack_array[entry_count] = obj;
	entry_count ++;
}

int Dynamic_range_stack::pop() {
	if (!empty()) {
		int topEntry = stack_array[entry_count - 1];	//store value of the item being removed

		//check max/min
		//if the top element is also a max/min, delete from the max/min array first
		if (top() == maximum_array[max_count - 1]) {
			int *new_max_array = new int[current_capacity];
			//ignore the last element in the max array
			std::copy(maximum_array, maximum_array + max_count - 1, new_max_array);
			delete[] maximum_array;
			maximum_array = new_max_array;
			max_count --;
		}
		if (top() == minimum_array[min_count - 1]) {
			int *new_min_array = new int[current_capacity];
			//ignore the last element in the min array
			std::copy(minimum_array, minimum_array + min_count - 1, new_min_array);
			delete[] minimum_array;
			minimum_array = new_min_array;
			min_count --;
		}

		//remove top
		int *new_stack_array = new int[current_capacity];
		//ignore the last entry
		std::copy(stack_array, stack_array + (entry_count - 1), new_stack_array);
		delete[] stack_array;
		stack_array = new_stack_array;
		entry_count --;

		return topEntry;
	} else {	//throws error if trying to pop from empty stack
		throw underflow();
	}
}

void Dynamic_range_stack::clear() {
	//delete memory addresses
	delete[] stack_array;
	delete[] maximum_array;
	delete[] minimum_array;

	//create new arrays
	int *new_stack_array = new int[initial_capacity];
	int *new_max_array = new int[initial_capacity];
	int *new_min_array = new int[initial_capacity];

	//re-initialize all counters
	entry_count = 0;
	current_capacity = initial_capacity;
	max_count = 0;
	min_count = 0;

	//point to the new addresses
	stack_array = new_stack_array;
	maximum_array = new_max_array;
	minimum_array = new_min_array;
}

std::ostream &operator<<( std::ostream &out, Dynamic_range_stack const &stack ) {
	// Print out your stacks

	return out;
}

#endif
