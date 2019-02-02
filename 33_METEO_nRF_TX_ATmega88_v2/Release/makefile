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
33_METEO_nRF_TX_ATmega88_v2.lss \

FLASH_IMAGE += \
33_METEO_nRF_TX_ATmega88_v2.hex \

EEPROM_IMAGE += \
33_METEO_nRF_TX_ATmega88_v2.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: 33_METEO_nRF_TX_ATmega88_v2.elf secondary-outputs

# Tool invocations
33_METEO_nRF_TX_ATmega88_v2.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,33_METEO_nRF_TX_ATmega88_v2.map -Wl,--gc-sections -mmcu=atmega88p -o "33_METEO_nRF_TX_ATmega88_v2.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

33_METEO_nRF_TX_ATmega88_v2.lss: 33_METEO_nRF_TX_ATmega88_v2.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S 33_METEO_nRF_TX_ATmega88_v2.elf  >"33_METEO_nRF_TX_ATmega88_v2.lss"
	@echo 'Finished building: $@'
	@echo ' '

33_METEO_nRF_TX_ATmega88_v2.hex: 33_METEO_nRF_TX_ATmega88_v2.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex 33_METEO_nRF_TX_ATmega88_v2.elf  "33_METEO_nRF_TX_ATmega88_v2.hex"
	@echo 'Finished building: $@'
	@echo ' '

33_METEO_nRF_TX_ATmega88_v2.eep: 33_METEO_nRF_TX_ATmega88_v2.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex 33_METEO_nRF_TX_ATmega88_v2.elf  "33_METEO_nRF_TX_ATmega88_v2.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: 33_METEO_nRF_TX_ATmega88_v2.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega88p 33_METEO_nRF_TX_ATmega88_v2.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) 33_METEO_nRF_TX_ATmega88_v2.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
