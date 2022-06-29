/*
 * Led.c
 *
 *  Created on: Apr 9, 2022
 *      Author: Ahmed-Yehia
 */

#include "Lcd.h"
#include "Lcd_cfg.h"
#include "../../MCAL/GPIO/Gpio.h"

#define LCD_RUNNING_RESTORE_TICK_COUNT      2

// FSM
static Lcd_state_t Lcd_state;

//Requests handling
static u16 newReq, doneReq;
static Lcd_Request_t ReqBuffer[LCD_MAX_REQ_BUFFER_SIZE];  // circular buffer

// externed from Lcd_cfg.c
extern const LcdCfg_t Lcd_Pins_cfg[];
extern const Lcd_Request_t Lcd_Config[];

// LCD_init (sync) function is used to initialize the LCD module
//  (initialize GPIO pins connected to LCD module) 
// Args:    none
// Return:  none
// example:
//          Lcd_init();
extern void LCD_init()
{
    GPIO_tstrPinConfiguration configurator;
    for (u8 pinIndex = 0; pinIndex < LCD_NUMBER_OF_PINS; pinIndex++)
    {
        configurator.GPIO_Port = Lcd_Pins_cfg[pinIndex].port;
        configurator.GPIO_Pin= Lcd_Pins_cfg[pinIndex].pin;
        configurator.GPIO_Mode = GPIO_u8OUTPUT_PUSHPULL;
        configurator.GPIO_Speed = GPIO_Speed_High;
        Gpio_enuPinConfigurationInit(&configurator);
    }
    Lcd_state = START;
}

// LCD_prv_send (sync) function is a private function that is used
//  internally by the module to send requests to LCD 
// note: this function can't be called by the user
// Args:    request         :(Lcd_Request_t) the request bits to be sent
// Return:  none
// example:
//          ----
void LCD_prv_send(Lcd_Request_t data)
{
    Gpio_enuSetPinValue(Lcd_Pins_cfg[Lcd_EN_PIN].port, Lcd_Pins_cfg[Lcd_EN_PIN].pin, 0b0);
    Gpio_enuSetPinValue(Lcd_Pins_cfg[Lcd_RS_PIN].port, Lcd_Pins_cfg[Lcd_RS_PIN].pin, 0b1&((data.type)>>1));
    Gpio_enuSetPinValue(Lcd_Pins_cfg[Lcd_RW_PIN].port, Lcd_Pins_cfg[Lcd_RW_PIN].pin, 0b1&((data.type)>>0));
    Gpio_enuSetPinValue(Lcd_Pins_cfg[Lcd_D7_PIN].port, Lcd_Pins_cfg[Lcd_D7_PIN].pin, 0b1&((data.value)>>7));
    Gpio_enuSetPinValue(Lcd_Pins_cfg[Lcd_D6_PIN].port, Lcd_Pins_cfg[Lcd_D6_PIN].pin, 0b1&((data.value)>>6));
    Gpio_enuSetPinValue(Lcd_Pins_cfg[Lcd_D5_PIN].port, Lcd_Pins_cfg[Lcd_D5_PIN].pin, 0b1&((data.value)>>5));
    Gpio_enuSetPinValue(Lcd_Pins_cfg[Lcd_D4_PIN].port, Lcd_Pins_cfg[Lcd_D4_PIN].pin, 0b1&((data.value)>>4));
    Gpio_enuSetPinValue(Lcd_Pins_cfg[Lcd_D3_PIN].port, Lcd_Pins_cfg[Lcd_D3_PIN].pin, 0b1&((data.value)>>3));
    Gpio_enuSetPinValue(Lcd_Pins_cfg[Lcd_D2_PIN].port, Lcd_Pins_cfg[Lcd_D2_PIN].pin, 0b1&((data.value)>>2));
    Gpio_enuSetPinValue(Lcd_Pins_cfg[Lcd_D1_PIN].port, Lcd_Pins_cfg[Lcd_D1_PIN].pin, 0b1&((data.value)>>1));
    Gpio_enuSetPinValue(Lcd_Pins_cfg[Lcd_D0_PIN].port, Lcd_Pins_cfg[Lcd_D0_PIN].pin, 0b1&((data.value)>>0));
    Gpio_enuSetPinValue(Lcd_Pins_cfg[Lcd_EN_PIN].port, Lcd_Pins_cfg[Lcd_EN_PIN].pin, 0b1);
}

