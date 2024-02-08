################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Modules/modbus/tcp/mbtcp.c 

OBJS += \
./Modules/modbus/tcp/mbtcp.o 

C_DEPS += \
./Modules/modbus/tcp/mbtcp.d 


# Each subdirectory must supply rules for building sources it contributes
Modules/modbus/tcp/%.o Modules/modbus/tcp/%.su: ../Modules/modbus/tcp/%.c Modules/modbus/tcp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -c -I"../Modules/modbus/ascii" -I"../Modules/modbus/functions" -I"../Modules/modbus/include" -I"../Modules/modbus/port" -I"../Modules/modbus/rtu" -I"../Modules/modbus/tcp" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Modules-2f-modbus-2f-tcp

clean-Modules-2f-modbus-2f-tcp:
	-$(RM) ./Modules/modbus/tcp/mbtcp.d ./Modules/modbus/tcp/mbtcp.o ./Modules/modbus/tcp/mbtcp.su

.PHONY: clean-Modules-2f-modbus-2f-tcp

