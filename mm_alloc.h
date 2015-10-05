/*
 * mm_alloc.h
 *
 * Exports a clone of the interface documented in "man 3 malloc".
 */

#pragma once

#ifndef _malloc_H_
#define _malloc_H_

 /* Define the block size since the sizeof will be wrong */
#define BLOCK_SIZE 40

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
void *bse;

void* mm_malloc(size_t size);
void* mm_realloc(void* ptr, size_t size);
void mm_free(void* ptr);


typedef struct s_block *s_block_ptr;

/* block struct */
struct s_block {
    size_t size;
    struct s_block *next;
    struct s_block *prev;
    int free;
    void *ptr;
    
    char data [0];
 };



void split_block(s_block_ptr b, size_t s){

s_block_ptr first;
first = b->data + s;
first->size = b->size - s - BLOCK_SIZE;
first->next = b->next;
first->free = 1;
b->size = s;
b->next = first;
}

s_block_ptr find_block(s_block_ptr *last, size_t size){
bse = NULL;
s_block_ptr bee = bse;
while(bee && !(bee->free && bee->size >= size)) {
*last = bee;
bee = bee->next;
}
return (bee);
}




s_block_ptr fusion(s_block_ptr b){
if(b->next && b->next->free){
b->size += BLOCK_SIZE + b->next->size;
b->next = b->next->next;
if (b->next)
b->next->prev = b;
}
return (b);
}






s_block_ptr get_block(void *p)
{
char *tempo;
tempo = p;
return (p = tempo -= BLOCK_SIZE);
}

void copy_block(s_block_ptr src, s_block_ptr dst)

{
int *sdt,*ddt;
size_t j;
sdt = src->ptr;
ddt = dst->ptr;
for(j=0; j*4<src->size && j*4<dst->size; j++)
ddt[j] = sdt[j];
}


s_block_ptr extend_heap(s_block_ptr last, size_t s)
{

s_block_ptr b;
b =sbrk(0);
if(sbrk(BLOCK_SIZE + s) == (void*)-1)
return (NULL);
b->size = s;
b->next = NULL;
if (last)
last->next = b;
b->free = 0;
return (b);
}


int valid_addr(void *p)
{
bse = NULL;
if(bse)
{
if( p>bse && p<sbrk(0))
{
return(p == (get_block(p))->ptr);
}
}
return (0);
}





#ifdef __cplusplus
}
#endif

#endif
