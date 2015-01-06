
#include "Commons.h"

void *my_malloc(size_t size)
{
  void *ptr;
  if(size<=0) size=1; /* for AIX compatibility */
  ptr=(void *)malloc(size);
  if(!ptr) {
    perror ("Out of memory!\n");
    exit (1);
  }
  return(ptr);
}