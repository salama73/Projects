################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stm32_f103c6_Drivers/stm32_f103c6_EXTI.c \
../stm32_f103c6_Drivers/stm32_f103c6_GPIO.c \
../stm32_f103c6_Drivers/stm32_f103c6_I2C.c \
../stm32_f103c6_Drivers/stm32_f103c6_RCC.c \
../stm32_f103c6_Drivers/stm32_f103c6_SPI.c \
../stm32_f103c6_Drivers/stm32_f103c6_USART.c 

OBJS += \
./stm32_f103c6_Drivers/stm32_f103c6_EXTI.o \
./stm32_f103c6_Drivers/stm32_f103c6_GPIO.o \
./stm32_f103c6_Drivers/stm32_f103c6_I2C.o \
./stm32_f103c6_Drivers/stm32_f103c6_RCC.o \
./stm32_f103c6_Drivers/stm32_f103c6_SPI.o \
./stm32_f103c6_Drivers/stm32_f103c6_USART.o 

C_DEPS += \
./stm32_f103c6_Drivers/stm32_f103c6_EXTI.d \
./stm32_f103c6_Drivers/stm32_f103c6_GPIO.d \
./stm32_f103c6_Drivers/stm32_f103c6_I2C.d \
./stm32_f103c6_Drivers/stm32_f103c6_RCC.d \
./stm32_f103c6_Drivers/stm32_f103c6_SPI.d \
./stm32_f103c6_Drivers/stm32_f103c6_USART.d 


# Each subdirectory must supply rules for building sources it contributes
stm32_f103c6_Drivers/stm32_f103c6_EXTI.o: ../stm32_f103c6_Drivers/stm32_f103c6_EXTI.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/New folder (3)/STM32CubeIDE/workspace_1.4.0/Drivers/HAL/inc" -I"D:/New folder (3)/STM32CubeIDE/workspace_1.4.0/Drivers/stm32_f103c6_Drivers/inc" -I"D:/New folder (3)/STM32CubeIDE/workspace_1.4.0/Drivers/stm32_f103c6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32_f103c6_Drivers/stm32_f103c6_EXTI.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32_f103c6_Drivers/stm32_f103c6_GPIO.o: ../stm32_f103c6_Drivers/stm32_f103c6_GPIO.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/New folder (3)/STM32CubeIDE/workspace_1.4.0/Drivers/HAL/inc" -I"D:/New folder (3)/STM32CubeIDE/workspace_1.4.0/Drivers/stm32_f103c6_Drivers/inc" -I"D:/New folder (3)/STM32CubeIDE/workspace_1.4.0/Drivers/stm32_f103c6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32_f103c6_Drivers/stm32_f103c6_GPIO.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32_f103c6_Drivers/stm32_f103c6_I2C.o: ../stm32_f103c6_Drivers/stm32_f103c6_I2C.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/New folder (3)/STM32CubeIDE/workspace_1.4.0/Drivers/HAL/inc" -I"D:/New folder (3)/STM32CubeIDE/workspace_1.4.0/Drivers/stm32_f103c6_Drivers/inc" -I"D:/New folder (3)/STM32CubeIDE/workspace_1.4.0/Drivers/stm32_f103c6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32_f103c6_Drivers/stm32_f103c6_I2C.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32_f103c6_Drivers/stm32_f103c6_RCC.o: ../stm32_f103c6_Drivers/stm32_f103c6_RCC.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/New folder (3)/STM32CubeIDE/workspace_1.4.0/Drivers/HAL/inc" -I"D:/New folder (3)/STM32CubeIDE/workspace_1.4.0/Drivers/stm32_f103c6_Drivers/inc" -I"D:/New folder (3)/STM32CubeIDE/workspace_1.4.0/Drivers/stm32_f103c6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32_f103c6_Drivers/stm32_f103c6_RCC.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32_f103c6_Drivers/stm32_f103c6_SPI.o: ../stm32_f103c6_Drivers/stm32_f103c6_SPI.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/New folder (3)/STM32CubeIDE/workspace_1.4.0/Drivers/HAL/inc" -I"D:/New folder (3)/STM32CubeIDE/workspace_1.4.0/Drivers/stm32_f103c6_Drivers/inc" -I"D:/New folder (3)/STM32CubeIDE/workspace_1.4.0/Drivers/stm32_f103c6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32_f103c6_Drivers/stm32_f103c6_SPI.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32_f103c6_Drivers/stm32_f103c6_USART.o: ../stm32_f103c6_Drivers/stm32_f103c6_USART.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/New folder (3)/STM32CubeIDE/workspace_1.4.0/Drivers/HAL/inc" -I"D:/New folder (3)/STM32CubeIDE/workspace_1.4.0/Drivers/stm32_f103c6_Drivers/inc" -I"D:/New folder (3)/STM32CubeIDE/workspace_1.4.0/Drivers/stm32_f103c6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32_f103c6_Drivers/stm32_f103c6_USART.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

