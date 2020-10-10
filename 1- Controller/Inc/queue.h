#include <stdint.h>
#include <stdlib.h>


#ifndef __QUEUE_H_
#define __QUEUE_H_

#define TRUE    1
#define FALSE	0
#define SIZE   200

typedef struct Parameters{
  int ID;
  int BAUD;
} Parameters;


/* the HEAD of the MessageQueue, hold the amount of node's that are in the queue*/
typedef struct MessageQueue { 
    uint8_t message[SIZE];
    int front; 
    int rear;     
} MessageQueue;


int enQueue(MessageQueue*, uint8_t);
uint8_t deQueue(MessageQueue*);
int isEmpty(MessageQueue*);
int isFull(MessageQueue*);
uint8_t peek(MessageQueue*);
int next(MessageQueue*);
int nextFront(MessageQueue*);


#endif
