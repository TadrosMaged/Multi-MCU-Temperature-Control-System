################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../code/HAL/dc_motor.c \
../code/HAL/temp_sensor.c 

OBJS += \
./code/HAL/dc_motor.o \
./code/HAL/temp_sensor.o 

C_DEPS += \
./code/HAL/dc_motor.d \
./code/HAL/temp_sensor.d 


# Each subdirectory must supply rules for building sources it contributes
code/HAL/%.o: ../code/HAL/%.c code/HAL/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


