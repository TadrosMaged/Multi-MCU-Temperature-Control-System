################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../code/MCAL/adc.c \
../code/MCAL/dio.c \
../code/MCAL/timer.c \
../code/MCAL/uart.c 

OBJS += \
./code/MCAL/adc.o \
./code/MCAL/dio.o \
./code/MCAL/timer.o \
./code/MCAL/uart.o 

C_DEPS += \
./code/MCAL/adc.d \
./code/MCAL/dio.d \
./code/MCAL/timer.d \
./code/MCAL/uart.d 


# Each subdirectory must supply rules for building sources it contributes
code/MCAL/%.o: ../code/MCAL/%.c code/MCAL/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


