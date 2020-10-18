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

/* Unique parameters retrieved from flash. */
typedef struct Stored_Parameters {

    uint8_t model_number;
    uint8_t firmware_version;
    uint8_t motor_ID;
    uint8_t baud_rate;
    uint8_t return_delay_time; 
    uint8_t drive_mode;
    uint8_t operating_mode;
    uint8_t secondary_ID;
    uint8_t protocol_type;
    uint8_t homing_offset;
    uint8_t moving_threshold;
    uint8_t temperature_limit;
    uint8_t min_voltage_limit;
    uint8_t max_voltage_limit;
    uint8_t PWM_limit;
    uint8_t velocity_limit;
    uint8_t min_position_limit;
    uint8_t max_position_limit;
    uint8_t shutdown;  

} Stored_Parameters;



typedef struct Temp_Parameters {

    uint8_t torque_enable;
    uint8_t LED;
    uint8_t status_return_level;
    uint8_t registered_instruction;
    uint8_t hardware_error_status;
    uint8_t velocity_PI_gain; 
    uint8_t position_PID_gain;
    uint8_t feedforward_gain;
    uint8_t BUS_watchdog;
    uint8_t Goal_PWM;
    uint8_t Goal_velocity;
    uint8_t profile_accelration;
    uint8_t profile_velocity;
    uint8_t goal_position;
    uint8_t realtime_tick;
    uint8_t moving;
    uint8_t moving_status;
    uint8_t present_PWM;
    uint8_t present_load;
    uint8_t present_velocity;
    uint8_t present_position;
    uint8_t velocity_trajectory;
    uint8_t position_trajectory;
    uint8_t present_input_voltage;
    uint8_t present_temperature;
    uint8_t indirect_address;
    uint8_t indirect_data;

}Temp_Parameters;


/*------FUNCTION PROTOTYPES---------------------------*/
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

/*------Stored Parameters FUNCTION PROTOTYPES---------------------------*/

void store_model_number(uint8_t);
void store_firmware_version(uint8_t);
void store_motor_ID(uint8_t);
void store_baud_rate(uint8_t);
void store_return_delay_time(uint8_t);
void store_drive_mode(uint8_t);
void store_operating_mode(uint8_t);
void store_secondary_ID(uint8_t);
void store_protocol_type(uint8_t);
void store_homing_offset(uint8_t);
void store_moving_threshold(uint8_t);
void store_temperature_limit(uint8_t);
void store_min_max_voltage_limit(uint8_t);
void store_PWM_limit(uint8_t);
void store_min_voltage_limit(uint8_t);
void store_max_voltage_limit(uint8_t);
void store_min_position_limit(uint8_t);
void store_max_position_limit(uint8_t);
void store_shutdown(uint8_t);

#endif