// LCD_Task (sync) function is scheduled by the OS to prform LCD 
// module operations
// the periodicity of the task is configured on the OS
// note: this function can't be called by the user
// Args:    none
// Return:  none
// example:
//          ----
extern void LCD_Task()
{
    
    // number of ticks that every state needs in order to finish 
    //  there operations (assuming tick time = 1ms)
    static u8 Lcd_stateTickCount[] = {
        // used only 1 time at the initialization
        [START]         = 30,
        [FUNCTION_SET]  = 1,
        [DISPLAY_CTRL]  = 1,
        [CLEAR_SCREEN]  = 2,
        [ENTRY_MODE]    = 1,

        // used continuously on the operation 
        //  so they need to be restored
        [RUNNING]       = LCD_RUNNING_RESTORE_TICK_COUNT,
    };

    static u8 Lcd_waitFlag = 0;

    // FSM
    switch (Lcd_state)
    {


        case START:

            // perform action (only waiting)
            
        	Lcd_stateTickCount[START]--;
            if (Lcd_stateTickCount[START] > 0)
            {
            	Lcd_waitFlag = 1;
            }
            else
            {
                Lcd_state = FUNCTION_SET;
                Lcd_waitFlag = 0;
            }

        break;



        case FUNCTION_SET:

            if (Lcd_waitFlag == 0)
            {
                // perform action
                LCD_prv_send(Lcd_Config[FUNCTION_SET]);
            }
            Lcd_stateTickCount[FUNCTION_SET]--;
            if (Lcd_stateTickCount[FUNCTION_SET] > 0)
            {
            	Lcd_waitFlag = 1;
            }
            else
            {
                Lcd_state = DISPLAY_CTRL;
                // enable = 0 at the end of signal
                Gpio_enuSetPinValue(Lcd_Pins_cfg[Lcd_EN_PIN].port, Lcd_Pins_cfg[Lcd_EN_PIN].pin, 0b0);
                Lcd_waitFlag = 0;
            }

        break;



        case DISPLAY_CTRL:

            if (Lcd_waitFlag == 0)
            {
                // perform action
                LCD_prv_send(Lcd_Config[DISPLAY_CTRL]);
            }
            Lcd_stateTickCount[DISPLAY_CTRL]--;
            if (Lcd_stateTickCount[DISPLAY_CTRL] > 0)
            {
            	Lcd_waitFlag = 1;
            }
            else
            {
                Lcd_state = CLEAR_SCREEN;
                // enable = 0 at the end of signal
                Gpio_enuSetPinValue(Lcd_Pins_cfg[Lcd_EN_PIN].port, Lcd_Pins_cfg[Lcd_EN_PIN].pin, 0b0);
                Lcd_waitFlag = 0;
            }

        break;



        case CLEAR_SCREEN:

            if (Lcd_waitFlag == 0)
            {
                // perform action
                LCD_prv_send(Lcd_Config[CLEAR_SCREEN]);
            }
            Lcd_stateTickCount[CLEAR_SCREEN]--;
            if (Lcd_stateTickCount[CLEAR_SCREEN] > 0)
            {
            	Lcd_waitFlag = 1;
            }
            else
            {
                Lcd_state = ENTRY_MODE;
                // enable = 0 at the end of signal
                Gpio_enuSetPinValue(Lcd_Pins_cfg[Lcd_EN_PIN].port, Lcd_Pins_cfg[Lcd_EN_PIN].pin, 0b0);
                Lcd_waitFlag = 0;
            }

        break;



        case ENTRY_MODE:

            if (Lcd_waitFlag == 0)
            {
                // perform action
                LCD_prv_send(Lcd_Config[ENTRY_MODE]);
            }
            Lcd_stateTickCount[ENTRY_MODE]--;
            if (Lcd_stateTickCount[ENTRY_MODE] > 0)
            {
            	Lcd_waitFlag = 1;
            }
            else
            {
                // based on registered requests
                if (newReq == doneReq)
                {
                    Lcd_state = IDLE;
                }
                else
                {
                    Lcd_state = RUNNING;
                }
                // enable = 0 at the end of signal
                Gpio_enuSetPinValue(Lcd_Pins_cfg[Lcd_EN_PIN].port, Lcd_Pins_cfg[Lcd_EN_PIN].pin, 0b0);
                Lcd_waitFlag = 0;
            }

        break;




        
        case IDLE:

            // based on registered requests
            if (newReq == doneReq)
            {
                Lcd_state = IDLE;
            }
            else
            {
                Lcd_state = RUNNING;
            }

        break;



        case RUNNING:

            if (Lcd_waitFlag == 0)
            {
                // perform action
                LCD_prv_send(ReqBuffer[doneReq]);
            }
            Lcd_stateTickCount[RUNNING]--;
            if (Lcd_stateTickCount[RUNNING] > 0)
            {
            	Lcd_waitFlag = 1;
            }
            else
            {
                // last request is handled
                doneReq = (doneReq+1) % LCD_MAX_REQ_BUFFER_SIZE;
                // based on registered requests
                if (newReq == doneReq)
                {
                    Lcd_state = IDLE;
                }
                else
                {
                    Lcd_state = RUNNING;
                }
                Lcd_stateTickCount[RUNNING] = LCD_RUNNING_RESTORE_TICK_COUNT;
                // enable = 0 at the end of signal
                Gpio_enuSetPinValue(Lcd_Pins_cfg[Lcd_EN_PIN].port, Lcd_Pins_cfg[Lcd_EN_PIN].pin, 0b0);
                Lcd_waitFlag = 0;
            }

        break;



    }
}

