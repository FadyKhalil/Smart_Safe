/* **************************************************************************************
**       Author      :	Smart Safe Group
**       Date        :	June 1, 2022
**       Version     :	V01
**       SWC         :	Flash
**       Description :	Flash module files
** **************************************************************************************/
#ifndef STM32F401CC_Fls_FLS_H_
#define STM32F401CC_Fls_FLS_H_
  typedef enum
  {
    FLS_ERROR_OK,
    FLS_ERROR_NOK,
    FLS_ERROR_ARGUMENT,
    FLS_ERROR_BUSY,
    FLS_ERROR_TIMED_OUT,
    FLS_ERROR_WRITE_PROTECTION,
    FLS_ERROR_PGSERR,
    FLS_ERROR_PGPERR,
    FLS_ERROR_PGAERR,
    FLS_ERROR_OPERATION,
  } Fls_tenuError;
  typedef enum
  {
    FLS_MEMORY_SECTOR_0 = 0x00000002,
    FLS_MEMORY_SECTOR_1 = 0x0000000A,
    FLS_MEMORY_SECTOR_2 = 0x00000012,
    FLS_MEMORY_SECTOR_3 = 0x0000001A,
    FLS_MEMORY_SECTOR_4 = 0x00000022,
    FLS_MEMORY_SECTOR_5 = 0x0000002A,
    FLS_MEMORY_MASS = 0x00000004,
    DUMMY_FOR_SECTOR_ALIGNMENT_32 = 0xFFFFFFFF
  } Fls_tenuSector;
  typedef enum
  {
    FLS_PROGRAM_PARALLELISM_X08 = 0x00000000,
    FLS_PROGRAM_PARALLELISM_X16 = 0x00000100,
    FLS_PROGRAM_PARALLELISM_X32 = 0x00000200,
    FLS_PROGRAM_PARALLELISM_X64 = 0x00000300,
    DUMMY_FOR_PROGRAMMING_SIZE_ALIGNMENT_32 = 0xFFFFFFFF
  } Fls_tenuProgrammingSize;
  typedef enum
  {
    FLS_INTERRUPT_DISABLED = 0x00000000,
    FLS_INTERRUPT_END_OF_OPERATION = 0x01000000,
    FLS_INTERRUPT_ERRORS = 0x02000000,
    DUMMY_FOR_INTERRUPT_ALIGNMENT_32 = 0xFFFFFFFF
  } Fls_tenuInterrupt;
  typedef struct
  {
    Fls_tenuProgrammingSize ProgrammingSize;
    Fls_tenuInterrupt Interrupts;
  } Fls_tstrConfig;
  extern Fls_tenuError Fls_enuInit(const Fls_tstrConfig * Add_pstrConfig);
  extern Fls_tenuError Fls_enuErase(Fls_tenuSector Copy_enuSector);
  extern Fls_tenuError Fls_enuWrite(pu32 Add_pu32TargetAddress, const pu8 Add_pu8DataAddress, u16 Copy_u8Length);
#endif /* STM32F401CC_Fls_FLS_H_ */
