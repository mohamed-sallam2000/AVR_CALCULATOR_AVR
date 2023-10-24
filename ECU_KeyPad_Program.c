/*
 * ECU_KeyPad_Program.c
 *
 *  Created on: Oct 22, 2023
 *      Author: mohamed
 */

#include"../ECU_KEYPAD_HEADRS/ECU_KeyPad_Interface.h"


u8 keys[4][4]={

		{'7','8','9','/'},
		{'4','5','6','*'},
		{'1','2','3','-'},
		{'s','0','=','+'}




};
Std_ReturnType ECU_KEYPAD_init(keypad_t * keypad){

	Std_ReturnType ret=E_NOT_OK;





	int i=0;
	for(i=0;i<4;i++){

		ret=Mcal_Dio_Std_Set_Pin_Direction(&keypad->col[i]);
		ret=Mcal_Dio_Std_Set_Pin_Value(&keypad->row[i],HIGH);
		ret=Mcal_Dio_Std_Set_Pin_Direction(&keypad->row[i]);


	}

	return ret;
}
Std_ReturnType ECU_KEYPAD_Get_Key(keypad_t * keypad,u8 * ret_val){
	Std_ReturnType ret=E_NOT_OK;
	u8 row_counter=0;
	u8 col_counter=0;
	u8 val=1;
	*ret_val=10;//invalid  value
	for(col_counter=0;col_counter<4;col_counter++){
	if(col_counter==0){	ret=Mcal_Dio_Std_Set_Pin_Value(&keypad->row[3],HIGH);}
	if(col_counter>0){	ret=Mcal_Dio_Std_Set_Pin_Value(&keypad->row[col_counter-1],HIGH);}
		ret=Mcal_Dio_Std_Set_Pin_Value(&keypad->row[col_counter],LOW);
		for(row_counter=0;row_counter<4;row_counter++){
			Mcal_Dio_Std_Get_Pin_Value(&keypad->col[row_counter],&val);

		if(val==LOW){*ret_val=keys[col_counter][row_counter];val=1;}

		}
//for  debouncsing
		_delay_ms(50);
	}
return ret;


}
