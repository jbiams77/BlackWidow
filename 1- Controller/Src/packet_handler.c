#include "packet_handler.h"
#include "main.h"
#include "port_handler.h"
#include "flash.h"

/* Fields -------------------------------------------------------------------*/
extern MessageQueue *message;

uint8_t messages[20][13];

uint8_t instruction;
uint8_t param[20];
uint8_t crc[2];
Stored_Parameters *stored_param;
Runtime_Parameters *runtime_param;
int delay_transmit_uS = 50;

/* Methods ------------------------------------------------------------------*/

void initialize_stored_parameters(void){
    stored_param->model_number = 1;
    // stored_param->model_information = 1;
    // stored_param->firmware_version = 1;
    // store_motor_ID(5);
    // stored_param->baud_rate = baud_115200;
    // TODO: finish initializing stored parametrs and set the param's by flash memory reads
}

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

    while (!isEmpty(message)){

        // shift one byte
        h1 = h2;
        h2 = h3;
        h3 = deQueue(message);
        header_block = (h1<<16) + (h2<<8) + (h3);
        if(header_block == 0xFFFFFD) {
            extract_message();
            break;
        }
    }
}






/* @brief After header block is found, extract reserved, id, length,
 * instruction, and message parameters.
 * 
 * @param void 
 * @return void
 */
void extract_message(){
    static uint8_t forensicCounter = 0;

    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

    uint8_t reserved = deQueue(message);
    uint8_t id = deQueue(message);
    uint8_t length1 = deQueue(message);
    uint8_t length2 = deQueue(message);
    uint16_t length = (length2 << 8) + (length1);
    instruction = deQueue(message);
    
    if (instruction != 0x01){
        __NOP();
    }
    
    // TODO: revisit if statement, originally prevented unligned message
    if (length<30){
        int i;
        // grab the parameters
        for (i=0; i< (length-3); i++){
            param[i] = deQueue(message);
        }
    }
    
    // grab CRC used for checking data loss
    crc[0] = deQueue(message);
    crc[1] = deQueue(message);

    messages[forensicCounter][0] = reserved;
    messages[forensicCounter][1] = id;
    messages[forensicCounter][2] = length1;
    messages[forensicCounter][3] = length2;
    messages[forensicCounter][4] = instruction;
    messages[forensicCounter][5] = crc[0];
    messages[forensicCounter][6] = crc[1];
    messages[forensicCounter][7] = 0x00;

    forensicCounter++;
    forensicCounter%=20;

    // TODO: fix memory ID storage
    // message fully received, proccess
    if (id==5 ){ // stored_param->motor_ID){
        process_instruction();
    }

    // if(forensicCounter == 19) {
    //     volatile int x = 100;
    //     x++;
    // }

}

/* @brief Execute the response for message.
 * 
 * @param void 
 * @return void
 */
