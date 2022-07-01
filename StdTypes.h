/* **************************************************************************************
**       Author      :	Smart Safe Group
**       Date        :	June 1, 2022
**       Version     :	V01
**       SWC         :	StdTypes
**       Description :	Definition of standard data types
** **************************************************************************************/
#ifndef _STDTYPES_H
#define _STDTYPES_H
  /* Defined STD Types */
  typedef unsigned char             u8;
  typedef signed   char             s8;
  typedef unsigned short int        u16;
  typedef signed   short int        s16;
  typedef unsigned long int         u32;
  typedef signed   long int         s32;
  typedef unsigned long long int    u64;
  typedef signed long long int      s64;
  typedef float                     f32;
  typedef double                    f64;
  typedef u8*                       pu8;
  typedef u16*                      pu16;
  typedef f64*                      pf64;
  typedef signed char *             ps8;
  typedef signed short int *        ps16;
  typedef unsigned int *            pu32;
  typedef signed int *              ps32;
  typedef unsigned long long int *  pu64;
  typedef signed long long int *    ps64;
  typedef float *                   pf32;
  typedef long double *             pf128;

  typedef void (*tpfCallback)(void);
  /* /////////////////////////////// Defined Types ////////////////////////////////////////////// */
  /* Buffer type */
  typedef struct
  {
    u8* Data;
    u32 Size;
    u32 Index; 
  }tstrBuffer;
  /* ///////////////////////////////////////////////////////////////////////////////////////////////// */
  /* NULL Pointer */
  #define NULL                      ((void*)0)
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
  /* MACROS */
  
#endif
