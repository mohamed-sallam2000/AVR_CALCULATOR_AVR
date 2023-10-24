#ifndef MCAL_DIO_INTERFACE
#define MCAL_DIO_INTERFACE

/* section :includes */
#include"MCAL_DIO_DATATYPES.h"
/* section :macros declaration */
#define INPUT 0
#define OUTPUT 1
#define PULL_UP (u8)2
/* section :macros function  declaration */
typedef enum{
	pin0,
	pin1,
	pin2,
	pin3,
	pin4,
	pin5,
	pin6,
	pin7


}pins;
typedef enum{
	portA,
	portB,
	portC,
	portD


}port_index_t;
/* section :data types */

/* section :function declaration  */

Std_ReturnType Mcal_Dio_Std_Set_Pin_Direction(pin_t* pin_obj);
Std_ReturnType Mcal_Dio_Std_Set_Pin_Value(pin_t* pin_obj,logic_t value) ;
Std_ReturnType Mcal_Dio_Std_Get_Pin_Value(pin_t* pin_obj,logic_t*ret_value) ;
Std_ReturnType Mcal_Dio_Std_Toggle_Pin_Value(pin_t* pin_obj) ;

Std_ReturnType Mcal_Dio_Std_Set_Port_Direction(port_index_t port_index,u8 value);
Std_ReturnType Mcal_Dio_Std_Set_Port_Value(port_index_t port_index,u8 value);
Std_ReturnType Mcal_Dio_Std_Get_Port_Value(port_index_t port_index,u8 *ret_value);
Std_ReturnType Mcal_Dio_Std_Toggle_Port_Value(port_index_t port_index);



#endif
