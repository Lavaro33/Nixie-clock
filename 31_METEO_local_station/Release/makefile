################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include LCD/subdir.mk
-include I2C_TWI/subdir.mk
-include HTU21/subdir.mk
-include BMP180/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
31_METEO_local_station.lss \

FLASH_IMAGE += \
31_METEO_local_station.hex \

EEPROM_IMAGE += \
31_METEO_local_station.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: 31_METEO_local_station.elf secondary-outputs

# Tool invocations
31_METEO_local_station.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,31_METEO_local_station.map -mmcu=atmega88p -o "31_METEO_local_station.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

31_METEO_local_station.lss: 31_METEO_local_station.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S 31_METEO_local_station.elf  >"31_METEO_local_station.lss"
	@echo 'Finished building: $@'
	@echo ' '

31_METEO_local_station.hex: 31_METEO_local_station.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex 31_METEO_local_station.elf  "31_METEO_local_station.hex"
	@echo 'Finished building: $@'
	@echo ' '

31_METEO_local_station.eep: 31_METEO_local_station.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex 31_METEO_local_station.elf  "31_METEO_local_station.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: 31_METEO_local_station.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega88p 31_METEO_local_station.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) 31_METEO_local_station.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
