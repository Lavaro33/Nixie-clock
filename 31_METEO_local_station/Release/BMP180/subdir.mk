################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BMP180/bmp180.c 

OBJS += \
./BMP180/bmp180.o 

C_DEPS += \
./BMP180/bmp180.d 


# Each subdirectory must supply rules for building sources it contributes
BMP180/%.o: ../BMP180/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega88p -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

