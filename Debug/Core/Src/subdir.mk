################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/bmp280.c \
../Core/Src/ccs811.c \
../Core/Src/filter.c \
../Core/Src/gpio.c \
../Core/Src/hdc1080.c \
../Core/Src/i2c.c \
../Core/Src/i2c_user.c \
../Core/Src/iwdg.c \
../Core/Src/loop.c \
../Core/Src/lsd1602.c \
../Core/Src/main.c \
../Core/Src/setup.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c \
../Core/Src/tim.c \
../Core/Src/uart_usb.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/bmp280.o \
./Core/Src/ccs811.o \
./Core/Src/filter.o \
./Core/Src/gpio.o \
./Core/Src/hdc1080.o \
./Core/Src/i2c.o \
./Core/Src/i2c_user.o \
./Core/Src/iwdg.o \
./Core/Src/loop.o \
./Core/Src/lsd1602.o \
./Core/Src/main.o \
./Core/Src/setup.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o \
./Core/Src/tim.o \
./Core/Src/uart_usb.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/bmp280.d \
./Core/Src/ccs811.d \
./Core/Src/filter.d \
./Core/Src/gpio.d \
./Core/Src/hdc1080.d \
./Core/Src/i2c.d \
./Core/Src/i2c_user.d \
./Core/Src/iwdg.d \
./Core/Src/loop.d \
./Core/Src/lsd1602.d \
./Core/Src/main.d \
./Core/Src/setup.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d \
./Core/Src/tim.d \
./Core/Src/uart_usb.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -c -I"../Modules/modbus/ascii" -I"../Modules/modbus/functions" -I"../Modules/modbus/include" -I"../Modules/modbus/port" -I"../Modules/modbus/rtu" -I"../Modules/modbus/tcp" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/bmp280.d ./Core/Src/bmp280.o ./Core/Src/bmp280.su ./Core/Src/ccs811.d ./Core/Src/ccs811.o ./Core/Src/ccs811.su ./Core/Src/filter.d ./Core/Src/filter.o ./Core/Src/filter.su ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/hdc1080.d ./Core/Src/hdc1080.o ./Core/Src/hdc1080.su ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/i2c_user.d ./Core/Src/i2c_user.o ./Core/Src/i2c_user.su ./Core/Src/iwdg.d ./Core/Src/iwdg.o ./Core/Src/iwdg.su ./Core/Src/loop.d ./Core/Src/loop.o ./Core/Src/loop.su ./Core/Src/lsd1602.d ./Core/Src/lsd1602.o ./Core/Src/lsd1602.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/setup.d ./Core/Src/setup.o ./Core/Src/setup.su ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/uart_usb.d ./Core/Src/uart_usb.o ./Core/Src/uart_usb.su ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su

.PHONY: clean-Core-2f-Src

