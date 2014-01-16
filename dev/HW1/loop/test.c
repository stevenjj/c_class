#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char str[10] = {'a','b'};

int main(void){
  size_t N = 11;
  size_t k = N>>1;
  size_t k_2 = N/2;
  //  FILE *fout = fopen( "hello.out", "w");
  //fprintf( fout, "Hello, world!\n" );
  //fclose( fout);
  printf("N = %zu, k = %zu, k_2 = %zu", N, k, k_2);
  
  return 0;
}

