################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../nRF24L01/SPI.c \
../nRF24L01/nRF24L01.c 

OBJS += \
./nRF24L01/SPI.o \
./nRF24L01/nRF24L01.o 

C_DEPS += \
./nRF24L01/SPI.d \
./nRF24L01/nRF24L01.d 


# Each subdirectory must supply rules for building sources it contributes
nRF24L01/%.o: ../nRF24L01/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega88p -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


