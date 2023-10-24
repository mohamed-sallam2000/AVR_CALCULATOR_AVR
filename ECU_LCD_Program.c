/*
 * ECU_LCD_Program.c
 *
 *  Created on: Oct 22, 2023
 *      Author: mohamed
 */

#include"../ECU_LCD_HEADERS/ECU_LCD_Interface.h"

Std_ReturnType ECU_Lcd_Send_Enable(lcd_t * lcd){
	Std_ReturnType ret=E_NOT_OK;
ret=Mcal_Dio_Std_Set_Pin_Value(&(lcd->en),HIGH);
_delay_us(5);

ret=Mcal_Dio_Std_Set_Pin_Value(&(lcd->en),LOW);
return ret;
}

Std_ReturnType ECU_Lcd_4Bit_Send_Command(lcd_t * lcd,u8 command){

	Std_ReturnType ret=E_NOT_OK;
	Mcal_Dio_Std_Set_Pin_Value(&(lcd->rs),LOW);//rs


	Mcal_Dio_Std_Set_Pin_Value(&(lcd->lcd_pins_0),((command>>4)&0x01));
	Mcal_Dio_Std_Set_Pin_Value(&(lcd->lcd_pins_1),((command>>5)&0x01));

	Mcal_Dio_Std_Set_Pin_Value(&(lcd->lcd_pins_2),((command>>6)&0x01));

	Mcal_Dio_Std_Set_Pin_Value(&(lcd->lcd_pins_3),((command>>7)&0x01));
	/*set enable */

	ECU_Lcd_Send_Enable(lcd);
	Mcal_Dio_Std_Set_Pin_Value(&(lcd->rs),LOW);//rs
	Mcal_Dio_Std_Set_Pin_Value(&lcd->lcd_pins_0,((command>>0)&0x01));

	Mcal_Dio_Std_Set_Pin_Value(&lcd->lcd_pins_1,((command>>1)&0x01));

	Mcal_Dio_Std_Set_Pin_Value(&lcd->lcd_pins_2,((command>>2)&0x01));

	Mcal_Dio_Std_Set_Pin_Value(&lcd->lcd_pins_3,((command>>3)&0x01));
		/*set enable */
		ECU_Lcd_Send_Enable(lcd);

		/*set enable */


		//_delay_ms(1000);	_delay_ms(1000);

return ret;




}

Std_ReturnType ECU_Lcd_4Bit_init(lcd_t * lcd){
	Std_ReturnType ret=E_NOT_OK;

	Mcal_Dio_Std_Set_Pin_Direction(&(lcd->en));
	ret=Mcal_Dio_Std_Set_Pin_Direction(&(lcd->rs));
	ret=Mcal_Dio_Std_Set_Pin_Direction(&(lcd->lcd_pins_0));
	ret=Mcal_Dio_Std_Set_Pin_Direction(&lcd->lcd_pins_1);
	ret=Mcal_Dio_Std_Set_Pin_Direction(&lcd->lcd_pins_2);
	ret=Mcal_Dio_Std_Set_Pin_Direction(&lcd->lcd_pins_3);


	_delay_ms(100);
	ret=ECU_Lcd_4Bit_Send_Command(lcd,_LCD_8BIT_MODE_2_LINE );
	_delay_ms(5);
	ret=ECU_Lcd_4Bit_Send_Command(lcd,_LCD_8BIT_MODE_2_LINE );//_LCD_8BIT_MODE_2_LINE
	_delay_ms(100);
	ret=ECU_Lcd_4Bit_Send_Command(lcd,_LCD_8BIT_MODE_2_LINE );//_LCD_8BIT_MODE_2_LINE
	_delay_ms(100);
	ret=ECU_Lcd_4Bit_Send_Command(lcd,_LCD_CLEAR );
	_delay_ms(100);


	ret=ECU_Lcd_4Bit_Send_Command(lcd,_LCD_RETURN_HOME );
	_delay_ms(100);

	ret=ECU_Lcd_4Bit_Send_Command(lcd,_LCD_ENTRY_MODE );
	_delay_ms(100);

	ret=ECU_Lcd_4Bit_Send_Command(lcd,_LCD_CURSOR_OFF_DISPLAY_ON );
	_delay_ms(100);

	ret=ECU_Lcd_4Bit_Send_Command(lcd,_LCD_4BIT_MODE_2_LINE );
	_delay_ms(100);

	ret=ECU_Lcd_4Bit_Send_Command(lcd,_LCD_RETURN_HOME );
	_delay_ms(100);
	return ret;
}

