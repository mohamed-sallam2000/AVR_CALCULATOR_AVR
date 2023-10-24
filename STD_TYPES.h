
/* section :includes */



/* section :macros function  declaration */

/* section :macros declaration */

#ifndef STD_TYPES_H
#define STD_TYPES_H
#define STD_HIGH        0x01
#define STD_LOW         0x00
#define NULL            0x00
#define CONFIG_ENEABLE  0X01
#define CONFIG_DISABLE  0X00

#define STD_ACTIVE      0x01
#define STD_IDEL        0x00
#define BIT_MASK        0x01
#define  E_OK           (Std_ReturnType)0x01
#define  E_NOT_OK       (Std_ReturnType)0x00

/* section :macros function  declaration */

#define SET_BIT(REG,BIT_POS) (REG|=(BIT_MASK<<BIT_POS))
#define CLEAR_BIT(REG,BIT_POS) (REG&=~(BIT_MASK<<BIT_POS))
#define TOGGLE_BIT(REG,BIT_POS) (REG^=(BIT_MASK<<BIT_POS))
#define READ_BIT(REG,BIT_POS)  ((REG>>BIT_POS)&BIT_MASK)

/* section :datatypes */

typedef unsigned char  u8;  
typedef unsigned short u16;
typedef unsigned long   u32;

typedef signed char  s8;
typedef signed short S16;
typedef signed long   s32;
typedef u8  Std_ReturnType;

#endif

