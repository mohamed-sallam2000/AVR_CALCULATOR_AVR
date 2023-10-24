/*
 * ECU_KeyPad_Interface.h
 *
 *  Created on: Oct 22, 2023
 *      Author: mohamed
 */

#ifndef HAL_ECU_KEYPAD_ECU_KEYPAD_HEADRS_ECU_KEYPAD_INTERFACE_H_
#define HAL_ECU_KEYPAD_ECU_KEYPAD_HEADRS_ECU_KEYPAD_INTERFACE_H_
#include "../../../MCAL_DIO/DIO_HEADERS/MCAL_DIO_INTERFACE.h"
#include<util\delay.h>

//row =inpput pull up
//col = output  high
typedef struct{



	pin_t row[4];


	pin_t col[4];

}keypad_t;


Std_ReturnType ECU_KEYPAD_init(keypad_t * keypad);


Std_ReturnType ECU_KEYPAD_Get_Key(keypad_t * keypad,u8 * ret_val);
#endif /* HAL_ECU_KEYPAD_ECU_KEYPAD_HEADRS_ECU_KEYPAD_INTERFACE_H_ */
/*keypad_t keypad;//row =inpput pull up
//col = output  high
keypad.col[0].direction=OUTPUT;
keypad.col[0].pin=pin7;
keypad.col[0].port_index=PORT_D;

keypad.col[1].direction=OUTPUT;
keypad.col[1].pin=pin6;
keypad.col[1].port_index=PORT_D;


keypad.col[2].direction=OUTPUT;
keypad.col[2].pin=pin5;
keypad.col[2].port_index=PORT_D;


keypad.col[3].direction=OUTPUT;
keypad.col[3].pin=pin3;
keypad.col[3].port_index=PORT_D;


keypad.row[0].direction=PULL_UP;
keypad.row[0].pin=pin5;
keypad.row[0].port_index=PORT_C;

keypad.row[1].direction=PULL_UP;
keypad.row[1].pin=pin4;
keypad.row[1].port_index=PORT_C;


keypad.row[2].direction=PULL_UP;
keypad.row[2].pin=pin3;
keypad.row[2].port_index=PORT_C;


keypad.row[3].direction=PULL_UP;
keypad.row[3].pin=pin2;
keypad.row[3].port_index=PORT_C;


*/
