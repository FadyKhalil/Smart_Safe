/*
 * Stepper.h
 *
 *  Created on: jun 6, 2022
 *      Author: Ahmed-Yehia
 */

#ifndef STEPPER_H_
#define STEPPER_H_

#include "../Utils/std_types.h"

// circular shift macros
#define CircularRight(n)        (n>>1 | (n<<3 & 0xF))
#define CircularLeft(n)         (n>>3 | (n<<1 & 0xF))

#define STEPPER_INIT_POSITION   0b0001

typedef enum{
  clockwise,
  anticlockwise,
} StepperDir_t;

// Stepper_init function is used to initialize the Stepper module
// Args:    none
// Return:  none
// example:
//          Stepper_init();
extern void Stepper_init(void);

// Stepper_step function is used to move the Stepper motor shaft
//  1 step based on the provided direction
// Args:    (StepperDir_t) the direction that the stepper moves with
// Return:  (res_t) the status of the function call
// example:
//          Stepper_init(clockwise);
extern res_t Stepper_step(StepperDir_t dir);

#endif /* STEPPER_SCHED_H_ */
