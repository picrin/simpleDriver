#ifndef __BOUNDED_BUFFER_HDR
#define __BOUNDED_BUFFER_HDR

/*
 * BoundedBuffer.h
 *
 * Header file for a bounded buffer implemented using pthread
 * facilities to allow it to be driven by concurrent threads.
 *
 * Uses standard tricks to keep it very generic.
 * Uses heap allocated data structures.
 *
 * Author: Peter Dickman
 *
 * Created: 7-3-2000
 * Edited:  28-2-2001
 *
 * Version: 1.1
 *
 */

typedef  void *    BoundedBuffer;
typedef  void *    BufferedItem;

typedef  unsigned int   Length;


BoundedBuffer createBB(Length);
void          destroyBB(BoundedBuffer);

void          blockingWriteBB(BoundedBuffer, BufferedItem);
BufferedItem  blockingReadBB(BoundedBuffer);

int     nonblockingWriteBB(BoundedBuffer, BufferedItem);
int     nonblockingReadBB(BoundedBuffer, BufferedItem *);

void          mapBB(BoundedBuffer, void (*mapFunction)(BufferedItem));

#endif
