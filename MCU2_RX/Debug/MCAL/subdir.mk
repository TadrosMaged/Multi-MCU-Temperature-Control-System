################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/adc.c \
../MCAL/dio.c \
../MCAL/interrupt.c \
../MCAL/timer.c \
../MCAL/uart.c 

OBJS += \
./MCAL/adc.o \
./MCAL/dio.o \
./MCAL/interrupt.o \
./MCAL/timer.o \
./MCAL/uart.o 

C_DEPS += \
./MCAL/adc.d \
./MCAL/dio.d \
./MCAL/interrupt.d \
./MCAL/timer.d \
./MCAL/uart.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/%.o: ../MCAL/%.c MCAL/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


