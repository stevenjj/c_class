/*
PROG: loop
LANG: C
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BLOCK_SIZE 128

void resize_string( char **str, size_t newsize );


char * enc (char *string, size_t length){
  if (length <= 2){
    //printf("string=%s, length = %zu\n", string,length);
        return string;
  }
  size_t N = length;
  size_t k = N/2;

  char *left_side = malloc(k * sizeof(char)); //split left
  char *right_side = malloc( (N-k) * sizeof(char)); //split right
  
  // Assign left_side = [s_k, s_k-1, ... , s1]
  for(size_t i = 0; i < k; i++){
    left_side[i] = string[k-1-i];
  }
  
  // Assign right_side = [s_N, s_N-1, ... , s_k+1]
  for(size_t i = 0; i < (N-k); i++){  
    right_side[i] = string[N-1-i]; 
  }  
  //printf("string:%s, left side is: %s, right side is: %s, its lenght is:%zu\n",string, left_side, right_side, length);  
  
  left_side = enc(left_side, strlen(left_side));
  right_side = enc(right_side, strlen(right_side));
  resize_string(&left_side, N);
  strcat(left_side, right_side);
  
for(size_t i = 0; i < N; i++){  
  string[i] = left_side[i];
 }

  free(left_side);
  free(right_side);

  //  printf("string:%s\n", string);
  return string;
    //left_side;
    //split left
    //split right
    // apply backwards assigning using while loop
    // add them recusrively calling the function.
    // call the function again
    //strcat(lh

}


char * encrypt( char *string, size_t length ) {
  if (length <= 2){
    //printf("string=%s, length = %zu\n", string,length);
        return string;
  }
  size_t N = length;
  size_t k = N/2;
  char holder[1];
  

 // Assign left_side = [s_k, s_k-1, ... , s1]
  for(size_t i = 0; i < k/2; i++){
    holder[0] = string[i];
    string[i] = string[k-1-i];
    //  printf("string=%s, length = %zu\n", string,length);
    string[k-1-i] = holder[0];
  }
  // Assign right_side = [s_N, s_N-1, ... , s_k+1]
   for(size_t i = 0; i < (N-k)/2; i++){  
      holder[0] = string[i+k];
      string[i+k] = string[N-1-i]; 
      string[N-1-i] = holder[0];
      //printf("string=%s, length = %zu\n", string,length);      
  }  
  
   //   size_t N_size = N;
   // N_size >>= 7;
   //   while (N_size>0){
          encrypt(&string[0], k);
	  encrypt(&string[k], N-k);
	  //            N_size>>=1;
	  // }
  
	  //  printf("string=%s, length = %zu\n", string,length);
  return string;

  /* This is the encryption function;
   * Fill this out!
   */
}


/* Resize a string using realloc;
 * if realloc fails, do not change the string.
 */
void resize_string( char **str, size_t newsize ) {
  if( *str == NULL ) {
    *str = malloc( newsize );
  } else {
    char *tmp = realloc( *str, newsize );
    // If realloc failed, do not change str
    if( tmp == NULL ) {
      fprintf( stderr, "Failed realloc to size %zu.\n", newsize );
    } else {
      *str = tmp;
    }
  }
}

/* Safe way of reading the contents of 'input'
 * into a string 'str'. Your job is to read and
 * understand how this works and why is it safe,
 * and then fill out the body of the while() loop.
 * Feel free to use the resize_string function
 * provided above.
 *
 * Parameters:
 *   str: pointer to string that will be filled
 *        up; if the string is NULL, it will be
 *        created, else it'll be appended to.
 *   input: input FILE pointer
 * Returns:
 *   length of new string str
 */
size_t getstr( char **str, FILE *input ) {
  size_t chars_to_read = BLOCK_SIZE;
  size_t length = 0;

  // If str already exists, we'll append to the end
  if( *str != NULL ) {
    length = strlen( *str );
    while( chars_to_read < length ) {
      chars_to_read <<= 1;
    }
  }

  resize_string( str, chars_to_read << 1 );

  // Try to read in the number of 'chars_to_read'; store # of 
  // chars actually read from input in 'chars'
  size_t chars = 0;
  while( ( chars = fread( *str + length, 1, chars_to_read, input ) ) ) {

    size_t used_bytes = chars + length;
    length = strlen( *str );

    if (chars < chars_to_read){
      resize_string(str, used_bytes); //Resize exactly to the amount of bytes used.
      break;
    }


    
    chars_to_read <<= 1;
    resize_string(str, chars_to_read << 1);

    //length = strlen ( *str );
    //resize_string(str, length);
			 
    /* What you need to do:
     * We've just read # 'chars' into str. If we're at the end of
     * the file, we should exit the loop. Otherwise, we should
     * resize the string to read in more chars. Certain methods
     * will be faster than others, so try out a couple of different
     * ways of doing this and pick the fastest one. DO NOT LEAK MEMORY!
     */
  }

    length = strlen( *str );
    //    printf("string is:%s, length right now is:%zu\n", *str,  length);

  // Add a terminating '\0' (removing the final newline)
  // and resize to save space
  if( length > 0 ) {
    length = length - 1;
    (*str)[length] = '\0';
    char *tmp = realloc( *str, length + 1 );
    if( tmp != NULL ) {
      *str = tmp;
    }
  }
 return length;
}

int main(void) {
  FILE *input = fopen( "loop.in", "r" );
  if( input == NULL ) {
    fprintf( stderr, "Could not open loop.in.\n" );
    exit( EXIT_FAILURE );
  }
  char *string = NULL;
  size_t length = getstr( &string, input );
  fclose( input );

  encrypt( string, length );

  FILE *output = fopen( "loop.out", "w" );
  fprintf( output, "%zu\n", length );
  fprintf( output, "%s\n", string );
  fclose( output );

  free( string );
  return 0;
}
