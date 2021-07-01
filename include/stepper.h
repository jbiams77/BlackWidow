#include <stdint.h>
#include <stdlib.h>
#include "dwt_delay.h"

#ifndef __STEPPER_H_
#define __STEPPER_H_

/*******  Functions *******/

void DRV8825_initStepper();
void DRV8825_setMode();
void DRV8825_findDirection();
void DRV8825_enableStepper();
void DRV8825_disableStepper();
uint8_t DRV8825_goToTarget();
void DRV8825_setCurrentAngle(uint16_t);
void DRV8825_setTarget(uint16_t);
void DRV8825_step();

/*******  Structures  *******/

typedef struct Motor{
    uint16_t target_angle;
    uint16_t current_angle;
    uint16_t delay;
    uint8_t stepsPerCycle;
} Motor_t;

#endif
