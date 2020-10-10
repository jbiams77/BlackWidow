#include "stepper.h"
#include "main.h"

Motor_t m;

void DRV8825_initStepper()
{
    m.delay = 60;
    m.stepsPerCycle = 8;
    DRV8825_setMode();
	DRV8825_enableStepper();

}

/*
      M0  |  M1  |  M2  |   Resolution
      0   |  0   |  0   |   Full Step
      1   |  0   |  0   |   Half Step
      0   |  1   |  0   |   1/4 Step
      1   |  1   |  0   |   1/8 Step
      0   |  0   |  1   |   1/16 Step
      1   |  0   |  1   |   1/32 Step
 */

void DRV8825_setMode()
{
    // 1/16th step
    HAL_GPIO_WritePin(M0_GPIO_Port, M0_Pin, 0);
	HAL_GPIO_WritePin(M1_GPIO_Port, M1_Pin, 0);
	HAL_GPIO_WritePin(M2_GPIO_Port, M2_Pin, 1);
}


void DRV8825_findDirection()
{
    if(m.target_angle < m.current_angle) {
        HAL_GPIO_WritePin(STEP_DIR_GPIO_Port, STEP_DIR_Pin, 0);
    } 
    else { 
        HAL_GPIO_WritePin(STEP_DIR_GPIO_Port, STEP_DIR_Pin, 1);
    }
}

void DRV8825_enableStepper()
{
    HAL_GPIO_WritePin(ENABLE_GPIO_Port, ENABLE_Pin, 0);
}

void DRV8825_disableStepper()
{
    HAL_GPIO_WritePin(ENABLE_GPIO_Port, ENABLE_Pin, 1);
}

uint8_t DRV8825_goToTarget()
{
    int i;
    float error = abs(m.target_angle-m.current_angle);
    DRV8825_findDirection();
    if(error > 20){
        for(i=0; i < m.stepsPerCycle; i++){
            DRV8825_step();
        }
		return 1;
    } else {
		return 0;
	}
	
}

void DRV8825_step()
{
    HAL_GPIO_WritePin(STEP_GPIO_Port, STEP_Pin, 1);
    DWT_Delay(m.delay);
    HAL_GPIO_WritePin(STEP_GPIO_Port, STEP_Pin, 0);
    DWT_Delay(m.delay);
}

void DRV8825_setCurrentAngle(uint16_t current_angle)
{
    m.current_angle = current_angle;
}

void DRV8825_setTarget(uint16_t new_angle)
{
    m.target_angle = new_angle;
}