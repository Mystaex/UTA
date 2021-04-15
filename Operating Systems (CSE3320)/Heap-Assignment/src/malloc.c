#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define ALIGN4(s)         (((((s) - 1) >> 2) << 2) + 4)
#define BLOCK_DATA(b)      ((b) + 1)
#define BLOCK_HEADER(ptr)   ((struct _block *)(ptr) - 1)

/*
 * Name: Robert Fabbro
 * ID: 1001724536
 * Name: Ethan Chase
 * ID: 1001457646
 */

static int atexit_registered = 0;
static int num_mallocs       = 0;
static int num_frees         = 0;
static int num_reuses        = 0;
static int num_grows         = 0;
static int num_blocks        = 0;
static int num_requested     = 0;
static int max_heap          = 0;


/*
 *  \brief printStatistics
 *
 *  \param none
 *
 *  Prints the heap statistics upon process exit.  Registered
 *  via atexit()
 *
 *  \return none
 */
void printStatistics( void )
{
  printf("\nheap management statistics\n");
  printf("mallocs:\t%d\n", num_mallocs );
  printf("frees:\t\t%d\n", num_frees );
  printf("reuses:\t\t%d\n", num_reuses );
  printf("grows:\t\t%d\n", num_grows );
  printf("splits:\t\t[NONE]\n");
  printf("coalesces:\t[NONE]\n");
  printf("blocks:\t\t%d\n", num_blocks );
  printf("requested:\t%d\n", num_requested );
  printf("max heap:\t%d\n", max_heap );
}

struct _block 
{
   size_t  size;         /* Size of the allocated _block of memory in bytes */
   struct _block *prev;  /* Pointer to the previous _block of allcated memory   */
   struct _block *next;  /* Pointer to the next _block of allcated memory   */
   bool   free;          /* Is this _block free?                     */
   char   padding[3];
};


struct _block *heapList = NULL; /* Free list to track the _blocks available */
struct _block *last_reuse = NULL;

/*
 * \brief findFreeBlock
 *
 * \param last pointer to the linked list of free _blocks
 * \param size size of the _block needed in bytes 
 *
 * \return a _block that fits the request or NULL if no free _block matches
 */
struct _block *findFreeBlock(struct _block **last, size_t size) 
{
   struct _block *curr = heapList;

#if defined FIT && FIT == 0
   /* First fit */
   while (curr && !(curr->free && curr->size >= size)) 
   {
      *last = curr;
      curr  = curr->next;
   }
#endif

#if defined BEST && BEST == 0
   /* Best fit */
   size_t minDiff = INT_MAX;
   struct _block *temp = NULL;
   size_t currentDiff = 0;
   //Loop through entire block list
   while (curr)
   {
      *last = curr;
      currentDiff = (int) (curr->size - size);
      //If new minimum difference is found, update as current best fit.
      if((size <= curr->size) && (minDiff > currentDiff) && (curr->free))
      {
         temp = curr;
         minDiff = currentDiff;
      }
      curr  = curr->next;
   }
   //Set the final best fit as return block
   curr = temp;
#endif

#if defined WORST && WORST == 0
   size_t maxDiff = 0;
   struct _block *temp = NULL;
   size_t currentDiff = 0;
   while (curr)
   {
      *last = curr;
      currentDiff = (int) (curr->size - size);
      // If new maximum difference is found, update as current worse fit.
      if((size <= curr->size) && (maxDiff < currentDiff) && (curr->free))
      {
         temp = curr;
         maxDiff = currentDiff;
      }
      curr  = curr->next;
   }
   curr = temp;
#endif

#if defined NEXT && NEXT == 0
   // check if there has been a last_reuse
   if(!last_reuse)
      last_reuse = curr;
   // follow first fit logic, just start at last_reuse instead of at the head.
   while(last_reuse && !(last_reuse->size >= size && last_reuse->free))
   {
      *last = last_reuse;
      last_reuse = last_reuse->next;
   }
   curr = last_reuse;
#endif

   return curr;
}

/*
 * \brief growheap
 *
 * Given a requested size of memory, use sbrk() to dynamically 
 * increase the data segment of the calling process.  Updates
 * the free list with the newly allocated memory.
 *
 * \param last tail of the free _block list
 * \param size size in bytes to request from the OS
 *
 * \return returns the newly allocated _block of NULL if failed
 */
