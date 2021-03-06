#include "list.h"
#include "reduce.h"
#include "apply.h"
#include <iostream>

int main() {
  int N = 5;
  auto list = List{};

  std::cout << list.length() << "\n";
  for( int i = 0; i < N; ++i ) {
    list.append( 0 );
  }
  list.print();
  list.insertBefore(5,0);
  list.print();  
  list.deleteAll(0);
  list.print();  
  
  list.apply(SquareApply());
  list.reduce(SumReduce());
  list.reduce(SumReduce());
 

  list.print();
  return 0;
}
