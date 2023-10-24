/*
 * main.c
 *
 *  Created on: Oct 20, 2023
 *      Author: mohamed
 */

#include<util\delay.h>
//#include <avr\io.h>
#include "STD_TYPES.h"
#include "MCAL_DIO/DIO_HEADERS/MCAL_DIO_REGISTER.h"
#include "MCAL_DIO/DIO_HEADERS/MCAL_DIO_INTERFACE.h"
#include "MCAL_DIO/DIO_HEADERS/MCAL_DIO_DATATYPES.h"
#include"HAL/ECU_LCD/ECU_LCD_HEADERS/ECU_LCD_Interface.h"
#include"HAL/ECU_7SEGMENT/ECU_7Segment_HEADERS/ECU_7segment_Interface.h"
#include"HAL/ECU_KEYPAD/ECU_KEYPAD_HEADRS/ECU_KeyPad_Interface.h"
#include <stdio.h>

/* section :includes */

/* section :macros declaration */
/* section :macros   declaration */
#define INVALID 10
/* section :macros function  declaration
Std_ReturnType ECU_Lcd_4Bit_init(pin_t *lcd[6]);
Std_ReturnType ECU_Lcd_Send_Enable(pin_t *LCD[6]);
Std_ReturnType ECU_Lcd_4Bit_Send_Command(pin_t *LCD[6],u8 commamd);
Std_ReturnType ECU_Lcd_4Bit_Send_char(pin_t *LCD[6],u8 charr);

Std_ReturnType ECU_Lcd_4Bit_Set_cursor(pin_t *LCD[6],u8 row,u8 col);
Std_ReturnType ECU_Lcd_4Bit_Send_Char_Pos(pin_t *LCD[6],u8 charr,u8 row,u8 col);
Std_ReturnType ECU_Lcd_4Bit_Send_str(pin_t *LCD[6],u8 *charr);
*/
/* section :data types */
#define ADD 1
#define SUB 2
#define MULT 3
#define DIV 4
#define IVALID_KEY 10
 Std_ReturnType lcd_print_res(lcd_t *,u8 arr1[],u8 arr2[],u8 *op,u16 *res);
 Std_ReturnType insert_element(u8 arr[],u8 charr);
 Std_ReturnType update_lcd(lcd_t* lcd,u8 input1[],u8 input2[],u8 *op,u16* res,u8*equality);
 Std_ReturnType convert_arr_to_int(u8 arr[],u16*val);
 Std_ReturnType convert_int_to_string(u32 value, u8 *str) ;
