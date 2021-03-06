#include "list.h"
#include "apply.h"
#include "reduce.h"

#include <iostream>

// complete the constructor!
//List::List() {
//  _list;
//}

// complete the destructor, as necessary
List::~List() {
  //  delete _list;
}

size_t List::length() const {
  // you fill out!
  return _list.size();
}

// Throw ListOutOfBounds() if pos >= length().
int& List::value( size_t pos ) {
  if (pos >= _list.size()){
    throw ListOutOfBounds();
  }
  return _list[pos];
  
  // you fill out!
}

// Throw ListOutOfBounds() if pos >= length().
int List::value( size_t pos ) const {
  if (pos >= _list.size()){
    throw ListOutOfBounds();
  }
  return _list.at(pos); // Returns a reference at specified element position
  // you fill out!
}

void List::append( int theValue ) {
  _list.push_back( theValue );
  // you fill out!
}

void List::deleteAll( int theValue ) {
  if (length() != 0){
    for(size_t i = 0; i < length(); i++){
      while ( value(i) == theValue){
	_list.erase(_list.begin()+i); // Erased the i-th element
	if ((length() == 0) || i>= length()){
	  break; // quit if empty or attempting to accessing non-existing i-th element
	}
      }
    }
  }  
  // you fill out!
}

void List::insertBefore( int theValue, int before ) {
  for(size_t i = 0; i < length(); i++ ){
    if ( value(i) == before){
      _list.insert( (_list.begin() + i), theValue);
      break;
    }
  }
  // you fill out!
}

// See apply.cpp
void List::apply( const ApplyFunction &interface ) {
  //  if (length() != 0){
    interface.apply( *this );
    // }
}

// See reduce.cpp
int List::reduce( const ReduceFunction &interface ) const {
  // if (length() == 0){
  //  return 0;
  //}
  return interface.reduce( *this );
}

// Already written for you, but kind of slow on large
// lists. Only for debugging purposes (function will
// not be tested on the grader)
void List::print() const {
  std::cout << "{ ";
  for( size_t p = 0; p < length() - 1; ++p ) {
    if (length() != 0){
      std::cout << value( p ) << " -> ";
    }
    if (length() == 0){
      break;
    }
  }
  if( length() > 0 ) {
    std::cout << value( length() - 1 ) << " ";
  }
  std::cout << "}\n";
}
