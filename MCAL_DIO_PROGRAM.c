/* section :includes */
#include "../../STD_TYPES.h"
#include"../DIO_HEADERS/MCAL_DIO_REGISTER.h"
#include "../DIO_HEADERS/MCAL_DIO_DATATYPES.h"
#include "../DIO_HEADERS/MCAL_DIO_INTERFACE.h"

/* section :macros declaration */

/* section :macros function  declaration */

/* section :data types */

volatile u8 *DDR[4] = { &DDRA_m, &DDRB_m, &DDRC_m, &DDRD_m };
volatile u8 *PIN[4] = { &PINA_m, &PINB_m, &PINC_m, &PIND_m };
volatile u8* PORT[4] = { &PORTA_m, &PORTB_m, &PORTC_m, &PORTD_m };
/* section :function declaration  */
/*
 *@brief set the direction of  a  specific  pin
 *argument : take struct  pointer of  type  pin_t
 * return Std_ReturnType error state
 *
 * **/

Std_ReturnType Mcal_Dio_Std_Set_Pin_Direction(pin_t* pin_obj) {

	Std_ReturnType ret = E_NOT_OK;
	if (pin_obj == NULL) {/*do nothing*/
	} else {

		if (pin_obj->direction==OUTPUT) {
			SET_BIT(*DDR[pin_obj->port_index], pin_obj->pin);
		} else if(pin_obj->direction==INPUT){

			CLEAR_BIT(*DDR[pin_obj->port_index], pin_obj->pin);

		}
		else if(pin_obj->direction==PULL_UP){
			CLEAR_BIT(*DDR[pin_obj->port_index], pin_obj->pin);
			SET_BIT(*PORT[pin_obj->port_index], pin_obj->pin);
		}
		ret = E_OK;
	}

	return ret;

}

/*
 *@brief set value  of  one  bit
 *name:Mcal_Dio_Std_Set_Pin_Value
 *argument : pointer to struct of type  pin_t value  of  this  pin
 *return Std_ReturnType error state
 *
 * **/
Std_ReturnType Mcal_Dio_Std_Set_Pin_Value(pin_t* pin_obj, logic_t value) {

	Std_ReturnType ret = E_NOT_OK;
	if (pin_obj == NULL || value > 1) {/*do nothing*/
	} else {
		if (value) {
			SET_BIT(*PORT[pin_obj->port_index], pin_obj->pin);
		} else {
			CLEAR_BIT(*PORT[pin_obj->port_index], pin_obj->pin);
		}
		ret = E_OK;
	}
	return ret;

}
/***
 *@brief read  the  logic of pin
 *arguments: pointer to struct  of  type  pint_t
 *argument : pointer to logic_t to store the value
 *return Std_ReturnType error state
 */
Std_ReturnType Mcal_Dio_Std_Get_Pin_Value(pin_t* pin_obj, logic_t *ret_value) {

	Std_ReturnType ret = E_NOT_OK;
	if (pin_obj == NULL || ret_value == NULL) {/*do nothing*/
	} else {

		*ret_value = READ_BIT(*PIN[pin_obj->port_index], pin_obj->pin);
		ret = E_OK;
	}

	return ret;

}
/*
 * @brief toggle the value  of the  pin
 * name:Mcal_Dio_Std_Toggle_Pin_Value
 * argument: pointer to struct  of  type pin_t
 *return Std_ReturnType error state
 * */
Std_ReturnType Mcal_Dio_Std_Toggle_Pin_Value(pin_t* pin_obj) {

	Std_ReturnType ret = E_NOT_OK;
	if (pin_obj == NULL) {/*do nothing*/
	} else {

		TOGGLE_BIT(*PORT[pin_obj->port_index], pin_obj->pin);

		ret = E_OK;
	}
	return ret;
}
/**
 * @brief set whole  port  with value
 * argument: port index
 * argument: value  in u8 form
 *return Std_ReturnType error state
 */
Std_ReturnType Mcal_Dio_Std_Set_Port_Direction(port_index_t port, u8 value) {

	Std_ReturnType ret = E_NOT_OK;
	if (port >= 4) {/*do nothing*/
	} else {

		*DDR[port] = value;

		ret = E_OK;
	}

	return ret;

}

/**
 * @brief set whole  port  with value
 * argument: port index
 * argument: value  in u8 form
 *return Std_ReturnType error state
 */
Std_ReturnType Mcal_Dio_Std_Set_Port_Value(port_index_t port, u8 value) {

	Std_ReturnType ret = E_NOT_OK;
	if (port >= 4) {/*do nothing*/
	} else {

		*PORT[port] = value;

		ret = E_OK;
	}

	return ret;

}

/**
 * @brief get   port  value
 * argument: port index
 * argument: pointer to store value  in
 *return Std_ReturnType error state
 */
Std_ReturnType Mcal_Dio_Std_Get_Port_Value(port_index_t port_index,
		u8 *ret_value) {
	Std_ReturnType ret = E_NOT_OK;
	if (port_index >= 4 || ret_value == NULL) {/*do nothing*/
	} else {

		*ret_value = *PORT[port_index];
		ret = E_OK;
	}

	return ret;

}


/**
 * @brief toggle   port  value
 * argument: port index
 * argument: pointer to store value  in
 *return Std_ReturnType error state
 */
Std_ReturnType Mcal_Dio_Std_Toggle_Port_Value(port_index_t port_index) {
	Std_ReturnType ret = E_NOT_OK;
	if (port_index >= 4 ) {/*do nothing*/
	} else {

		 *PORT[port_index]^=0xff;
		ret = E_OK;
	}

	return ret;

}

