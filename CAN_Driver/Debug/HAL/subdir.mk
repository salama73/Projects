################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/Door.c \
../HAL/EEPROM.c \
../HAL/Fan.c \
../HAL/Flame_Sensor.c \
../HAL/IR_Sensor.c \
../HAL/Keypad.c \
../HAL/LCD.c \
../HAL/Servo.c 

OBJS += \
./HAL/Door.o \
./HAL/EEPROM.o \
./HAL/Fan.o \
./HAL/Flame_Sensor.o \
./HAL/IR_Sensor.o \
./HAL/Keypad.o \
./HAL/LCD.o \
./HAL/Servo.o 

C_DEPS += \
./HAL/Door.d \
./HAL/EEPROM.d \
./HAL/Fan.d \
./HAL/Flame_Sensor.d \
./HAL/IR_Sensor.d \
./HAL/Keypad.d \
./HAL/LCD.d \
./HAL/Servo.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/Door.o: ../HAL/Door.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"F:/CAN_Driver/MY_RTOS/inc" -I"F:/CAN_Driver/CMSIS_V5" -I"F:/CAN_Driver/HAL/inc" -I"F:/CAN_Driver/stm32_f103c6_Drivers/inc" -I"F:/CAN_Driver/stm32_f103c6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/Door.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
HAL/EEPROM.o: ../HAL/EEPROM.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"F:/CAN_Driver/MY_RTOS/inc" -I"F:/CAN_Driver/CMSIS_V5" -I"F:/CAN_Driver/HAL/inc" -I"F:/CAN_Driver/stm32_f103c6_Drivers/inc" -I"F:/CAN_Driver/stm32_f103c6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/EEPROM.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
HAL/Fan.o: ../HAL/Fan.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"F:/CAN_Driver/MY_RTOS/inc" -I"F:/CAN_Driver/CMSIS_V5" -I"F:/CAN_Driver/HAL/inc" -I"F:/CAN_Driver/stm32_f103c6_Drivers/inc" -I"F:/CAN_Driver/stm32_f103c6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/Fan.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
HAL/Flame_Sensor.o: ../HAL/Flame_Sensor.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"F:/CAN_Driver/MY_RTOS/inc" -I"F:/CAN_Driver/CMSIS_V5" -I"F:/CAN_Driver/HAL/inc" -I"F:/CAN_Driver/stm32_f103c6_Drivers/inc" -I"F:/CAN_Driver/stm32_f103c6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/Flame_Sensor.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
HAL/IR_Sensor.o: ../HAL/IR_Sensor.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"F:/CAN_Driver/MY_RTOS/inc" -I"F:/CAN_Driver/CMSIS_V5" -I"F:/CAN_Driver/HAL/inc" -I"F:/CAN_Driver/stm32_f103c6_Drivers/inc" -I"F:/CAN_Driver/stm32_f103c6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/IR_Sensor.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
HAL/Keypad.o: ../HAL/Keypad.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"F:/CAN_Driver/MY_RTOS/inc" -I"F:/CAN_Driver/CMSIS_V5" -I"F:/CAN_Driver/HAL/inc" -I"F:/CAN_Driver/stm32_f103c6_Drivers/inc" -I"F:/CAN_Driver/stm32_f103c6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/Keypad.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
HAL/LCD.o: ../HAL/LCD.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"F:/CAN_Driver/MY_RTOS/inc" -I"F:/CAN_Driver/CMSIS_V5" -I"F:/CAN_Driver/HAL/inc" -I"F:/CAN_Driver/stm32_f103c6_Drivers/inc" -I"F:/CAN_Driver/stm32_f103c6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/LCD.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
HAL/Servo.o: ../HAL/Servo.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"F:/CAN_Driver/MY_RTOS/inc" -I"F:/CAN_Driver/CMSIS_V5" -I"F:/CAN_Driver/HAL/inc" -I"F:/CAN_Driver/stm32_f103c6_Drivers/inc" -I"F:/CAN_Driver/stm32_f103c6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/Servo.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

