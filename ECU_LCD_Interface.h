/*
 * ECU_LCD_Interface.h
 *
 *  Created on: Oct 22, 2023
 *      Author: mohamed
 */

#ifndef HAL_ECU_LCD_ECU_LCD_HEADERS_ECU_LCD_INTERFACE_H_
#define HAL_ECU_LCD_ECU_LCD_HEADERS_ECU_LCD_INTERFACE_H_
#include"../../../STD_TYPES.h"
#include"../../../MCAL_DIO/DIO_HEADERS/MCAL_DIO_INTERFACE.h"
#include<util\delay.h>
#include"string.h"
#include"../../../MCAL_DIO/DIO_HEADERS/MCAL_DIO_DATATYPES.h"
#include"ECU_LCD_Config.h"
#include <avr\io.h>
typedef struct {
pin_t rs;
pin_t en;

pin_t lcd_pins_0;

pin_t lcd_pins_1;

pin_t lcd_pins_2;

	pin_t lcd_pins_3;

}lcd_t;
Std_ReturnType ECU_Lcd_4Bit_init(lcd_t * lcd);
Std_ReturnType ECU_Lcd_Send_Enable(lcd_t * LCD);
Std_ReturnType ECU_Lcd_4Bit_Send_Command(lcd_t (* LCD),u8 commamd);
Std_ReturnType ECU_Lcd_4Bit_Send_char(lcd_t * lcd,u8 charr);
Std_ReturnType ECU_Lcd_4Bit_Set_cursor(lcd_t * lcd,u8 row,u8 col);
Std_ReturnType ECU_Lcd_4Bit_Send_Char_Pos(lcd_t * lcd,u8 charr,u8 row,u8 col);
Std_ReturnType ECU_Lcd_4Bit_Send_str(lcd_t * lcd,u8 *charr);
Std_ReturnType ECU_Lcd_4Bit_convert_int(u8 charr,u8 * int_val);
Std_ReturnType  ECU_Lcd_convert_int_to_string(u32 value, u8 *str) ;
u32 pow_m(u8 l_base, u8 power) ;

#endif /* HAL_ECU_LCD_ECU_LCD_HEADERS_ECU_LCD_INTERFACE_H_ */
/*lcd_t lcd_obj;
lcd_obj.en.pin=pin2;
lcd_obj.en.port_index=PORT_A;
lcd_obj.en.direction=OUTPUT;

lcd_obj.rs.pin=pin3;
lcd_obj.rs.port_index=PORT_A;
lcd_obj.rs.direction=OUTPUT;

lcd_obj.lcd_pins[0].pin=pin0;
lcd_obj.rs.port_index=PORT_B;
lcd_obj.rs.direction=OUTPUT;


lcd_obj.lcd_pins[1].pin=pin1;
lcd_obj.rs.port_index=PORT_B;
lcd_obj.rs.direction=OUTPUT;


lcd_obj.lcd_pins[2].pin=pin2;
lcd_obj.rs.port_index=PORT_B;
lcd_obj.rs.direction=OUTPUT;


lcd_obj.lcd_pins[3].pin=pin4;
lcd_obj.rs.port_index=PORT_B;
lcd_obj.rs.direction=OUTPUT;
ECU_Lcd_4Bit_init(&lcd_obj);*/
