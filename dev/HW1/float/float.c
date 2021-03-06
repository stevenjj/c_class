/*
PROG: floating
LANG: C
*/

#include <stdio.h>
#include <stdlib.h>

#include <string.h>     /* strcat */

unsigned int sign     = 0x80000000; // sign bits
unsigned int exponent = 0x7F800000; // exponent bits 
unsigned int mantisa  = 0x007FFFFF; // mantisa bits
unsigned int bias = 127;
 
union float_bits{
  float f;
  unsigned int bits;
};


const char *byte_to_binary(unsigned x)
{
  static char b[24];
  b[0] = '\0';
  char *p = b;
  
  unsigned int z = 0x400000;

  while (z > 0){
    //strcat(b, ((x & z) == z) ? "1" : "0");
    *p++ = (x & z) ? '1' : '0';  
    z >>= 1;
    }

  return b;
}


void print_hex( float f){
  union float_bits t;
  t.f = f;
  printf(" The float %f looks like 0x%x in hex.\n", t.f, t.bits);
}

size_t scan_size_of_file(FILE *input){
  size_t i = 0;
  float nothing = 0;
  while(fscanf(input, "%f",&nothing) == 1){
    i++;
    //  printf("%zu\n",i);
  }
  return i;
}

unsigned int give_bits(float f){
  union float_bits t;
  t.f = f;
  return t.bits;
}


int main(void){
  FILE *fin = fopen( "floating.in", "r");
  
  if (fin == NULL){
    printf( "Error: could not open floating.in\n" );
    exit( EXIT_FAILURE );
  }
  
  int n = 0;

  fscanf(fin, "%d",&n);
    //  n = scan_size_of_file(fin);
  size_t i = 0;
  //rewind(fin);
  float list_of_floats[n];  

  while(fscanf(fin, "%f", &list_of_floats[i]) == 1){
    //printf("%f, %zu\n", list_of_floats[i], i);
     print_hex(list_of_floats[i]);
      i++;
   }
  fclose(fin);  

  i=0;
  FILE *output = fopen("floating.out","w");

  while(i< (size_t) n){  
  unsigned int sign_out = (((give_bits(list_of_floats[i]) & sign) >> 31) == 1) ? -1 :  1;
  unsigned int mantisa_out = give_bits(list_of_floats[i]) & mantisa; // must convert this to binary
  unsigned int exponent_out = (((give_bits(list_of_floats[i])) & exponent) >> 23) - bias;

  printf(" The unsigned int looks like 0x%x in hex.\n", (give_bits(list_of_floats[i]) & sign) | ((exponent_out+bias)<<23) | mantisa_out);
  fprintf(output, "%d.%s * 2^%d\n", sign_out,byte_to_binary(mantisa_out), exponent_out);
  i++;
  }
  
  fclose( output );
  return 0;
}
