#include <stdint.h>
#include <stdlib.h>
#include "queue.h"

#ifndef __PACKET_HANDLER_H_
#define __PACKET_HANDLER_H_

#define HIGH GPIO_PIN_SET
#define LOW GPIO_PIN_RESET

#define BUFFER_SIZE 8
#define HEADER1 0
#define HEADER2 1
#define HEADER3 2
#define RSRVD 3
#define PACKET_ID  4
#define LENGTH_LOW 5
#define LENGTH_HIGH 6

#define PING 1
#define READ 2
#define WRITE 3
#define REG_WRITE 4
#define ACTION 5
#define FACTORY_RESET 6
#define REBOOT 8
#define CLEAR 10
#define STATUS 55
#define SYNC_READ 82
#define SYNC_WRITE 83
#define BULK_READ 92
#define BULK_WRITE 93

// Dynamixel Communication 2.0 writable settings
#define MODEL_NUMBER 0
#define MODEL_INFORMATION 2
#define FIRMWARE_VERSION 6
#define ID 7
#define BAUD_RATE 8
#define RETURN_DELAY_TIME 9
#define DRIVE_MODE 10 
#define OPERATING_MODE 11 
#define SECONDARY_ID 12
#define PROTOCOL_TYPE 13 
#define HOMING_OFFSET 20 
#define MOVING_THRESHOLD 24 
#define TEMPERATURE_LIMIT 31 
#define MAX_VOLTAGE_LIMIT 32
#define MIN_VOLTAGE_LIMIT 34
#define PWM_LIMIT 36 
#define VELOCITY_LIMIT 44
#define MAX_POSITION_LIMIT 48
#define MIN_POSITION_LIMIT 52
#define SHUTDOWN 63

// Dynamixel Communication 2.0 RAM Area

#define TORQUE_ENABLE 64
#define LED 65
#define STATUS_RETURN_LEVEL 68
#define REGISTERED_INSTRUCTION 69
#define HARDWARE_ERROR_STATUS 70
#define VELOCITY_I_GAIN 76
#define VELOCITY_P_GAIN 78
#define POSITION_D_GAIN 80
#define POSITION_I_GAIN 82
#define POSITION_P_GAIN 84
#define FEEDFORWARD_2ND_GAIN 88
#define FEEDFORWARD_1ST_GAIN 90
#define BUS_WATCHDOG 98
#define GOAL_PWM 100
#define GOAL_VELOCITY 104
#define PROFILE_ACCELERATION 108
#define PROFILE_VELOCITY 112
#define GOAL_POSITION 116
#define REALTIME_TICK 120
#define MOVING 122
#define MOVING_STATUS 123
#define PRESENT_PWM 124
#define PRESENT_LOAD 126
#define PRESENT_VELOCITY 128
#define PRESENT_POSITION 132
#define VELOCITY_TRAJECTORY 136
#define POSITION_TRAJECTORY 140
#define PRESENT_INPUT_VOLTAGE 144
#define PRESENT_TEMPERATURE 146

#define ENABLED 1
#define DISABLED 0

/* Baud Rate values */
enum Baud {

    baud_9600 = 0,
    baud_57600 = 1, // default baudrate
    baud_115200 = 2,
    baud_1M = 3,
    baud_2M = 4,
    baud_3M = 5,
    baud_4M = 6,
    baud_4P5 = 7

};
// TODO: initialize function
/* Unique parameters retrieved from flash. */
typedef struct Stored_Parameters {

    uint16_t model_number;
    uint32_t model_information;
    uint8_t firmware_version;
    uint8_t motor_ID;
    uint8_t baud_rate;
    uint8_t return_delay_time; 
    uint8_t drive_mode;
    uint8_t operating_mode;
    uint8_t secondary_ID;
    uint8_t protocol_type;
    uint32_t homing_offset;
    uint32_t moving_threshold;
    uint8_t temperature_limit;
    uint16_t min_voltage_limit;
    uint16_t max_voltage_limit;
    uint16_t PWM_limit;
    uint32_t velocity_limit;
    uint32_t min_position_limit;
    uint32_t max_position_limit;
    uint8_t shutdown;  

} Stored_Parameters;

// TODO: initialize function
/* Unique parameters for runtime only. */
typedef struct Runtime_Parameters {

    uint8_t  torque_enable;
    uint8_t  led;
    uint8_t  status_return_level;
    uint8_t  registered_instruction;
    uint8_t  hardware_error_status;
    uint16_t velocity_I_gain; 
    uint16_t velocity_P_gain; 
    uint16_t position_D_gain;
    uint16_t position_I_gain;
    uint16_t position_P_gain;
    uint16_t feedforward_1st_gain;
    uint16_t feedforward_2nd_gain;
    uint8_t  BUS_watchdog;
    uint16_t goal_PWM;
    uint32_t goal_velocity;
    uint32_t profile_accelration;
    uint32_t profile_velocity;
    uint32_t goal_position;
    uint16_t realtime_tick;
    uint8_t  moving;
    uint8_t  moving_status;
    uint16_t present_PWM;
    uint16_t present_load;
    uint32_t present_velocity;
    uint32_t present_position;
    uint32_t velocity_trajectory;
    uint32_t position_trajectory;
    uint16_t present_input_voltage;
    uint8_t  present_temperature;

} Runtime_Parameters;


/*------FUNCTION PROTOTYPES---------------------------*/
void initialize_stored_parameters(void);
void process_queue(void);
void process_message(void);
void ping(void);
void read(void); 
void write(void); 
void reg_write(void); 
void action(void); 
void factory_reset(void);
void reboot(void); 
void clear(void); 
void status(void); 
void sync_read(void); 
void sync_write(void); 
void bulk_read(void); 
void bulk_write(void); 
uint32_t get_value_from_param(void);
void write_to_RAM(uint16_t, uint32_t);
void write_to_Flash(uint16_t, uint32_t);
unsigned short updateCRC(uint16_t crc_accum, uint8_t *, uint16_t);

/*------Stored Parameters FUNCTION PROTOTYPES---------------------------*/

void store_motor_ID(uint8_t);
void store_baud_rate(uint32_t);
void store_return_delay_time(uint32_t);
void store_drive_mode(uint32_t);
void store_operating_mode(uint32_t);
void store_secondary_ID(uint32_t);
void store_protocol_type(uint32_t);
void store_homing_offset(uint32_t);
void store_moving_threshold(uint32_t);
void store_temperature_limit(uint32_t);
void store_PWM_limit(uint32_t);
void store_min_voltage_limit(uint32_t);
void store_max_voltage_limit(uint32_t);
void store_velocity_limit(uint32_t);
void store_min_position_limit(uint32_t);
void store_max_position_limit(uint32_t);
void store_shutdown(uint32_t);

#endif