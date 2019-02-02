################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include nRF24L01/subdir.mk
-include DEBOUNCE/subdir.mk
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
41_RELAY_TX_ATmega88.lss \

FLASH_IMAGE += \
41_RELAY_TX_ATmega88.hex \

EEPROM_IMAGE += \
41_RELAY_TX_ATmega88.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: 41_RELAY_TX_ATmega88.elf secondary-outputs

# Tool invocations
41_RELAY_TX_ATmega88.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,41_RELAY_TX_ATmega88.map -Wl,--gc-sections -mmcu=atmega88p -o "41_RELAY_TX_ATmega88.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

41_RELAY_TX_ATmega88.lss: 41_RELAY_TX_ATmega88.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S 41_RELAY_TX_ATmega88.elf  >"41_RELAY_TX_ATmega88.lss"
	@echo 'Finished building: $@'
	@echo ' '

41_RELAY_TX_ATmega88.hex: 41_RELAY_TX_ATmega88.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex 41_RELAY_TX_ATmega88.elf  "41_RELAY_TX_ATmega88.hex"
	@echo 'Finished building: $@'
	@echo ' '

41_RELAY_TX_ATmega88.eep: 41_RELAY_TX_ATmega88.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex 41_RELAY_TX_ATmega88.elf  "41_RELAY_TX_ATmega88.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: 41_RELAY_TX_ATmega88.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega88p 41_RELAY_TX_ATmega88.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) 41_RELAY_TX_ATmega88.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
