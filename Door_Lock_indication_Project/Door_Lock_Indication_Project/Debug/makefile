################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include SWCs/subdir.mk
-include RTOS/subdir.mk
-include RTE/subdir.mk
-include PWM_Module/subdir.mk
-include PORT_Module/subdir.mk
-include DIO_Module/subdir.mk
-include Common_Module/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
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
EXECUTABLES += \
Door_Lock_Indication_Project.axf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Door_Lock_Indication_Project.list \

OBJCOPY_BIN += \
Door_Lock_Indication_Project.bin \


# All Target
all: Door_Lock_Indication_Project.axf secondary-outputs

# Tool invocations
Door_Lock_Indication_Project.axf: $(OBJS) $(USER_OBJS) F:\DOOR_Project\CAN_Module\STM32F103C8TX_FLASH.ld
	arm-none-eabi-gcc -o "Door_Lock_Indication_Project.axf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"F:\DOOR_Project\CAN_Module\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Door_Lock_Indication_Project.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Door_Lock_Indication_Project.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Door_Lock_Indication_Project.list"
	@echo 'Finished building: $@'
	@echo ' '

Door_Lock_Indication_Project.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Door_Lock_Indication_Project.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
