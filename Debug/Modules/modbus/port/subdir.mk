################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Modules/modbus/port/mt_port.c \
../Modules/modbus/port/portevent.c \
../Modules/modbus/port/portserial.c \
../Modules/modbus/port/porttimer.c 

OBJS += \
./Modules/modbus/port/mt_port.o \
./Modules/modbus/port/portevent.o \
./Modules/modbus/port/portserial.o \
./Modules/modbus/port/porttimer.o 

C_DEPS += \
./Modules/modbus/port/mt_port.d \
./Modules/modbus/port/portevent.d \
./Modules/modbus/port/portserial.d \
./Modules/modbus/port/porttimer.d 


# Each subdirectory must supply rules for building sources it contributes
Modules/modbus/port/%.o Modules/modbus/port/%.su: ../Modules/modbus/port/%.c Modules/modbus/port/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -c -I"../Modules/modbus/ascii" -I"../Modules/modbus/functions" -I"../Modules/modbus/include" -I"../Modules/modbus/port" -I"../Modules/modbus/rtu" -I"../Modules/modbus/tcp" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Modules-2f-modbus-2f-port

clean-Modules-2f-modbus-2f-port:
	-$(RM) ./Modules/modbus/port/mt_port.d ./Modules/modbus/port/mt_port.o ./Modules/modbus/port/mt_port.su ./Modules/modbus/port/portevent.d ./Modules/modbus/port/portevent.o ./Modules/modbus/port/portevent.su ./Modules/modbus/port/portserial.d ./Modules/modbus/port/portserial.o ./Modules/modbus/port/portserial.su ./Modules/modbus/port/porttimer.d ./Modules/modbus/port/porttimer.o ./Modules/modbus/port/porttimer.su

.PHONY: clean-Modules-2f-modbus-2f-port