// LCD_requestRegister (async) function is used to register a new
// request to be performed on Lcd module (write data - send command)
// note:
//      - the registered request will not performed immediately
//        after the call as it works asynchronously
//      - the registeration request can be rejected if the internal
//        requests buffer is filled with previous requests (it needs
//        to be registered later)
//      - this function needs to be used inside a task scheduled to os
//        schedule in order to work correctly
// Args:    request         :(Lcd_Request_t) the request to be registered
// Return:  returnStatus    :(res_t) the status of the 
//                          registeration call 
//                          (Status_Ok: register,
//                          Status_busy: not registered)
// example:
//          LCD_requestRegister(Lcd_Request_t request);
extern res_t LCD_requestRegister(Lcd_Request_t request)
{
    res_t returnStatus = Status_Ok;
    if ( ((doneReq-newReq+LCD_MAX_REQ_BUFFER_SIZE) % LCD_MAX_REQ_BUFFER_SIZE) == 1 )
    {
        returnStatus = Status_busy;
    }
    else
    {
        // register the request
        ReqBuffer[newReq] = request;
        newReq = (newReq+1) % LCD_MAX_REQ_BUFFER_SIZE;
    }
    return returnStatus;
}


////////////////////
// wrapper functions
////////////////////


// LCD_displayCharacter (async) function is used to send a request to 
// display a character
// note:
//      - this function needs to be used inside a task scheduled to os
//        schedule in order to work correctly
// Args:    data            :(u8) the displayed data
// Return:  returnStatus    :(res_t) the status of the call 
//                          (Status_Ok: register,
//                          Status_busy: not registered)
// example:
//          LCD_displayCharacter('A');
extern res_t LCD_displayCharacter(u8 data)
{
    Lcd_Request_t req = {
        .type = LCD_REQ_TYP__DATA,
        .value = data
    };
    return LCD_requestRegister(req);
}

// LCD_sendCharacter (async) function is used to move the cursor
//  on display 
// note:
//      - this function needs to be used inside a task scheduled to os
//        schedule in order to work correctly
// Args:    x            :(u8) the targeted x value
//          y            :(u8) the targeted y value
// Return:  returnStatus    :(res_t) the status of the call 
//                          (Status_Ok: register,
//                          Status_busy: not registered)
// example:
//          LCD_Goto(4,1);
extern res_t LCD_Goto(u8 x, u8 y)
{
    Lcd_Request_t req = {
        .type = LCD_REQ_TYP__CMD,
        .value = LCD_REQ__DISPLAY_LINE2_OFFSET * y + x
    };
    return LCD_requestRegister(req);
}


/*
*   Lcd_enuDisplayNumber()
        print number on screen 
* Args:         Copy_u8Num: number value
* Return:       error status
*/
// Lcd_displayNumber (async) function is used print number on display 
// note:
//      - this function needs to be used inside a task scheduled to os
//        schedule in order to work correctly
// Args:    Num          :(s32) the displayed number
// Return:  returnStatus    :(res_t) the status of the call 
//                          (Status_Ok: register,
//                          Status_busy: not registered)
// example:
//          Lcd_displayNumber(12);
extern res_t Lcd_displayNumber(s32 Num)
{
	res_t Loc_enuStatus = Status_Ok;
	s32 Loc_s32Val;
    u8 Loc_u8Itr;
    Lcd_Request_t req;
	static u8 Loc_au8AllDigits[11]; // from -2 Billion to 2 Billion (1 bit sign and 10 bits number)
    // Loc_enuStatus = Lcd_enuSend(LCD_u8SEND_TYPE_DATA, Loc_u32Val % 10 + LCD_u8DATA__XX_RAM_DATA_ASCII_0);
	if (Num >= 0)
		Loc_s32Val = Num;
	else
		Loc_s32Val = -Num;
	for (Loc_u8Itr = 10; Loc_u8Itr >= 0 && Loc_s32Val; Loc_u8Itr--)
    {
        Loc_au8AllDigits[Loc_u8Itr] = Loc_s32Val % 10 + '0'; // store digits in ascii
        Loc_s32Val /= 10;
    }
    if (Num < 0)
    {
        Loc_au8AllDigits[Loc_u8Itr] = '-';
    }
    else
    {
        Loc_u8Itr++;
    }
	for (; Loc_u8Itr < 11; Loc_u8Itr++)
    {
        req.type = LCD_REQ_TYP__DATA;
        req.value = Loc_au8AllDigits[Loc_u8Itr];
        Loc_enuStatus = LCD_requestRegister(req);
    }
	return Loc_enuStatus;
}

extern Lcd_state_t Lcd_status(void)
{
	return Lcd_state;
}
