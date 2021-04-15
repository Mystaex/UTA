#include <stdlib.h>
#include <stdio.h>

int main()
{
  /*printf("Running test 3 to test realloc / calloc\n");

  char * ptr1 = ( char * ) malloc ( 1200 );
  
  printf("original: %p\n", ptr1);

  ptr1 = realloc(ptr1, 2000);

  printf("realloced: %p\n", ptr1);

  char * ptr2 = (char * ) calloc(200, 400);

  printf("Calloced: %p\n", ptr2);*/

  printf("Running test 3  to test coalesce\n");

  char * ptr1 = ( char * ) malloc ( 1200 );
  char * ptr2 = ( char * ) malloc ( 1200 );

  free( ptr1 );
  free( ptr2 );

  char * ptr3 = ( char * ) malloc ( 2048 );

  free( ptr3 );

  return 0;
}
