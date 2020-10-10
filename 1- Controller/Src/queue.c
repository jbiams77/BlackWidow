#include "queue.h"

Parameters* initializeParameters(int id, int baud){
  Parameters *param = (Parameters*) malloc(sizeof(Parameters));
  param->ID = id;
  param->BAUD = baud;
  return param;
}


MessageQueue* constructMessage(){
    MessageQueue *queue = (MessageQueue*) malloc(sizeof (MessageQueue)); 
    int i;
    queue->front = -1;
    queue->rear = 0;
    for (i=0; i<SIZE; i++){
        queue->message[i] = 0;    
    }
    return queue;
}


int enQueue(MessageQueue *queue, uint8_t data){
    if(isEmpty(queue)){
        queue->front = queue->rear;
        queue->message[queue->rear] = data;
        return TRUE;
    } else if (isFull(queue)){
        return FALSE;
    } else {
        queue->rear = nextRear(queue);
        queue->message[queue->rear] = data;
        return TRUE;
    }
}


uint8_t deQueue(MessageQueue *queue){
    if(isEmpty(queue)){
        return 253;
    } else if (queue->front==queue->rear){
        uint8_t temp = queue->message[queue->front];
        queue->front = -1;
        return temp;
    } else {
        uint8_t temp = queue->message[queue->front];
        queue->front = nextFront(queue);
        return temp;
    }
}

uint8_t peek(MessageQueue *queue){
    return queue->message[queue->front];
}

int isEmpty(MessageQueue *queue){
    if(queue->front == -1){
        return TRUE;    
    }
    return FALSE;
}

int isFull(MessageQueue *queue){
    if(nextRear(queue)==queue->front){
        return TRUE;
    }
    return FALSE;
}

int nextRear(MessageQueue *queue){
    return (queue->rear + 1) % SIZE;
}

int nextFront(MessageQueue *queue){
    return (queue->front + 1) % SIZE;
}
