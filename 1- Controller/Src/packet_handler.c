#include "packet_handler.h"
#include "main.h"
#include "port_handler.h"
#include "flash.h"

/* Fields -------------------------------------------------------------------*/
extern MessageQueue *message;
uint8_t instruction;
uint8_t param[20];
uint8_t crc[2];
extern Stored_Parameters *stored_param;
int delay_transmit_uS = 50;

/* Methods ------------------------------------------------------------------*/

/* @brief Moves through queue to look for header block.
 * 
 * @param void 
 * @return void
 */
void process_queue(){

    // header
    uint8_t h1 = 0;
    uint8_t h2 = 0;
    uint8_t h3 = 0;
    uint32_t header_block=0;
    uint8_t header_block_found = 0;

    while (!header_block_found && !isEmpty(message)){

        // shift one byte
        h1 = h2;
        h2 = h3;
        h3 = deQueue(message);
        header_block = (h1<<16) + (h2<<8) + (h3);
        if(header_block == 0xFFFFFD){
            header_block_found = 1;
        }
    }
    
    if (header_block_found){
        extract_message();
    }

}

/* @brief After header block is found, extract reserved, id, length,
 * instruction, and message parameters.
 * 
 * @param void 
 * @return void
 */
void extract_message(){

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
    if (id==stored_param->motor_ID){
        process_message();
    }

}

/* @brief Execute the response for message.
 * 
 * @param void 
 * @return void
 */
void process_message(){

    // TODO: calculate delay time based on UART baud rate and set return delay time in parameters. 
    /* Important to have small delay to ensure master is ready to receive*/
    DWT_Delay(delay_transmit_uS);
    delay_transmit_uS += 50;

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

// TODO: finish instruction
void ping(){    
    uint8_t response[] = {0xFF, 0xFF, 0xFD, 0x00, 0x01, 0x07, 0x00, 0x55, 0x00, 0x06, 0x04, 0x26, 0x65, 0x5D};
    transmit_buffer(response, sizeof(response));
}

// TODO: finish instruction
void read(void){

}

// TODO: finish instruction
void write(void){

}

// TODO: finish instruction
void reg_write(void){
    
}

// TODO: finish instruction
void action(void){
    
}

// TODO: finish instruction
void factory_reset(void){
    
}

// TODO: finish instruction
void reboot(void){
    
}

// TODO: finish instruction
void clear(void){
    
}

// TODO: finish instruction
void status(void){
    
}

// TODO: finish instruction
void sync_read(void){
    
}

// TODO: finish instruction
void sync_write(void){
    
}

// TODO: finish instruction
void bulk_read(void){
    
}

// TODO: finish instruction
void bulk_write(void){
    
}

/*------Stored Parameters FUNCTION PROTOTYPES---------------------------*/

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_model_number(uint8_t value){

    stored_param->model_number = value;
    Flash_Write(MODEL_NUMBER_ADDRESS, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_firmware_version(uint8_t value){

    stored_param->firmware_version = value;
    Flash_Write(FIRMWARE_VERSION_ADDRESS, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_motor_ID(uint8_t value){

    stored_param->motor_ID = value;
    Flash_Write(ID_ADDRESS, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_baud_rate(uint8_t value){

    stored_param->baud_rate = value;
    Flash_Write(BAUD_RATE_ADDRESS, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_return_delay_time(uint8_t value){

    stored_param->return_delay_time = value;
    Flash_Write(RETURN_DELAY_TIME_ADDRESS, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_drive_mode(uint8_t value){

    stored_param->drive_mode = value;
    Flash_Write(DRIVE_MODE_ADDRESS, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_operating_mode(uint8_t value){

    stored_param->operating_mode = value;
    Flash_Write( OPERATING_MODE_ADDRESS, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_secondary_ID(uint8_t value){

    stored_param->secondary_ID = value;
    Flash_Write(SECONDARY_ID_ADDRESS, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_protocol_type(uint8_t value){

    stored_param->protocol_type = value;
    Flash_Write(PROTOCOL_TYPE_ADDRESS, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_homing_offset(uint8_t value){

    stored_param->homing_offset = value;
    Flash_Write(HOMING_OFFSET_ADDRESS, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_moving_threshold(uint8_t value){

    stored_param->moving_threshold = value;
    Flash_Write(MOVING_THRESHOLD_ADDRESS, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_temperature_limit(uint8_t value){

    stored_param->temperature_limit = value;
    Flash_Write(TEMPERATURE_LIMIT_ADDRESS, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_min_voltage_limit(uint8_t value){

    stored_param->min_voltage_limit = value;
    Flash_Write(MIN_VOLTAGE_LIMIT_ADDRESS, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_max_voltage_limit(uint8_t value){

    stored_param->max_voltage_limit = value;
    Flash_Write(MAX_VOLTAGE_LIMIT_ADDRESS, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_PWM_limit(uint8_t value){

    stored_param->PWM_limit = value;
    Flash_Write(PWM_LIMIT, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_velocity_limit(uint8_t value){

    stored_param->velocity_limit = value;
    Flash_Write(VELOCITY_LIMIT, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_min_position_limit(uint8_t value){

    stored_param->min_position_limit = value;
    Flash_Write(MIN_POSITION_LIMIT, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_max_position_limit(uint8_t value){

    stored_param->max_position_limit = value;
    Flash_Write(MAX_POSITION_LIMIT, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_shutdown(uint8_t value){

    stored_param->shutdown = value;
    Flash_Write(SHUTDOWN, value);

}

