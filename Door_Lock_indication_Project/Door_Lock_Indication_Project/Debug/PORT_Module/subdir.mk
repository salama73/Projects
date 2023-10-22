################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../PORT_Module/Port.c \
../PORT_Module/Port_PBcfg.c 

OBJS += \
./PORT_Module/Port.o \
./PORT_Module/Port_PBcfg.o 

C_DEPS += \
./PORT_Module/Port.d \
./PORT_Module/Port_PBcfg.d 


# Each subdirectory must supply rules for building sources it contributes
PORT_Module/Port.o: ../PORT_Module/Port.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -I"F:/DOOR_Project/CAN_Module/Common_Module" -I"F:/DOOR_Project/CAN_Module/RTOS/inc" -I"F:/DOOR_Project/CAN_Module/CMSIS_V5" -I"F:/DOOR_Project/CAN_Module/CMSIS_V5" -I"F:/DOOR_Project/CAN_Module/PWM_Module" -I"F:/DOOR_Project/CAN_Module/RTE" -I"F:/DOOR_Project/CAN_Module/DIO_Module" -I"F:/DOOR_Project/CAN_Module/SWCs" -I"F:/DOOR_Project/CAN_Module/PORT_Module" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"PORT_Module/Port.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
PORT_Module/Port_PBcfg.o: ../PORT_Module/Port_PBcfg.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -I"F:/DOOR_Project/CAN_Module/Common_Module" -I"F:/DOOR_Project/CAN_Module/RTOS/inc" -I"F:/DOOR_Project/CAN_Module/CMSIS_V5" -I"F:/DOOR_Project/CAN_Module/CMSIS_V5" -I"F:/DOOR_Project/CAN_Module/PWM_Module" -I"F:/DOOR_Project/CAN_Module/RTE" -I"F:/DOOR_Project/CAN_Module/DIO_Module" -I"F:/DOOR_Project/CAN_Module/SWCs" -I"F:/DOOR_Project/CAN_Module/PORT_Module" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"PORT_Module/Port_PBcfg.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