void process_instruction(){

    // TODO: calculate delay time based on UART baud rate and set return delay time in parameters. 
    /* Important to have small delay to ensure master is ready to receive*/
    DWT_Delay(delay_transmit_uS);

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

#pragma region instructions

// TODO: finish instruction
void ping(){    

    uint8_t response[] = {0xFF, 0xFF, 0xFD, 0x00, 0x05, 0x07, 0x00, 0x55, 0x00, 0x06, 0x04, 0x26, 0x00, 0x00};
    uint16_t status_CRC = updateCRC(0, response, 12);
    response[12] = (uint8_t)(status_CRC & 0xFF);
    response[13] = (uint8_t)((status_CRC & 0xFF00)>>8);
    transmit_buffer(response, sizeof(response));
}

// TODO: finish instruction
void read(void){

    uint32_t read_address = (param[0]<<8) + param[1];
    //uint32_t read_size = pack_value();
    uint32_t read_value;

    switch (read_address){
        case MODEL_NUMBER: read_value = stored_param->model_number; break;
        case MODEL_INFORMATION:  read_value = stored_param->model_information; break;
        case FIRMWARE_VERSION:  read_value = stored_param->firmware_version; break;
        case ID:  read_value = stored_param->motor_ID; break;
        case BAUD_RATE:  read_value = stored_param->baud_rate; break;
        case RETURN_DELAY_TIME:  read_value = stored_param->return_delay_time; break;
        case DRIVE_MODE :  read_value = stored_param->drive_mode; break;
        case OPERATING_MODE:  read_value = stored_param->operating_mode; break;
        case SECONDARY_ID:  read_value = stored_param->secondary_ID; break;
        case PROTOCOL_TYPE:  read_value = stored_param->protocol_type; break;
        case HOMING_OFFSET:  read_value = stored_param->homing_offset; break;
        case MOVING_THRESHOLD:  read_value = stored_param->moving_threshold; break;
        case TEMPERATURE_LIMIT:  read_value = stored_param->temperature_limit; break;
        case MAX_VOLTAGE_LIMIT:  read_value = stored_param->max_voltage_limit; break;
        case MIN_VOLTAGE_LIMIT:  read_value = stored_param->min_voltage_limit; break;
        case PWM_LIMIT:  read_value = stored_param->PWM_limit; break;
        case VELOCITY_LIMIT:  read_value = stored_param->velocity_limit; break;
        case MAX_POSITION_LIMIT:  read_value = stored_param->max_position_limit; break;
        case MIN_POSITION_LIMIT:  read_value = stored_param->min_position_limit; break;
        case SHUTDOWN:  read_value = stored_param->shutdown; break;
        case TORQUE_ENABLE:  read_value = runtime_param->torque_enable; break;
        case LED:  read_value = runtime_param->led; break;
        case STATUS_RETURN_LEVEL:  read_value = runtime_param->status_return_level; break;
        case REGISTERED_INSTRUCTION:  read_value = runtime_param->registered_instruction; break;
        case HARDWARE_ERROR_STATUS:  read_value = runtime_param->hardware_error_status; break;
        case VELOCITY_I_GAIN:  read_value = runtime_param->velocity_I_gain; break;
        case VELOCITY_P_GAIN:  read_value = runtime_param->velocity_P_gain; break;
        case POSITION_D_GAIN:  read_value = runtime_param->position_D_gain; break;
        case POSITION_I_GAIN:  read_value = runtime_param->position_I_gain; break;
        case POSITION_P_GAIN:  read_value = runtime_param->position_P_gain; break;
        case FEEDFORWARD_2ND_GAIN:  read_value = runtime_param->feedforward_2nd_gain; break;
        case FEEDFORWARD_1ST_GAIN:  read_value = runtime_param->feedforward_1st_gain; break;
        case BUS_WATCHDOG:  read_value = runtime_param->BUS_watchdog; break;
        case GOAL_PWM:  read_value = runtime_param->goal_PWM; break;
        case GOAL_VELOCITY:  read_value = runtime_param->goal_velocity; break;
        case PROFILE_ACCELERATION:  read_value = runtime_param->profile_accelration; break;
        case PROFILE_VELOCITY:  read_value = runtime_param->profile_velocity; break;
        case GOAL_POSITION:  read_value = runtime_param->goal_position; break;
        case REALTIME_TICK:  read_value = runtime_param->realtime_tick; break;
        case MOVING:  read_value = runtime_param->moving_status; break;
        case MOVING_STATUS:  read_value = runtime_param->moving_status; break;
        case PRESENT_PWM:  read_value = runtime_param->present_PWM; break;
        case PRESENT_LOAD:  read_value = runtime_param->present_load; break;
        case PRESENT_VELOCITY:  read_value = runtime_param->present_velocity; break;
        case PRESENT_POSITION:  read_value = runtime_param->present_position; break;
        case VELOCITY_TRAJECTORY:  read_value = runtime_param->velocity_trajectory; break;
        case POSITION_TRAJECTORY:  read_value = runtime_param->position_trajectory; break;
        case PRESENT_INPUT_VOLTAGE:  read_value = runtime_param->present_input_voltage; break;
        case PRESENT_TEMPERATURE:  read_value = runtime_param->present_temperature; break;
    }

    uint8_t array_size = 10 + sizeof(param);
    uint8_t packet_length = 3 + sizeof(param);
    // send the read value on transmit line
    uint8_t status_packet[array_size];

    status_packet[HEADER1] = 0xFF;
    status_packet[HEADER2] = 0xFF;
    status_packet[HEADER3] = 0xFD;
    status_packet[RSRVD] = 0x00;
    status_packet[PACKET_ID] = stored_param->motor_ID;
    status_packet[LENGTH_LOW] = packet_length;
    status_packet[LENGTH_HIGH] = 0x00;
    status_packet[7] = STATUS;

    // TODO: finish the status packet...

}

/* @brief Writes value to control table.
 *
 * @param void 
 * @return void
 */
void write(void){
    
    /* Pack parameter */
    uint16_t write_address = (param[0]<<8) + param[1];
    uint32_t value = get_value_from_param();

    /* parameter addresses less than 64 write to flash */
    if (write_address >= 64){

        write_to_RAM(write_address, value);

    } else if (write_address < 64 && !runtime_param->torque_enable){

        write_to_Flash(write_address, value);

    }     
    
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

#pragma endregion

#pragma region runtime_memory

void write_to_RAM(uint16_t address, uint32_t value){

        switch (address){
        case TORQUE_ENABLE:
            runtime_param->torque_enable = (uint8_t)value;
            break;
        case LED:   
            runtime_param->led = value;
            break;
        case STATUS_RETURN_LEVEL:   
            runtime_param->status_return_level = (uint8_t)value;
            break;
        case VELOCITY_I_GAIN :   
            runtime_param->velocity_I_gain = value;
            break;
        case VELOCITY_P_GAIN:
            runtime_param->velocity_P_gain = value;
            break;
        case POSITION_D_GAIN:
            runtime_param->position_D_gain = value;
            break;
        case POSITION_I_GAIN:   
            runtime_param->position_I_gain = value;
            break;
        case POSITION_P_GAIN:
            runtime_param->position_P_gain = value;
            break;
        case FEEDFORWARD_2ND_GAIN:
            runtime_param->feedforward_1st_gain = value;
            break;
        case FEEDFORWARD_1ST_GAIN:
            runtime_param->feedforward_2nd_gain = value;
           break;
        case BUS_WATCHDOG:
            runtime_param->BUS_watchdog = (uint8_t)value;
           break;
        case GOAL_PWM:   
            runtime_param->goal_PWM = (uint16_t)value;
            break;
        case GOAL_VELOCITY:
            runtime_param->goal_velocity = value;
            break;
        case PROFILE_ACCELERATION:   
            runtime_param->profile_accelration = value;
            break;
        case PROFILE_VELOCITY:
            runtime_param->profile_velocity = value;
            break;
        case GOAL_POSITION:   
            runtime_param->goal_position = value;        
            break;
        case REALTIME_TICK:
            runtime_param->realtime_tick = (uint16_t)value;
            break;
    }

}

#pragma endregion

#pragma region flash_memory_functions

void write_to_Flash(uint16_t address, uint32_t value){
    
    switch (address){        
        case ID: store_motor_ID(value); break;
        case BAUD_RATE: store_baud_rate(value); break;
        case RETURN_DELAY_TIME: store_return_delay_time(value);break;
        case DRIVE_MODE: store_drive_mode(value);break;
        case OPERATING_MODE: store_operating_mode(value); break;
        case SECONDARY_ID: store_secondary_ID(value); break;
        case PROTOCOL_TYPE: store_protocol_type(value);break;
        case HOMING_OFFSET: store_homing_offset(value); break;
        case MOVING_THRESHOLD: store_moving_threshold(value); break;
        case TEMPERATURE_LIMIT: store_temperature_limit(value); break;
        case MAX_VOLTAGE_LIMIT: store_max_voltage_limit(value); break;
        case MIN_VOLTAGE_LIMIT: store_min_voltage_limit(value); break;
        case PWM_LIMIT: store_PWM_limit(value); break;
        case VELOCITY_LIMIT: store_velocity_limit(value); break;
        case MAX_POSITION_LIMIT: store_max_position_limit(value); break;
        case MIN_POSITION_LIMIT: store_min_position_limit(value); break;
        case SHUTDOWN: store_shutdown(value); break;
    }

}

// TODO: manage various data size types in flash.c and address to ensure 
//       everything currently is set to unit8_t

/*------Stored Parameters FUNCTION PROTOTYPES---------------------------*/

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_motor_ID(uint8_t value){

    stored_param->motor_ID = value;
    //Flash_Write(ID_ADDRESS, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_baud_rate(uint32_t value){

    stored_param->baud_rate = value;
    Flash_Write(BAUD_RATE_ADDRESS, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_return_delay_time(uint32_t value){

    stored_param->return_delay_time = value;
    Flash_Write(RETURN_DELAY_TIME_ADDRESS, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_drive_mode(uint32_t value){

    stored_param->drive_mode = value;
    Flash_Write(DRIVE_MODE_ADDRESS, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_operating_mode(uint32_t value){

    stored_param->operating_mode = value;
    Flash_Write( OPERATING_MODE_ADDRESS, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_secondary_ID(uint32_t value){

    stored_param->secondary_ID = value;
    Flash_Write(SECONDARY_ID_ADDRESS, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_protocol_type(uint32_t value){

    stored_param->protocol_type = value;
    Flash_Write(PROTOCOL_TYPE_ADDRESS, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_homing_offset(uint32_t value){

    stored_param->homing_offset = value;
    Flash_Write(HOMING_OFFSET_ADDRESS, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_moving_threshold(uint32_t value){

    stored_param->moving_threshold = value;
    Flash_Write(MOVING_THRESHOLD_ADDRESS, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_temperature_limit(uint32_t value){

    stored_param->temperature_limit = value;
    Flash_Write(TEMPERATURE_LIMIT_ADDRESS, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_min_voltage_limit(uint32_t value){

    stored_param->min_voltage_limit = value;
    Flash_Write(MIN_VOLTAGE_LIMIT_ADDRESS, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_max_voltage_limit(uint32_t value){

    stored_param->max_voltage_limit = value;
    Flash_Write(MAX_VOLTAGE_LIMIT_ADDRESS, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_PWM_limit(uint32_t value){

    stored_param->PWM_limit = value;
    Flash_Write(PWM_LIMIT, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_velocity_limit(uint32_t value){

    stored_param->velocity_limit = value;
    Flash_Write(VELOCITY_LIMIT, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_min_position_limit(uint32_t value){

    stored_param->min_position_limit = value;
    Flash_Write(MIN_POSITION_LIMIT, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_max_position_limit(uint32_t value){

    stored_param->max_position_limit = value;
    Flash_Write(MAX_POSITION_LIMIT, value);

}

/* Stores value to memory, available after
 * power cycle.
 * @param value to store
 * @return void
 */
void store_shutdown(uint32_t value){

    stored_param->shutdown = value;
    Flash_Write(SHUTDOWN, value);

}
#pragma endregion 

/* @brief Retrieves value by packing the bits from message
 *        parameters.
 *
 * @param void 
 * @return uint32_t packed message parameter value
 */
uint32_t get_value_from_param(void){
    uint32_t value=0;
    /* Pack value */
    int i;
    int bit_shift = 0;
    for ( i=2; i<sizeof(param)-3; i++){
        value += (param[i] << bit_shift);
        bit_shift += 8;
    }
    return value;
}

unsigned short updateCRC(uint16_t crc_accum, uint8_t *data_blk_ptr, uint16_t data_blk_size)
{
  uint16_t i;
  static const uint16_t crc_table[256] = {0x0000,
  0x8005, 0x800F, 0x000A, 0x801B, 0x001E, 0x0014, 0x8011,
  0x8033, 0x0036, 0x003C, 0x8039, 0x0028, 0x802D, 0x8027,
  0x0022, 0x8063, 0x0066, 0x006C, 0x8069, 0x0078, 0x807D,
  0x8077, 0x0072, 0x0050, 0x8055, 0x805F, 0x005A, 0x804B,
  0x004E, 0x0044, 0x8041, 0x80C3, 0x00C6, 0x00CC, 0x80C9,
  0x00D8, 0x80DD, 0x80D7, 0x00D2, 0x00F0, 0x80F5, 0x80FF,
  0x00FA, 0x80EB, 0x00EE, 0x00E4, 0x80E1, 0x00A0, 0x80A5,
  0x80AF, 0x00AA, 0x80BB, 0x00BE, 0x00B4, 0x80B1, 0x8093,
  0x0096, 0x009C, 0x8099, 0x0088, 0x808D, 0x8087, 0x0082,
  0x8183, 0x0186, 0x018C, 0x8189, 0x0198, 0x819D, 0x8197,
  0x0192, 0x01B0, 0x81B5, 0x81BF, 0x01BA, 0x81AB, 0x01AE,
  0x01A4, 0x81A1, 0x01E0, 0x81E5, 0x81EF, 0x01EA, 0x81FB,
  0x01FE, 0x01F4, 0x81F1, 0x81D3, 0x01D6, 0x01DC, 0x81D9,
  0x01C8, 0x81CD, 0x81C7, 0x01C2, 0x0140, 0x8145, 0x814F,
  0x014A, 0x815B, 0x015E, 0x0154, 0x8151, 0x8173, 0x0176,
  0x017C, 0x8179, 0x0168, 0x816D, 0x8167, 0x0162, 0x8123,
  0x0126, 0x012C, 0x8129, 0x0138, 0x813D, 0x8137, 0x0132,
  0x0110, 0x8115, 0x811F, 0x011A, 0x810B, 0x010E, 0x0104,
  0x8101, 0x8303, 0x0306, 0x030C, 0x8309, 0x0318, 0x831D,
  0x8317, 0x0312, 0x0330, 0x8335, 0x833F, 0x033A, 0x832B,
  0x032E, 0x0324, 0x8321, 0x0360, 0x8365, 0x836F, 0x036A,
  0x837B, 0x037E, 0x0374, 0x8371, 0x8353, 0x0356, 0x035C,
  0x8359, 0x0348, 0x834D, 0x8347, 0x0342, 0x03C0, 0x83C5,
  0x83CF, 0x03CA, 0x83DB, 0x03DE, 0x03D4, 0x83D1, 0x83F3,
  0x03F6, 0x03FC, 0x83F9, 0x03E8, 0x83ED, 0x83E7, 0x03E2,
  0x83A3, 0x03A6, 0x03AC, 0x83A9, 0x03B8, 0x83BD, 0x83B7,
  0x03B2, 0x0390, 0x8395, 0x839F, 0x039A, 0x838B, 0x038E,
  0x0384, 0x8381, 0x0280, 0x8285, 0x828F, 0x028A, 0x829B,
  0x029E, 0x0294, 0x8291, 0x82B3, 0x02B6, 0x02BC, 0x82B9,
  0x02A8, 0x82AD, 0x82A7, 0x02A2, 0x82E3, 0x02E6, 0x02EC,
  0x82E9, 0x02F8, 0x82FD, 0x82F7, 0x02F2, 0x02D0, 0x82D5,
  0x82DF, 0x02DA, 0x82CB, 0x02CE, 0x02C4, 0x82C1, 0x8243,
  0x0246, 0x024C, 0x8249, 0x0258, 0x825D, 0x8257, 0x0252,
  0x0270, 0x8275, 0x827F, 0x027A, 0x826B, 0x026E, 0x0264,
  0x8261, 0x0220, 0x8225, 0x822F, 0x022A, 0x823B, 0x023E,
  0x0234, 0x8231, 0x8213, 0x0216, 0x021C, 0x8219, 0x0208,
  0x820D, 0x8207, 0x0202 };

  for (uint16_t j = 0; j < data_blk_size; j++)
  {
    i = ((uint16_t)(crc_accum >> 8) ^ *data_blk_ptr++) & 0xFF;
    crc_accum = (crc_accum << 8) ^ crc_table[i];
  }

  return crc_accum;
}


