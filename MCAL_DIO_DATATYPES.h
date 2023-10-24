/*
 * MCAL_DIO_DATATYPES.h
 *
 *  Created on: Oct 20, 2023
 *      Author: mohamed
 */

#ifndef MCAL_DIO_DIO_HEADERS_MCAL_DIO_DATATYPES_H_
#define MCAL_DIO_DIO_HEADERS_MCAL_DIO_DATATYPES_H_
#include"../../STD_TYPES.h"
typedef struct{

	u8 port_index:2;
	u8 pin:3;
	u8 direction:2;
	u8    :1;

}pin_t;

typedef enum {

	PORT_A=0,
	PORT_B,
	PORT_C,
	PORT_D

}port_T;
typedef enum {

	LOW,HIGH

}LOGIC;
typedef u8 logic_t;

#endif /* MCAL_DIO_DIO_HEADERS_MCAL_DIO_DATATYPES_H_ */