struct _block *growHeap(struct _block *last, size_t size) 
{
   /* Request more space from OS */
   struct _block *curr = (struct _block *)sbrk(0);
   struct _block *prev = (struct _block *)sbrk(sizeof(struct _block) + size);

   assert(curr == prev);

   /* OS allocation failed */
   if (curr == (struct _block *)-1) 
   {
      return NULL;
   }

   /* Update heapList if not set */
   if (heapList == NULL) 
   {
      heapList = curr;
   }

   /* Attach new _block to prev _block */
   if (last) 
   {
      last->next = curr;
   }

   /* Update _block metadata */
   curr->size = size;
   curr->next = NULL;
   curr->free = false;
   num_grows++;
   return curr;
}

/*
 * \brief malloc
 *
 * finds a free _block of heap memory for the calling process.
 * if there is no free _block that satisfies the request then grows the 
 * heap and returns a new _block
 *
 * \param size size of the requested memory in bytes
 *
 * \return returns the requested memory allocation to the calling process 
 * or NULL if failed
 */
void *malloc(size_t size) 
{

   if( atexit_registered == 0 )
   {
      atexit_registered = 1;
      atexit( printStatistics );
   }

   /* Align to multiple of 4 */
   size = ALIGN4(size);

   /* Handle 0 size */
   if (size == 0) 
   {
      return NULL;
   }

   /* Look for free _block */
   struct _block *last = heapList;
   struct _block *next = findFreeBlock(&last, size);

   /* Could not find free _block, so grow heap */

   if (next == NULL) 
   {
      next = growHeap(last, size);
      max_heap += size;
   }
   else
   {
      num_reuses++;
      num_blocks--;
   }

   /* Could not find free _block or grow heap, so just return NULL */
   if (next == NULL) 
   {
      return NULL;
   }


   
   /* Mark _block as in use */
   next->free = false;

   /* Return data address associated with _block */
   num_mallocs ++;
   num_requested += size;
   return BLOCK_DATA(next);
}

/*
 * \brief free
 *
 * frees the memory _block pointed to by pointer. if the _block is adjacent
 * to another _block then coalesces (combines) them
 *
 * \param ptr the heap memory to free
 *
 * \return none
 */
void free(void *ptr) 
{
   if (ptr == NULL) 
   {
      return;
   }

   /* Make _block as free */
   struct _block *curr = BLOCK_HEADER(ptr);
   assert(curr->free == 0);
   curr->free = true;
   num_frees++;
   num_blocks++;
}

/*
* \brief realloc
*
* Creates a new memory block with updated size. Copies contents of original
* memory block into new memory block, and then frees original block.
*
* \param ptr the heap memory to copy into new memory then free
* \param size of the new memory block
*
* \return new memory block with original memory block contents or
*  returns a new malloced memory if ptr is null or returns itself
*  if the requested size is smaller than the current size.
*/
void* realloc(void *ptr, size_t size)
{
   // if ptr doesn't exist, return a new malloced block.
   if(ptr == NULL)
   {
       return malloc(size);
   }
   struct _block* curr = ptr;
   
   // if requested size is smaller than current block
   // just return itself. Don't want to have
   // an overflow on data copy to smaller size.
   if(size <= curr->size)
   {
       return ptr;
   }

   struct _block* new_ptr = malloc(size);
   memcpy(new_ptr, curr, curr->size);
   free(curr);

   return new_ptr;
}

/*
* \brief calloc
*
* allocates a new block based on the wanted size of array and
* size of the elements. Sets the memory to 0 rather than random
* junk.
*
* \param size of array, size of inputted elements
*
* \returns requested malloced array or NULL if failed.
*/
void* calloc(size_t nmemb, size_t size)
{
   if(nmemb == 0 || size == 0)
   {
      return NULL;
   }
   struct _block* curr = malloc(nmemb * size);
   memset(curr, 0, nmemb * size);
   
   return curr;
}

/* vim: set expandtab sts=3 sw=3 ts=6 ft=cpp: --------------------------------*/
