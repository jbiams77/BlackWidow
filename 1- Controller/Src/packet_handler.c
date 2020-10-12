#include "packet_handler.h"
#include "main.h"
#include "port_handler.h"




void process_queue(){

    // header
    uint8_t h1 = 0;
    uint8_t h2 = 0;
    uint8_t h3 = 0;
    uint32_t header_block=0;
    uint8_t found = 0;

    //REVIEW: review shift and clear cache
    // find 0xFFFFFD by dequeing 3 bytes and shifting until match is met
    while (!found && !isEmpty(message)){

        // shift one byte
        h1 = h2;
        h2 = h3;
        h3 = deQueue(message);
        header_block = (h1<<16) + (h2<<8) + (h3);
        if(header_block == 0xFFFFFD){
            found = 1;
        }

    }
    if (found){
        
        uint8_t reserved = deQueue(message);
        uint8_t id = deQueue(message);
        uint8_t length1 = deQueue(message);
        uint8_t length2 = deQueue(message);
        uint16_t length = (length2 << 8) + (length1);
        instruction = deQueue(message);
        int i;
        if(length<10){
            // grab the parameters
            for (i=0; i< (length-3); i++){
                param[i] = deQueue(message);
            }
        }
        // grab CRC used for checking data loss
        crc[0] = deQueue(message);
        crc[1] = deQueue(message);

        // message fully received, proccess
        if (id==PARAM->ID){
            process_message(length);
        }
    }
}

void process_message(uint16_t length){

    switch (instruction){
        case PING: ping(); break;
        case READ : read(); break;
        case WRITE : write(); break;
        case REG_WRITE : reg_write(); break;
        case ACTION : action(); break;
        case FACTORY_RESET : factory_reset(); break;        
        case REBOOT : reboot(); break;
        case CLEAR  : clear(); break;
        case STATUS  : status(); break;
        case SYNC_READ  : sync_read(); break;
        case SYNC_WRITE  : sync_write(); break;
        case BULK_READ  : bulk_read(); break;
        case BULK_WRITE  : bulk_write(); break;
    }

}

void ping(){
    uint8_t response[4] = {0xFF, 0xFF, 0xFF, 0xFF};
    //transmit_buffer(response, sizeof(response));
}

void read(void){

}

void write(void){

}

void reg_write(void){
    int i;
    for (i=0;i<REG_WRITE;i++){
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, HIGH);
        HAL_Delay(50);
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, LOW);
        HAL_Delay(50);
    }
}

void action(void){
    int i;
    for (i=0;i<ACTION;i++){
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, HIGH);
        HAL_Delay(50);
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, LOW);
        HAL_Delay(50);
    }
}

void factory_reset(void){
    int i;
    for (i=0;i<FACTORY_RESET;i++){
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, HIGH);
        HAL_Delay(50);
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, LOW);
        HAL_Delay(50);
    }
}

void reboot(void){
    int i;
    for (i=0;i<REBOOT;i++){
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, HIGH);
        HAL_Delay(50);
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, LOW);
        HAL_Delay(50);
    }
}

void clear(void){
    int i;
    for (i=0;i<CLEAR;i++){
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, HIGH);
        HAL_Delay(50);
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, LOW);
        HAL_Delay(50);
    }
}

void status(void){
    int i;
    for (i=0;i<STATUS;i++){
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, HIGH);
        HAL_Delay(50);
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, LOW);
        HAL_Delay(50);
    }
}

void sync_read(void){
    int i;
    for (i=0;i<SYNC_READ;i++){
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, HIGH);
        HAL_Delay(50);
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, LOW);
        HAL_Delay(50);
    }
}

void sync_write(void){
    int i;
    for (i=0;i<SYNC_WRITE;i++){
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, HIGH);
        HAL_Delay(50);
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, LOW);
        HAL_Delay(50);
    }
}

void bulk_read(void){
    int i;
    for (i=0;i<BULK_READ;i++){
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, HIGH);
        HAL_Delay(50);
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, LOW);
        HAL_Delay(50);
    }
}

void bulk_write(void){
    int i;
    for (i=0;i<BULK_WRITE;i++){
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, HIGH);
        HAL_Delay(50);
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, LOW);
        HAL_Delay(50);
    }
}

