#pragma once
#include "utility.h"

#define TRUE    1
#define FALSE	0
#define SIZE   256


/* the HEAD of the MessageQueue, hold the amount of node's that are in the queue*/
typedef struct MessageQueue { 
    uint8_t message[SIZE];
    int front; 
    int rear;     
} MessageQueue;

MessageQueue* constructMessage();
int enQueue(MessageQueue*, uint8_t);
uint8_t deQueue(MessageQueue*);
int isEmpty(MessageQueue*);
int isFull(MessageQueue*);
uint8_t peek(MessageQueue*);
int nextRear(MessageQueue*);
int nextFront(MessageQueue*);



