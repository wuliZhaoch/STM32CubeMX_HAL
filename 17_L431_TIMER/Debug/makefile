################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32L4xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
L431_TIMER.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
L431_TIMER.list \

OBJCOPY_BIN += \
L431_TIMER.bin \


# All Target
all: L431_TIMER.elf secondary-outputs

# Tool invocations
L431_TIMER.elf: $(OBJS) $(USER_OBJS) D:\03_WorkSpace\03_STM32Cube_HAL\L431_TIMER\STM32L431CCTX_FLASH.ld
	arm-none-eabi-gcc -o "L431_TIMER.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"D:\03_WorkSpace\03_STM32Cube_HAL\L431_TIMER\STM32L431CCTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="L431_TIMER.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

L431_TIMER.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "L431_TIMER.list"
	@echo 'Finished building: $@'
	@echo ' '

L431_TIMER.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "L431_TIMER.bin"
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
