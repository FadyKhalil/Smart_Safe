/*
 * App.h
 *
 *  Created on: Apr 17, 2022
 *      Author: fady
 */

#ifndef APPLICATION_APP_H_
#define APPLICATION_APP_H_


enum // FSM states
{
	DIGIT_STATE = 1,
	SIGN_STATE,
	EQUAL_STATE,
};

void Calculator(void);


#endif /* APPLICATION_APP_H_ */
