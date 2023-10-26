/*
 * main.c
 *
 *  Created on: Oct 20, 2023
 *      Author: mohamed
 *      description: calculator using lcd and keypad
 */
/* section :includes */
#include<util\delay.h>
#include "STD_TYPES.h"
#include "MCAL_DIO/DIO_HEADERS/MCAL_DIO_REGISTER.h"
#include "MCAL_DIO/DIO_HEADERS/MCAL_DIO_INTERFACE.h"
#include "MCAL_DIO/DIO_HEADERS/MCAL_DIO_DATATYPES.h"
#include"HAL/ECU_LCD/ECU_LCD_HEADERS/ECU_LCD_Interface.h"
#include"HAL/ECU_7SEGMENT/ECU_7Segment_HEADERS/ECU_7segment_Interface.h"
#include"HAL/ECU_KEYPAD/ECU_KEYPAD_HEADRS/ECU_KeyPad_Interface.h"
#include <stdio.h>

/* section :macros declaration */
#define INVALID 					10
#define NOT_signed_num				 0
#define signed_num					 1
#define NOT_DONE					 0
#define DONE						 1
#define EMPTY						 0
#define DELAY_PERIOD        		100
#define ZERO_VALUE 					 0
#define MAX_CELLS_PER_NUMBER   		 6
/* section :function declaration  */
Std_ReturnType lcd_print_res(lcd_t *,u8 arr1[],u8 arr2[],u8 *op,f32 *res,u8 *signed_flag);
Std_ReturnType insert_element(u8 arr[],u8 charr);
Std_ReturnType update_lcd(lcd_t* lcd,u8 input1[],u8 input2[],u8 *op,f32 * res,u8*equality,u8 *signed_flag);
Std_ReturnType convert_arr_to_int(u8 arr[],u16*val);
Std_ReturnType floatToString(f32 number, u8* buffer, u8 bufferSize, u8 precision) ;

int main(void){

	keypad_t keypad;//create object of keypad //row =input pull up  //col = output  high
	/*keypad initialization*/
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
	//////////////////////////////////////
	lcd_t lcd_obj;//Create object of lcd
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
	ECU_Lcd_4Bit_init(&lcd_obj);//intialize lcd
	//////variables initialization
	u8 key_press=INVALID;
	u8 input_1_done= NOT_DONE ;
	u8 input_arr_2[10]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
	u8 input_arr_1[10]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
	u8 current_index=EMPTY;
	u8 op=INVALID;
	u8 opertion_done=NOT_DONE;
	u8 signed_flag=NOT_signed_num;
	f32 res=EMPTY;
	u8 equality=INVALID;
	//super loop
	while(1){
		ECU_KEYPAD_Get_Key(&keypad,&key_press);//get key from user
		if(key_press!=INVALID){
			update_lcd(&lcd_obj,input_arr_1,input_arr_2,&op,&res,&equality,&signed_flag);
			if(key_press=='s'){
				current_index--;
				if(!input_1_done){input_arr_1[current_index]=0xff;}
				else{input_arr_2[current_index]=0xff;}
				if(opertion_done){
					ECU_Lcd_4Bit_Send_Command(&lcd_obj, _LCD_CLEAR);
					ECU_Lcd_4Bit_Send_Command(&lcd_obj, _LCD_RETURN_HOME);
					opertion_done=NOT_DONE;
					current_index=EMPTY;
					input_1_done=NOT_DONE;
					equality=INVALID;
					op=INVALID;
				}
				else{/*do nothing*/}

				for (u8 i=0;i<6;i++){
					input_arr_1[i]=0xff;			//ECU_Lcd_4Bit_convert_int(arr1[i],&char1);
					input_arr_2[i]=0xff;

				}
			}

			else{//key!=s
				if(key_press!='+'&&key_press!='/'&&key_press!='*'&&key_press!='-'&&key_press!='='){//num

					if(input_1_done==NOT_DONE){//input one not done
						insert_element( input_arr_1,key_press);
					}
					else {insert_element( input_arr_2,key_press);}

					current_index++;
				}
				else{/*do nothing*/}

				if(key_press=='+'||key_press=='/'||key_press=='*'||key_press=='-'||key_press=='=')//op
				{
					if(key_press=='='){//operation
						lcd_print_res(&lcd_obj,input_arr_1,input_arr_2,&op,&res,&signed_flag);
						opertion_done=DONE;
						equality='=';
						update_lcd(&lcd_obj,input_arr_1,input_arr_2,&op,&res,&equality,&signed_flag);
					}
					else{equality=INVALID;}

					if(key_press=='+'){//operation
						input_1_done=DONE;
						op='+';
						signed_flag=NOT_signed_num;
					}
					if(key_press=='*'){//operation
						op='*';
						signed_flag=NOT_signed_num;
						input_1_done=DONE;

					}
					if(key_press=='-'){//operation
						op='-';
						signed_flag=NOT_signed_num;
						input_1_done=DONE;

					}

					if(key_press=='/'){//operation
						op='/';
						signed_flag=NOT_signed_num;
						input_1_done=DONE;

					}
				}

			}



		}
		update_lcd(&lcd_obj,input_arr_1,input_arr_2,&op, &res,&equality,&signed_flag);
		_delay_ms(DELAY_PERIOD);
	}

	return ZERO_VALUE ;
}