/* section :function declaration  */
int main(void){
	pin_t led;
	led.direction=OUTPUT;
	led.pin=pin5;
	led.port_index=PORT_D;
	Mcal_Dio_Std_Set_Pin_Direction(&led);
	Mcal_Dio_Std_Set_Pin_Value(&led,HIGH);
lcd_t lcd_obj;
keypad_t keypad;//row =inpput pull up
//col = output  high
keypad.col[0].direction=PULL_UP;
keypad.col[0].pin=pin7;
keypad.col[0].port_index=PORT_D;

keypad.col[1].direction=PULL_UP;
keypad.col[1].pin=pin6;
keypad.col[1].port_index=PORT_D;


keypad.col[2].direction=PULL_UP;
keypad.col[2].pin=pin5;
keypad.col[2].port_index=PORT_D;


keypad.col[3].direction=PULL_UP;
keypad.col[3].pin=pin3;
keypad.col[3].port_index=PORT_D;


keypad.row[0].direction=OUTPUT;
keypad.row[0].pin=pin5;
keypad.row[0].port_index=PORT_C;

keypad.row[1].direction=OUTPUT;
keypad.row[1].pin=pin4;
keypad.row[1].port_index=PORT_C;


keypad.row[2].direction=OUTPUT;
keypad.row[2].pin=pin3;
keypad.row[2].port_index=PORT_C;


keypad.row[3].direction=OUTPUT;
keypad.row[3].pin=pin2;
keypad.row[3].port_index=PORT_C;
ECU_KEYPAD_init(&keypad);
//	while(1){
//
//		_delay_ms(1000);
//		_delay_ms(1000);
//	}


	lcd_obj.en.pin=pin2;
	lcd_obj.en.port_index=PORT_A;
	lcd_obj.en.direction=OUTPUT;

	lcd_obj.rs.pin=pin3;
	lcd_obj.rs.port_index=PORT_A;
	lcd_obj.rs.direction=OUTPUT;

	lcd_obj.lcd_pins_0.pin=pin0;
	lcd_obj.lcd_pins_0.port_index=PORT_B;
	lcd_obj.lcd_pins_0.direction=OUTPUT;


	lcd_obj.lcd_pins_1.pin=pin1;
	lcd_obj.lcd_pins_1.port_index=PORT_B;
	lcd_obj.lcd_pins_1.direction=OUTPUT;


	lcd_obj.lcd_pins_2.pin=pin2;
	lcd_obj.lcd_pins_2.port_index=PORT_B;
	lcd_obj.lcd_pins_2.direction=OUTPUT;


	lcd_obj.lcd_pins_3.pin=pin4;
	lcd_obj.lcd_pins_3.port_index=PORT_B;
	lcd_obj.lcd_pins_3.direction=OUTPUT;
	ECU_Lcd_4Bit_init(&lcd_obj);
u8 key_press=10;
u8 input_1_done=0;
u8 input_arr_2[10]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
u8 input_arr_1[10]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
u8 current_index=0;
u8 op=INVALID;
u8 opertion_done=0;


u16 res=INVALID;//INVALID;
u8 equality=0;
/*
u16 tst;
u8 *ste="l";
u8 arr3[]={'2','1'};
convert_arr_to_int(arr3,&tst);

convert_int_to_string(tst,ste);
ECU_Lcd_4Bit_Send_str(&lcd_obj,ste);
*/



while(1){

ECU_KEYPAD_Get_Key(&keypad,&key_press);
if(key_press!=IVALID_KEY){//ECU_Lcd_4Bit_Send_char(&lcd_obj,key_press);
	update_lcd(&lcd_obj,input_arr_1,input_arr_2,&op,&res,&equality);
		if(key_press=='s'){
				current_index--;
	if(!input_1_done){input_arr_1[current_index]=0xff;}
	else{input_arr_2[current_index]=0xff;}
if(opertion_done){ECU_Lcd_4Bit_Send_Command(&lcd_obj, _LCD_CLEAR);
ECU_Lcd_4Bit_Send_Command(&lcd_obj, _LCD_RETURN_HOME);
opertion_done=0;//not done
current_index=0;
		input_1_done=0;//not done
		equality=0;

		op=INVALID;
}

for (u8 i=0;i<6;i++){
	input_arr_1[i]=0xff;			//ECU_Lcd_4Bit_convert_int(arr1[i],&char1);
		input_arr_2[i]=0xff;

		}
							}

else{//key!=s
		if(key_press!='+'&&key_press!='/'&&key_press!='*'&&key_press!='-'&&key_press!='='){//num

	if(input_1_done==0){//input one not done

	//	if(current_index==0){num1=key_press-'0';}

		insert_element( input_arr_1,key_press);

	}
	else {insert_element( input_arr_2,key_press);
//	ECU_Lcd_4Bit_Send_char(&lcd_obj,input_arr_2[current_index]+'0');

	}

	//current_index++;
}

if(key_press=='+'||key_press=='/'||key_press=='*'||key_press=='-'||key_press=='=')//op
{
	if(key_press=='='){//operation
		//ECU_Lcd_4Bit_Send_char(&lcd_obj,key_press);
	lcd_print_res(&lcd_obj,input_arr_1,input_arr_2,&op,&res);
opertion_done=1;
equality='=';
update_lcd(&lcd_obj,input_arr_1,input_arr_2,&op,&res,&equality);
	}//else{equality=0;}

	if(key_press=='+'){//operation
		//ECU_Lcd_4Bit_Send_char(&lcd_obj,key_press);
		input_1_done=1;

		op='+';
		key_press=IVALID_KEY;
		//input_1_done=1;

	}
	if(key_press=='*'){//operation
		op='*';
		input_1_done=1;

	}
	if(key_press=='-'){//operation
		op='-';
		input_1_done=1;

	}

	if(key_press=='/'){//operation
		op='/';
		input_1_done=1;

	}
}

}



}
update_lcd(&lcd_obj,input_arr_1,input_arr_2,&op, &res,&equality);
_delay_ms(100);
}

	return 0;
}

 Std_ReturnType lcd_print_res(lcd_t *lcd,u8 arr1[10],u8 arr2[10], u8 *op,u16 *res){

	 Std_ReturnType ret=E_NOT_OK;


	 			u16 num1=0;
	 			u16 num2=0;

switch(*op){

case '+':

	convert_arr_to_int(arr1,&num1);

	convert_arr_to_int(arr2,&num2);

			*res=num2+num1;//+num2

	break;

case '-':

	convert_arr_to_int(arr1,&num1);

	convert_arr_to_int(arr2,&num2);

			*res=num1-num2;//+num2

	break;

case '*':

	convert_arr_to_int(arr1,&num1);

	convert_arr_to_int(arr2,&num2);

			*res=num2*num1;//+num2

	break;

case '/':

	convert_arr_to_int(arr1,&num1);

	convert_arr_to_int(arr2,&num2);

			*res=num1/num2;//+num2

	break;


}


	return ret ;
 }
