
#ifndef COMMON_MACROS
#define COMMON_MACROS

/* GEt a value of a bit */
#define GET_BIT(REG,BIT) (((REG)>>BIT) &(1))

/* GEt a value of a bit */
#define GET_REG(REG) (REG)

/* Set a certain bit in any register */
#define SET_BIT(REG,BIT) ((REG|=(1<<BIT)))
/* Set a register */
#define SET_REG(REG) ((REG|=0xff))

/* Clear a certain bit in any register */
#define CLR_BIT(REG,BIT) (REG&=(~(1<<BIT)))
/* Clear a register */
#define CLR_REG(REG) (REG&=(~(REG))) //Or  (REG=REG & 0x00)

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))
/* Toggle any register */
#define TOGGLE_REG(REG) (REG=REG ^ 0xff)

/* Right shift the register value with specific number of Shifts */
#define RSHIFT(REG,num) ( REG= (REG>>num) )
/* Left shift the register value with specific number of Shifts */
#define LSHIFT(REG,num) ( REG= (REG<<num) )

/* Rotate right the register value with specific number of rotates */
#define ROR(REG,num) ( REG= (REG>>num) | (REG<<(8-num)) )
/* Rotate left the register value with specific number of rotates */
#define ROL(REG,num) ( REG= (REG<<num) | (REG>>(8-num)) )

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) (1&(REG>>BIT)) 
/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) (!(1&(REG>>BIT)))

/* Assigning value to a REG */
#define ASSIGN_REG(REG,VALUE) (REG=VALUE)




/* GEt the High bits value */
#define GET_H_NIB(REG) ((REG>>4) & (0x0f))
/* GEt the Low bits value */
#define GET_L_NIB(REG) (REG & (0x0f))

/* Set the High bits value */
#define SET_H_NIB(REG) (REG|=(0xf0))
/* Set the Low bits value */
#define SET_L_NIB(REG) (REG|=(0x0f))

/* Clear the High bits value */
#define CLR_H_NIB(REG) (REG&=(0x0f))
/* Clear the Low bits value */
#define CLR_L_NIB(REG) (REG&=(0xf0))

/* Assign the High bits value */
#define ASSIGN_H_NIB(REG,VALUE) (REG=(VALUE << 4) |( REG & 0x0f)) 
/* Assign the Low bits value */
#define ASSIGN_L_NIB(REG,VALUE) (REG=(VALUE & 0x0f) |( REG & 0xf0)) 

/* Toggle the High bits value */
#define TOGGLE_H_NIB(REG) (REG^=(0xf0))
/* Toggle the Low bits value */
#define TOGGLE_L_NIB(REG) (REG^=(0x0f))

/* Swap the High & Low bits value */
#define SWAP(REG) (REG=((REG & 0x0f)<<4 )|(( REG & 0xf0)>>4)) // or ( REG= (REG>>4) | (REG << 4) )

#endif
