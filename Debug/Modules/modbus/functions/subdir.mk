################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Modules/modbus/functions/mbfunccoils.c \
../Modules/modbus/functions/mbfuncdiag.c \
../Modules/modbus/functions/mbfuncdisc.c \
../Modules/modbus/functions/mbfuncholding.c \
../Modules/modbus/functions/mbfuncinput.c \
../Modules/modbus/functions/mbfuncother.c \
../Modules/modbus/functions/mbutils.c 

OBJS += \
./Modules/modbus/functions/mbfunccoils.o \
./Modules/modbus/functions/mbfuncdiag.o \
./Modules/modbus/functions/mbfuncdisc.o \
./Modules/modbus/functions/mbfuncholding.o \
./Modules/modbus/functions/mbfuncinput.o \
./Modules/modbus/functions/mbfuncother.o \
./Modules/modbus/functions/mbutils.o 

C_DEPS += \
./Modules/modbus/functions/mbfunccoils.d \
./Modules/modbus/functions/mbfuncdiag.d \
./Modules/modbus/functions/mbfuncdisc.d \
./Modules/modbus/functions/mbfuncholding.d \
./Modules/modbus/functions/mbfuncinput.d \
./Modules/modbus/functions/mbfuncother.d \
./Modules/modbus/functions/mbutils.d 


# Each subdirectory must supply rules for building sources it contributes
Modules/modbus/functions/%.o Modules/modbus/functions/%.su: ../Modules/modbus/functions/%.c Modules/modbus/functions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -c -I"../Modules/modbus/ascii" -I"../Modules/modbus/functions" -I"../Modules/modbus/include" -I"../Modules/modbus/port" -I"../Modules/modbus/rtu" -I"../Modules/modbus/tcp" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Modules-2f-modbus-2f-functions

clean-Modules-2f-modbus-2f-functions:
	-$(RM) ./Modules/modbus/functions/mbfunccoils.d ./Modules/modbus/functions/mbfunccoils.o ./Modules/modbus/functions/mbfunccoils.su ./Modules/modbus/functions/mbfuncdiag.d ./Modules/modbus/functions/mbfuncdiag.o ./Modules/modbus/functions/mbfuncdiag.su ./Modules/modbus/functions/mbfuncdisc.d ./Modules/modbus/functions/mbfuncdisc.o ./Modules/modbus/functions/mbfuncdisc.su ./Modules/modbus/functions/mbfuncholding.d ./Modules/modbus/functions/mbfuncholding.o ./Modules/modbus/functions/mbfuncholding.su ./Modules/modbus/functions/mbfuncinput.d ./Modules/modbus/functions/mbfuncinput.o ./Modules/modbus/functions/mbfuncinput.su ./Modules/modbus/functions/mbfuncother.d ./Modules/modbus/functions/mbfuncother.o ./Modules/modbus/functions/mbfuncother.su ./Modules/modbus/functions/mbutils.d ./Modules/modbus/functions/mbutils.o ./Modules/modbus/functions/mbutils.su

.PHONY: clean-Modules-2f-modbus-2f-functions

