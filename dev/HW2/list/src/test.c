#include "list.h"
#include <stdio.h>

int sq( int x ) {
  return x * x;
}

int plus( int x, int y ) {
  return x + y;
}

int main(void) {
  int N = 2;
  List list = empty_list();

    for( int i = 0; i < N; ++i ) {
    list_append( &list, i );
  }
  list_print( list );
  


  list_insert_before( &list, 100,0);  
  
  //  list_insert_before( &list, 100,4);
  // list_insert_before( &list, 100,4);
  list_print( list );

  list_delete( &list, 1);
  //list_delete( &list, 3);
  //list_delete( &list, 4);
  // list_append( &list, 50);  
  // list_append( &list, 50);  
  // list_append( &list, 50);  

  //list_insert_before( &list, 100,2);


  list_print( list );
  list_delete( &list, 5);
  //  list_apply( &list,  &sq);
  list_print( list );
  list_delete( &list, 0);
  list_print( list );
  list_delete( &list, 1);
  list_print( list );

  //  list_delete( &list, 2);
  list_print( list );

  



  printf("result = %d\n", list_reduce( &list, &plus));

  list_clear( &list );
  return 0;
}
