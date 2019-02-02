################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include nRF24L01/subdir.mk
-include MPR121/subdir.mk
-include LED/subdir.mk
-include I2C_TWI/subdir.mk
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
42_RELAY_TX_ATmega88_touch.lss \

FLASH_IMAGE += \
42_RELAY_TX_ATmega88_touch.hex \

EEPROM_IMAGE += \
42_RELAY_TX_ATmega88_touch.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: 42_RELAY_TX_ATmega88_touch.elf secondary-outputs

# Tool invocations
42_RELAY_TX_ATmega88_touch.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,42_RELAY_TX_ATmega88_touch.map -mmcu=atmega88p -o "42_RELAY_TX_ATmega88_touch.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

42_RELAY_TX_ATmega88_touch.lss: 42_RELAY_TX_ATmega88_touch.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S 42_RELAY_TX_ATmega88_touch.elf  >"42_RELAY_TX_ATmega88_touch.lss"
	@echo 'Finished building: $@'
	@echo ' '

42_RELAY_TX_ATmega88_touch.hex: 42_RELAY_TX_ATmega88_touch.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex 42_RELAY_TX_ATmega88_touch.elf  "42_RELAY_TX_ATmega88_touch.hex"
	@echo 'Finished building: $@'
	@echo ' '

42_RELAY_TX_ATmega88_touch.eep: 42_RELAY_TX_ATmega88_touch.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex 42_RELAY_TX_ATmega88_touch.elf  "42_RELAY_TX_ATmega88_touch.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: 42_RELAY_TX_ATmega88_touch.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega88p 42_RELAY_TX_ATmega88_touch.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) 42_RELAY_TX_ATmega88_touch.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
