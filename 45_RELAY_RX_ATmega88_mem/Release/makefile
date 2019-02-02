################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include nRF24L01/subdir.mk
-include LED/subdir.mk
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
45_RELAY_RX_ATmega88_mem.lss \

FLASH_IMAGE += \
45_RELAY_RX_ATmega88_mem.hex \

EEPROM_IMAGE += \
45_RELAY_RX_ATmega88_mem.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: 45_RELAY_RX_ATmega88_mem.elf secondary-outputs

# Tool invocations
45_RELAY_RX_ATmega88_mem.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,45_RELAY_RX_ATmega88_mem.map -mmcu=atmega88p -o "45_RELAY_RX_ATmega88_mem.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

45_RELAY_RX_ATmega88_mem.lss: 45_RELAY_RX_ATmega88_mem.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S 45_RELAY_RX_ATmega88_mem.elf  >"45_RELAY_RX_ATmega88_mem.lss"
	@echo 'Finished building: $@'
	@echo ' '

45_RELAY_RX_ATmega88_mem.hex: 45_RELAY_RX_ATmega88_mem.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex 45_RELAY_RX_ATmega88_mem.elf  "45_RELAY_RX_ATmega88_mem.hex"
	@echo 'Finished building: $@'
	@echo ' '

45_RELAY_RX_ATmega88_mem.eep: 45_RELAY_RX_ATmega88_mem.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex 45_RELAY_RX_ATmega88_mem.elf  "45_RELAY_RX_ATmega88_mem.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: 45_RELAY_RX_ATmega88_mem.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega88p 45_RELAY_RX_ATmega88_mem.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) 45_RELAY_RX_ATmega88_mem.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
