################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include SWITCH/subdir.mk
-include LCD/subdir.mk
-include DEBOUNCE/subdir.mk
-include 1Wire/subdir.mk
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
36_WYTRAWIARKA.lss \

FLASH_IMAGE += \
36_WYTRAWIARKA.hex \

EEPROM_IMAGE += \
36_WYTRAWIARKA.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: 36_WYTRAWIARKA.elf secondary-outputs

# Tool invocations
36_WYTRAWIARKA.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,36_WYTRAWIARKA.map -mmcu=atmega32 -o "36_WYTRAWIARKA.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

36_WYTRAWIARKA.lss: 36_WYTRAWIARKA.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S 36_WYTRAWIARKA.elf  >"36_WYTRAWIARKA.lss"
	@echo 'Finished building: $@'
	@echo ' '

36_WYTRAWIARKA.hex: 36_WYTRAWIARKA.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex 36_WYTRAWIARKA.elf  "36_WYTRAWIARKA.hex"
	@echo 'Finished building: $@'
	@echo ' '

36_WYTRAWIARKA.eep: 36_WYTRAWIARKA.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex 36_WYTRAWIARKA.elf  "36_WYTRAWIARKA.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: 36_WYTRAWIARKA.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 36_WYTRAWIARKA.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) 36_WYTRAWIARKA.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