Std_ReturnType insert_element(u8 arr[],u8 charr){
	for (int i=0;i<6;i++){

		arr[i]=arr[i+1];



	}

	arr[5]=charr;
return 0;
}
Std_ReturnType convert_arr_to_int(u8 arr[],u16*val){
	Std_ReturnType ret=E_NOT_OK;
	*val=0;

	for (int i=0;i<6;i++){


		if(arr[i]!=0xff&&arr[i]>='0'&&arr[i]<='9'){
			*val=(*val)*10+(arr[i]-'0');}
	}

return ret;
}
Std_ReturnType update_lcd(lcd_t* lcd,u8 input1[],u8 input2[],u8* op,u16 *res,u8*equality){
	Std_ReturnType ret=E_NOT_OK;

ECU_Lcd_4Bit_Send_Command(lcd,_LCD_CLEAR);
_delay_ms(10);
ECU_Lcd_4Bit_Send_Command(lcd,_LCD_RETURN_HOME);
_delay_ms(10);

ECU_Lcd_4Bit_Set_cursor(lcd,1,1);
_delay_ms(10);

for(u8 i=0;i<6;i++){///////////////////////////////////////////
	if (input1[i]!=0xff){ECU_Lcd_4Bit_Send_char(lcd,input1[i]);
}
}
if(*op!=INVALID){

ECU_Lcd_4Bit_Send_char(lcd,*op);
for(u8 i=0;i<6;i++){
	if (input2[i]!=0xff){ECU_Lcd_4Bit_Send_char(lcd,input2[i]);
}

}


}
if(*equality=='='){//ECU_Lcd_4Bit_Send_char(lcd,*res);

u8 str[100];
		///
/*
 *
 * u8 str[100]
 * u8* str
 */


		 ///convert int to string
		//sprintf(str, "%d", *res);
		 convert_int_to_string(*res, str);

		 ECU_Lcd_4Bit_Send_Char_Pos(lcd,'r',2,1);

		for( int i=0;i<6;i++){

			if (str[i]>47&&str[i]<58){ECU_Lcd_4Bit_Send_char(lcd,str[i]);}
		}
}

	return ret;

}

Std_ReturnType convert_int_to_string(u32 value, u8 *str) {
    u32 l_counter = 0;
    Std_ReturnType ret = E_NOT_OK;

    if (NULL == str) {
        ret = E_NOT_OK;
    } else {
        u32 power;
        memset(str, '\0', 10); //fill the array with null termination
        for (l_counter = 1; l_counter <= 6; l_counter++) {
            power = pow_m(10, l_counter);

            str[6 - l_counter] = (((value) % (power)) / (power / 10)) + '0';


        }

        ret = E_OK;
    }



    return ret;
}
