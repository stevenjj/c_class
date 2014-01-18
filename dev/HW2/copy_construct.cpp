

// Array::Array( Array rhs ) BAD <-- recursive definition, because we don't know how to copy it yet.

Array::Array( const Array& rhs) // Copy Constructor Takes in constant reference. We don't want to modify and we don't know how to copy
  : _size{rhs._size}, _elem{nullptr} { // Initializer list

    _elem = new int[_size];
    for( size_t i = 0; i < _size; ++i){
      _elem[i] = rhs._elem[i];
    }
		      }

Array& Array::operator=( const Array &rhs){
  if ( this != &rhs){
    _size = rhs._size;
    _elem = new double[_size];
    for( size_t i = 0; i < _size; ++i){
      _elem[i] rhs._elem[i];
    }
   }
  return *this;
}

      
