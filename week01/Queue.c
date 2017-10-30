// ADT for a FIFO queue
// COMP1521 17s2 Week01 Lab Exercise
// Written by John Shepherd, July 2017
// Modified by ...

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Queue.h"

typedef struct QueueNode {
   int jobid;  // unique job ID
   int size;   // size/duration of job
   struct QueueNode *next;
} QueueNode;

struct QueueRep {
   int nitems;      // # of nodes
   QueueNode *head; // first node
   QueueNode *tail; // last node
};

// TODO:
// remove the #if 0 and #endif
// once you've added code to use this function

// create a new node for a Queue
static
QueueNode *makeQueueNode(int id, int size)
{
   QueueNode *new;
   new = malloc(sizeof(struct QueueNode));
   assert(new != NULL);
   new->jobid = id;
   new->size = size;
   new->next = NULL;
   return new;
}


// make a new empty Queue
Queue makeQueue()
{
   Queue new;
   new = malloc(sizeof(struct QueueRep));
   assert(new != NULL);
   new->nitems = 0; new->head = new->tail = NULL;
   return new;
}

// release space used by Queue
void  freeQueue(Queue q)
{
   assert(q != NULL);
   QueueNode *curr = q->head;
   QueueNode *a;
   while (curr != NULL) {
   		a = curr->next;
   		free(curr);
   		curr = a;
   }
   free(q);
}

// add a new item to tail of Queue
void  enterQueue(Queue q, int id, int size)
{
   assert(q != NULL);
   QueueNode *n = makeQueueNode(id, size);
   if (q->head == NULL) {
   		q->head = n;
   } else {
   		q->tail->next = n;
   }
   q->tail = n;
   q->nitems++;
}

// remove item on head of Queue
int  leaveQueue(Queue q)
{
   assert(q != NULL);
   assert(q->nitems > 0); 
   QueueNode *a = q->head;
   int id = a->jobid;
   q->head = a->next;
   if (q->head == NULL) q->tail == NULL;
   free(a);
   q->nitems--;

   return id;  
}

// count # items in Queue
int   lengthQueue(Queue q)
{
   assert(q != NULL);
   return q->nitems;
}

// return total size in all Queue items
int   volumeQueue(Queue q)
{
   assert(q != NULL);
   QueueNode *a = q->head;
   int sum = 0;
   while (a != NULL) {
   		sum = sum + a->size;
   		a = a->next;
   }
   return sum;
}

// return size/duration of first job in Queue
int   nextDurationQueue(Queue q)
{
   assert(q != NULL);
   if (q->head == NULL) {

   		return 0;
   } else {

   		return q->head->size;
   }
}


// display jobid's in Queue
void showQueue(Queue q)
{
   QueueNode *curr;
   curr = q->head;
   while (curr != NULL) {
      printf(" (%d,%d)", curr->jobid, curr->size);
      curr = curr->next;
   }
}
