#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

/****************************************
* UW User ID:  c37liang
* Submitted for ECE 250
* Semester of Submission:  Winter 2017
*
* By submitting this file, I affirm that
* I am the author of all modifications to
* the provided code.
****************************************/

#include "Exception.h"
#include "ece250.h"
#include <iostream>

using namespace std;

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
private:
  int count;
  int power;
  int array_size;
  T *array;
  state *array_state;
  int h1( T const & ) const; // first hash function
  int h2( T const & ) const; // second hash function

public:
  DoubleHashTable( int = 5 );
  ~DoubleHashTable();
  int size() const;
  int capacity() const;
  bool empty() const;
  bool member( T const & ) const;
  T bin( int ) const;
  void print() const;
  void insert( T const & );
  bool remove( T const & );
  void clear();
};

template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
array( new T [array_size] ),
array_state( new state[array_size] ) {
  for ( int i = 0; i < array_size; ++i ) {
    array_state[i] = EMPTY;
  }
}

template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
  // destructor
  delete[] array;
  delete[] array_state;
}

template<typename T >
int DoubleHashTable<T >::size() const {
  // returns the number of elements in the hash table
  return count;
}

template<typename T >
int DoubleHashTable<T >::capacity() const {
  // enter the total number of bins (2^m)
  return array_size;
}

template<typename T >
bool DoubleHashTable<T >::empty() const {
  // returns true if hash table is empty, false otherwise
  if (count == 0) {
    return true;
  } else {
    return false;
  }
}

template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
  // implementation of h1(k), initial probe
  int input = static_cast<int> (obj);   // static cast the input
  int h1k = input % array_size;   // take modulo M(size)
  if (h1k < 0) {h1k += array_size;}   // add M if got negative
  return h1k;
}

template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
  // implementation of h2(k), offset
  int input = static_cast<int> (obj);   // static cast the input
  int h2k = (input / array_size) % array_size;    // (k/M)%M
  if (h2k < 0) {h2k += array_size;}   // make it positive
  if (h2k % 2 == 0) {h2k += 1;}   // check if even, make it odd
  return h2k;
}

template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {
  // returns true if input is in the hash table
  if (empty()) {
    return false;   // cannot be in the hash table if it's empty
  } else {
    // if all elements have the same h1, then i would go to size()-1 (ie. count-1) at most
    for (int i = 0; i <= size(); i++) {
      // if the entry is equal to obj
      if (array[(h1(obj) + i * h2(obj)) % capacity()] == obj &&
      array_state[(h1(obj) + i * h2(obj)) % capacity()] == OCCUPIED) {
        return true;
      } else {
        return false;
      }
      break;
    }
  }
}


template<typename T >
T DoubleHashTable<T >::bin( int n ) const {
  // returns the entry in bin n
  if (array_state[n] == OCCUPIED) {
    return array[n];
  }
}

template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {
  if (size() < capacity()) {    // only when size has not yet reached the max capacity
    for (int i = 0; i <= size() ; i++) {   // the max index one can go to is capacity - 1
      if (array_state[(h1(obj) + i * h2(obj)) % capacity()] != OCCUPIED) {
        array[(h1(obj) + i * h2(obj)) % capacity()] = obj;   // set value
        array_state[(h1(obj) + i * h2(obj)) % capacity()] = OCCUPIED;    // update state
        count += 1;   // increment count
        break;
      }
    }
  } else {
    throw overflow();
  }
}

template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
  for (int i = 0; i <= size(); i++) {
    // test if values are equal and flag says occupied
    if (array[(h1(obj) + i * h2(obj)) % capacity()] == obj &&
    array_state[(h1(obj) + i * h2(obj)) % capacity()] == OCCUPIED) {
      array[(h1(obj) + i * h2(obj)) % capacity()] = 0;    // reset value to 0
      array_state[(h1(obj) + i * h2(obj)) % capacity()] = DELETED;    // set flag to DELETED
      count --;
      return true;
    }
  }
  return false;
}


template<typename T >
void DoubleHashTable<T >::clear() {
  // initiate array_state to contain all EMPTYs and array to all 0s
  for ( int i = 0; i < array_size; ++i ) {
      array[i] = 0;
      array_state[i] = EMPTY;
  }
  count = 0;    // reset count
}

template<typename T >
void DoubleHashTable<T >::print() const {
  // enter your implemetation here
  for (int i = 0; i < array_size; i++) {
    std::cout << array[i] << " " << array_state[i] <<"\n";
  }
}

#endif
