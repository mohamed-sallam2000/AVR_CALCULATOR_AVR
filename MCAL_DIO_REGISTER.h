#ifndef MCAL_DIO_REGISTER
#define MCAL_DIO_REGISTER


/* section :includes */

/* section :macros declaration */

/* section :macros function  declaration */


/* section :data types */
#define DDRA_m *((volatile u8 *)0x3A)
#define PORTA_m *((volatile u8 *)0x3B)
#define PINA_m *((volatile u8 *)0x39)

#define DDRB_m *((volatile u8 *)0x37)
#define PORTB_m *((volatile u8 *)0x38)
#define PINB_m *((volatile u8 *)0x36)

#define DDRC_m *((volatile u8 *)0x34)
#define PORTC_m *((volatile u8 *)0x35)
#define PINC_m *((volatile u8 *)0x33)

#define DDRD_m *((volatile u8 *)0x31)
#define PORTD_m *((volatile u8 *)0x32)
#define PIND_m *((volatile u8 *)0x30)

/* section :function declaration  */



#endif
