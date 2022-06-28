#ifndef _STD_TYPES_H
#define _STD_TYPES_H

typedef void (*tpfCallback)(void);
/*	Unsigned Type	*/
typedef unsigned char 	       u8;
typedef unsigned short int     u16;
typedef unsigned long int 	   u32;
typedef unsigned long long     u64;

/*	Signed Type		*/
typedef signed char 	       s8;
typedef signed short int       s16;
typedef signed long int        s32;
typedef signed long long       s64;

/*	Unsigned Pointer Type	*/
typedef unsigned char *	       pu8;
typedef unsigned short int *   pu16;
typedef unsigned long int *    pu32;
typedef unsigned long long *   pu64;

/*	Signed Pointer Type		*/
typedef signed char *	        ps8;
typedef signed short int *      ps16;
typedef signed long int *       ps32;
typedef signed long long *      ps64;

/*	Float Type		*/
typedef float                  f32;
typedef double                 f64;
typedef long double            f128;

#define NULL  ((void *) 0)

typedef struct{
	pu8 Data;
	u32	Size;
	u32 Used;
}tstrBuffer;

/* Truthness Values */
  #define FALSE                     0
  #define TRUE                      1
  /* Remainder result */
  #define ZERO_REM                  0
  /* Compare Values */
  #define ZERO_COMP                 0
  /* Flag Values */
  #define FLAG_LOW                  0
  #define FLAG_HIGH                 1
  /* Init values */
  #define ZERO_INIT                 0
  /* Bit Slicers */
  #define FIRST_BIT_SLICER          0x01

  /* /////////////////////////////////////// OS Standard Types ////////////////////////////////// */
  /* Defined Types */
  typedef void (*pfTask_t)(void);
  typedef enum
  {
    enuStatus_Nok,
    enuStatus_Ok
  }enuStatus_t;
  typedef enum
  {
    enuSemType_Binary,
    enuSemType_Counting,
    enuSemType_Mutex
  }enuSemType_t;
  typedef struct ossem
  {
    enuSemType_t SemType;
    u32          SemValue;
    struct tcb*  SemOwner;
  }strOSSem_t;
  typedef struct tcb
  {
    u32*        TaskSP;
    u32         TaskStackSize;
    struct tcb* Next;
    struct tcb* Prev;
    pfTask_t    Task;
    u32         TaskBasePri;
    u32         TaskPri;
    u32         WaitTicks;
    strOSSem_t* Sem;
  }strTCB_t;
  typedef enum
  {
    enuOrderType_Pri,
    enuOrderType_Tick
  }enuOrderType_t;
  typedef enum
  {
    enuOS_State_Off,
    enuOS_State_On
  }enuOS_State_t;

#endif