Std_ReturnType lcd_print_res(lcd_t *lcd,u8 arr1[10],u8 arr2[10], u8 *op,f32 *res,u8 * signed_flag){

	Std_ReturnType ret=E_NOT_OK;
	u16 num1=ZERO_VALUE;
	u16 num2=ZERO_VALUE;
	switch(*op){
	case '+':
		convert_arr_to_int(arr1,&num1);
		convert_arr_to_int(arr2,&num2);
		*res=num2+num1;
		break;

	case '-':
		convert_arr_to_int(arr1,&num1);
		convert_arr_to_int(arr2,&num2);
		if(num2>num1){
			*res=num2-num1;
			*signed_flag=signed_num;
		}
		else{*res=num1-num2;
		*signed_flag=NOT_signed_num;}
		break;

	case '*':
		convert_arr_to_int(arr1,&num1);
		convert_arr_to_int(arr2,&num2);
		*res=num2*num1;
		break;

	case '/':
		convert_arr_to_int(arr1,&num1);
		convert_arr_to_int(arr2,&num2);
		if(num2==0){*res=0xff;}else{
			*res=num1/(f32)num2;
		}
		break;
	}
	return ret ;
}
Std_ReturnType insert_element(u8 arr[],u8 charr){
	Std_ReturnType ret=E_NOT_OK;
	for (int i=ZERO_VALUE;i<MAX_CELLS_PER_NUMBER;i++){
		arr[i]=arr[i+1];
	}
	arr[5]=charr;
	ret=E_OK;
	return ret;
}
Std_ReturnType convert_arr_to_int(u8 arr[],u16*val){
	Std_ReturnType ret=E_NOT_OK;
	*val=ZERO_VALUE;
	for (int i=ZERO_VALUE;i<MAX_CELLS_PER_NUMBER;i++){
		if(arr[i]!=0xff&&arr[i]>='0'&&arr[i]<='9'){//,AKE SURE THE  NUMBER  IS NOT ANY OTHER  CHARARCTER
			*val=(*val)*10+(arr[i]-'0');}
	}
	return ret;
}
Std_ReturnType update_lcd(lcd_t* lcd,u8 input1[],u8 input2[],u8* op,f32 *res,u8*equality,u8*signed_flag){
	Std_ReturnType ret=E_NOT_OK;
	ECU_Lcd_4Bit_Send_Command(lcd,_LCD_CLEAR);
	_delay_ms(10);
	ECU_Lcd_4Bit_Send_Command(lcd,_LCD_RETURN_HOME);
	_delay_ms(10);

	ECU_Lcd_4Bit_Set_cursor(lcd,1,1);
	_delay_ms(10);

	for(u8 i=ZERO_VALUE;i<MAX_CELLS_PER_NUMBER;i++){
		if (input1[i]!=0xff){ECU_Lcd_4Bit_Send_char(lcd,input1[i]);}
		else{/*do nothing*/}
	}
	if(*op!=INVALID){
		ECU_Lcd_4Bit_Send_char(lcd,*op);
		for(u8 i=ZERO_VALUE;i<MAX_CELLS_PER_NUMBER;i++){
			if (input2[i]!=0xff){ECU_Lcd_4Bit_Send_char(lcd,input2[i]);
			}
		}
	}
	else{/*do nothing*/}
	if(*equality=='='){
		u8 str[100];
		u8 res_msg[10]="result=";
		ret=ECU_Lcd_4Bit_Send_Char_Pos(lcd,' ',ROW4,1);
		ret=ECU_Lcd_4Bit_Send_str(lcd,res_msg);
		u8 ch='-';
		if((*signed_flag==signed_num)){
			ret=ECU_Lcd_4Bit_Send_char(lcd,ch);
		}
		if((f32)(*res)!=(f32)0xff){
			floatToString(*res,str,20,3);
			for( int i=ZERO_VALUE;i<MAX_CELLS_PER_NUMBER;i++){

				if (str[i]>='.'&&str[i]<58){ret=ECU_Lcd_4Bit_Send_char(lcd,str[i]);}
				else{/*do nothing*/}
			}}else{
				u8	msg[10]="ERROR";
				ret=ECU_Lcd_4Bit_Send_str(lcd,msg);
			}
	}
	else{/*do nothing*/}

	return ret;
}
Std_ReturnType reverse(u8* str, u8 length) {
	Std_ReturnType ret=E_OK;
	u8 start = 0;
	u8 end = length - 1;
	while (start < end) {
		u8 temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
	return ret;
}

Std_ReturnType floatToString(f32 number, u8* buffer, u8 bufferSize, u8 precision) {
	Std_ReturnType ret=E_NOT_OK;
	u8 isNegative = INVALID;
	if (number < ZERO_VALUE) {
		isNegative = signed_num;
		number = -number;
	}

	// Extract integer and fractional parts
	u32 intPart = (u32)number;
	f32 fractionalPart = number - intPart;

	// Convert integer part to string
	u8 index = 0;
	while (intPart) {
		buffer[index++] = (intPart % 10) + '0';
		intPart /= 10;
	}
	if (index == 0) {
		buffer[index++] = '0';
	}
	if (isNegative) {
		buffer[index++] = '-';
	}
	reverse(buffer, index);

	// Convert fractional part to string
	if (precision > 0) {
		buffer[index++] = '.';
		for (u8 i = 0; i < precision; i++) {
			fractionalPart *= 10;
			u8 digit = (u8)fractionalPart;
			buffer[index++] = digit + '0';
			fractionalPart -= digit;
		}
	}

	buffer[index-2] = '\0';//add termination char
	return ret;
}
