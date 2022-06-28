################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Fls.c \
../src/GPIO_program.c \
../src/Nvic.c \
../src/Parse.c \
../src/RCC.c \
../src/RCC_cfg.c \
../src/Systick.c \
../src/Systick_cfg.c \
../src/Usart.c \
../src/main.c 

OBJS += \
./src/Fls.o \
./src/GPIO_program.o \
./src/Nvic.o \
./src/Parse.o \
./src/RCC.o \
./src/RCC_cfg.o \
./src/Systick.o \
./src/Systick_cfg.o \
./src/Usart.o \
./src/main.o 

C_DEPS += \
./src/Fls.d \
./src/GPIO_program.d \
./src/Nvic.d \
./src/Parse.d \
./src/RCC.d \
./src/RCC_cfg.d \
./src/Systick.d \
./src/Systick_cfg.d \
./src/Usart.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F401xC -DUSE_HAL_DRIVER -DHSE_VALUE=25000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


