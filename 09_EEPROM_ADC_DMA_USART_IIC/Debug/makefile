################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32H7xx_HAL_Driver/Src/subdir.mk
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
09_EEPROM_ADC_DMA_USART_IIC.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
09_EEPROM_ADC_DMA_USART_IIC.list \

OBJCOPY_BIN += \
09_EEPROM_ADC_DMA_USART_IIC.bin \


# All Target
all: 09_EEPROM_ADC_DMA_USART_IIC.elf secondary-outputs

# Tool invocations
09_EEPROM_ADC_DMA_USART_IIC.elf: $(OBJS) $(USER_OBJS) D:\03_WorkSpace\03_STM32Cube_HAL\09_EEPROM_ADC_DMA_USART_IIC\STM32H743IITX_FLASH.ld
	arm-none-eabi-gcc -o "09_EEPROM_ADC_DMA_USART_IIC.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"D:\03_WorkSpace\03_STM32Cube_HAL\09_EEPROM_ADC_DMA_USART_IIC\STM32H743IITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="09_EEPROM_ADC_DMA_USART_IIC.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -u _printf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

09_EEPROM_ADC_DMA_USART_IIC.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "09_EEPROM_ADC_DMA_USART_IIC.list"
	@echo 'Finished building: $@'
	@echo ' '

09_EEPROM_ADC_DMA_USART_IIC.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "09_EEPROM_ADC_DMA_USART_IIC.bin"
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
