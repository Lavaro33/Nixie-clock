################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MPR121/subdir.mk
-include LED/subdir.mk
-include I2C_TWI/subdir.mk
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
39_RELAY_MPR121.lss \

FLASH_IMAGE += \
39_RELAY_MPR121.hex \

EEPROM_IMAGE += \
39_RELAY_MPR121.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: 39_RELAY_MPR121.elf secondary-outputs

# Tool invocations
39_RELAY_MPR121.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,39_RELAY_MPR121.map -mmcu=atmega88p -o "39_RELAY_MPR121.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

39_RELAY_MPR121.lss: 39_RELAY_MPR121.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S 39_RELAY_MPR121.elf  >"39_RELAY_MPR121.lss"
	@echo 'Finished building: $@'
	@echo ' '

39_RELAY_MPR121.hex: 39_RELAY_MPR121.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex 39_RELAY_MPR121.elf  "39_RELAY_MPR121.hex"
	@echo 'Finished building: $@'
	@echo ' '

39_RELAY_MPR121.eep: 39_RELAY_MPR121.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex 39_RELAY_MPR121.elf  "39_RELAY_MPR121.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: 39_RELAY_MPR121.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega88p 39_RELAY_MPR121.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) 39_RELAY_MPR121.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
