/*Mohamed Zayyan Variawa- please dont steal my code*/
/*
 * mm_alloc.c
 *
 * Stub implementations of the mm_* routines.
 
 	My malloc funtion works as follows:
	•If the bse is initialized:
	-Search for a free memory chunk which is the right size (using the find_block function);
	-If we find a memory chunk;
	*Try to split the memory block (using the split_block function);
	*Mark the memory chunk as used (c->free=0);
	-Otherwise: we extend the heap (call the extend_heap function).
	Note the use of the last:find_block put the pointer to the last visited chunk in
	last,so we can access it during the extension without traversing the whole list
	again.
	•Otherwise: we extended the heap (use extend_heap (which is empty at that point).	 
 
 
 
 */


#include "mm_alloc.h"

#include <stdlib.h>
void *bse;

void* mm_malloc(size_t size)
{
//#ifdef MM_USE_STUBS
//#else
bse=NULL;

s_block_ptr c,last;
size_t s;
s = size;
if (bse) {
last = bse;
c = find_block(&last,s);
if (c) {
if ((c->size - s) >= (BLOCK_SIZE + 4))
split_block(c,s);
c->free=0;
}
else
{
c = extend_heap(last,s);
if (!c)
return (NULL);
}
}
else
{
c = extend_heap(NULL,s);
if (!c)
return (NULL);
bse = c;
}
return calloc(1, size);
//#endif
}

void* mm_realloc(void* ptr, size_t size)
{
//#ifdef MM_USE_STUBS
//#else
size_t sze;
s_block_ptr bee, new;
void *newp;
if (!ptr)
return (malloc(size));
if (valid_addr(ptr))
{
sze = size; 
bee = get_block(ptr);
if (bee->size >= sze)
{
if (bee->size - sze >= (BLOCK_SIZE + 4))
split_block(bee,sze);
}
else
{
if (bee->next && bee->next->free && (bee->size + BLOCK_SIZE + bee->next->size) >= sze)
{
fusion(bee);
if (bee->size - sze >= (BLOCK_SIZE + 4))
split_block(bee,sze);
}
else
{
newp = malloc(sze);
if (!newp)
return (NULL);
new = get_block(newp);
copy_block(bee,new);
free(ptr);
return (newp);
}
}
return (ptr);
}
return (NULL);

return realloc(ptr, size);
//#endif
}

void mm_free(void* ptr)
{
/*#ifdef MM_USE_STUBS


#else*/
bse=NULL;
s_block_ptr bee;
if (valid_addr(ptr))
{
bee = get_block(ptr);
bee->free = 1;
if (bee->prev && bee->prev->free)
bee = fusion(bee->prev);
if (bee->next)
fusion(bee);
else
{
if (bee->prev)
bee->prev->next = NULL;
else
bse = NULL;
brk(bee);
}

}
 free(ptr);
//#endif
}