Std_ReturnType ECU_Lcd_4Bit_Send_char(lcd_t * lcd,u8 charr){

	Std_ReturnType ret=E_NOT_OK;
	Mcal_Dio_Std_Set_Pin_Value(&(lcd->rs),HIGH);//rs

	Mcal_Dio_Std_Set_Pin_Value(&(lcd->lcd_pins_0),((charr>>4)&0x01));

	Mcal_Dio_Std_Set_Pin_Value(&lcd->lcd_pins_1,((charr>>5)&0x01));

	Mcal_Dio_Std_Set_Pin_Value(&lcd->lcd_pins_2,((charr>>6)&0x01));

	Mcal_Dio_Std_Set_Pin_Value(&lcd->lcd_pins_3,((charr>>7)&0x01));


	/*set enable */

	ECU_Lcd_Send_Enable(lcd);
	Mcal_Dio_Std_Set_Pin_Value(&(lcd->rs),HIGH);//rs
	Mcal_Dio_Std_Set_Pin_Value(&(lcd->lcd_pins_0),((charr>>0)&0x01));

	Mcal_Dio_Std_Set_Pin_Value(&lcd->lcd_pins_1,((charr>>1)&0x01));

	Mcal_Dio_Std_Set_Pin_Value(&lcd->lcd_pins_2,((charr>>2)&0x01));

	Mcal_Dio_Std_Set_Pin_Value(&lcd->lcd_pins_3,((charr>>3)&0x01));
		/*set enable */
		ECU_Lcd_Send_Enable(lcd);


return ret;




}
Std_ReturnType ECU_Lcd_4Bit_Set_cursor(lcd_t * lcd,u8 row,u8 col){

	Std_ReturnType ret=E_NOT_OK;
	col--;
	    switch (row) {
	        case ROW1:
	        	ECU_Lcd_4Bit_Send_Command(lcd, ((0x80) + col));
	            break;
	        case ROW2:ECU_Lcd_4Bit_Send_Command(lcd, ((0x80) + col + 0x40));
	            break;

	        case ROW3:ECU_Lcd_4Bit_Send_Command(lcd, ((0x80) + col + 0x14));
	            break;
	        case ROW4:ECU_Lcd_4Bit_Send_Command(lcd, ((0x80) + col + 0x54));
	            break;
	default:
	            ;
	    }
	            return ret;
}
Std_ReturnType ECU_Lcd_4Bit_Send_Char_Pos(lcd_t * lcd,u8 charr,u8 row,u8 col){
	ECU_Lcd_4Bit_Set_cursor(lcd,row,col);
	ECU_Lcd_4Bit_Send_char(lcd,charr);

	Std_ReturnType ret=E_NOT_OK;
    return ret;


}




Std_ReturnType ECU_Lcd_4Bit_Send_str(lcd_t * lcd,u8 *str){

	Std_ReturnType ret= E_NOT_OK;


	while(*str){

		ret= ECU_Lcd_4Bit_Send_char(lcd,*str);
str++;

	}



	return ret;



}
Std_ReturnType ECU_Lcd_4Bit_convert_int(u8 charr,u8 * int_val){
	*int_val=charr-'0';
	return E_OK;



}


Std_ReturnType ECU_Lcd_convert_int_to_string(u32 value, u8 *str) {
    u32 l_counter = 0;
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == str) {
        ret = E_NOT_OK;
    } else {
        u32 power;
        memset(str, "\0", 11); //fill the array with null termination
        for (l_counter = 1; l_counter <= 11; l_counter++) {
            power = pow_m(10, l_counter);

            str[11 - l_counter] = (((value) % (power)) / (power / 10)) + '0';


        }

        ret = E_OK;
    }



    return ret;
}
u32 pow_m(u8 l_base, u8 power) {


    u32 res = 1;
    if (power == 0) {
        return 1;
    }
    while (power--) {
        res *= l_base;

    }
    return res;
}
