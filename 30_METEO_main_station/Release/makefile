################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include TERM_VT100/subdir.mk
-include MKUART/subdir.mk
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
30_METEO_main_station.lss \

FLASH_IMAGE += \
30_METEO_main_station.hex \

EEPROM_IMAGE += \
30_METEO_main_station.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: 30_METEO_main_station.elf secondary-outputs

# Tool invocations
30_METEO_main_station.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,30_METEO_main_station.map -mmcu=atmega32 -o "30_METEO_main_station.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

30_METEO_main_station.lss: 30_METEO_main_station.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S 30_METEO_main_station.elf  >"30_METEO_main_station.lss"
	@echo 'Finished building: $@'
	@echo ' '

30_METEO_main_station.hex: 30_METEO_main_station.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex 30_METEO_main_station.elf  "30_METEO_main_station.hex"
	@echo 'Finished building: $@'
	@echo ' '

30_METEO_main_station.eep: 30_METEO_main_station.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex 30_METEO_main_station.elf  "30_METEO_main_station.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: 30_METEO_main_station.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 30_METEO_main_station.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) 30_METEO_main_station.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
