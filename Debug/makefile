################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Modules/modbus/tcp/subdir.mk
-include Modules/modbus/rtu/subdir.mk
-include Modules/modbus/port/subdir.mk
-include Modules/modbus/functions/subdir.mk
-include Modules/modbus/ascii/subdir.mk
-include Modules/modbus/subdir.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
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

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := meteo_rs486_lcd
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
meteo_rs486_lcd.elf \

MAP_FILES += \
meteo_rs486_lcd.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
meteo_rs486_lcd.list \

OBJCOPY_HEX += \
meteo_rs486_lcd.hex \

OBJCOPY_BIN += \
meteo_rs486_lcd.bin \


# All Target
all: main-build

# Main-build Target
main-build: meteo_rs486_lcd.elf secondary-outputs

# Tool invocations
meteo_rs486_lcd.elf meteo_rs486_lcd.map: $(OBJS) $(USER_OBJS) E:\STM32CubeIDE\workspace_1.112v3\meteo_rs486_lcd\STM32F103C8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "meteo_rs486_lcd.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"E:\STM32CubeIDE\workspace_1.112v3\meteo_rs486_lcd\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="meteo_rs486_lcd.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

meteo_rs486_lcd.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "meteo_rs486_lcd.list"
	@echo 'Finished building: $@'
	@echo ' '

meteo_rs486_lcd.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "meteo_rs486_lcd.hex"
	@echo 'Finished building: $@'
	@echo ' '

meteo_rs486_lcd.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "meteo_rs486_lcd.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) default.size.stdout meteo_rs486_lcd.bin meteo_rs486_lcd.elf meteo_rs486_lcd.hex meteo_rs486_lcd.list meteo_rs486_lcd.map
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
