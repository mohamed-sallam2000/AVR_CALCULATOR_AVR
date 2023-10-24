/*
 * ECU_LCD_Config.h
 *
 *  Created on: Oct 22, 2023
 *      Author: mohamed
 */

#ifndef HAL_ECU_LCD_ECU_LCD_HEADERS_ECU_LCD_CONFIG_H_
#define HAL_ECU_LCD_ECU_LCD_HEADERS_ECU_LCD_CONFIG_H_

#define _LCD_CLEAR                      0x01
#define _LCD_RETURN_HOME                0x02
#define _LCD_ENTRY_MODE                 0x06
#define _LCD_CURSOR_OFF_DISPLAY_ON      0x0C
#define _LCD_CURSOR_OFF_DISPLAY_OFF     0x08
#define _LCD_CURSOR_ON_BLINK_ON         0x0F
#define _LCD_CURSOR_ON_BLINK_OFF        0x0E
#define _LCD_DISPLAY_SHIFT_RIGHT        0x1C
#define _LCD_DISPLAY_SHIFT_LEFT         0x18
#define _LCD_8BIT_MODE_2_LINE           0x38
#define _LCD_4BIT_MODE_2_LINE           0x28
#define _LCD_CGRAM_START                0x40
#define _LCD_DDRAM_START                0x80


#define ROW1 1
#define ROW2 2
#define ROW3 3
#define ROW4 4

#endif /* HAL_ECU_LCD_ECU_LCD_HEADERS_ECU_LCD_CONFIG_H_ */
