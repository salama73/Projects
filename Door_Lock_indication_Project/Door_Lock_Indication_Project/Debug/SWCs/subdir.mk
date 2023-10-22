################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SWCs/DoorLock_indication.c \
../SWCs/ECU_Abstraction_SWC.c \
../SWCs/LED_Actuator.c \
../SWCs/Read_Door_State.c 

OBJS += \
./SWCs/DoorLock_indication.o \
./SWCs/ECU_Abstraction_SWC.o \
./SWCs/LED_Actuator.o \
./SWCs/Read_Door_State.o 

C_DEPS += \
./SWCs/DoorLock_indication.d \
./SWCs/ECU_Abstraction_SWC.d \
./SWCs/LED_Actuator.d \
./SWCs/Read_Door_State.d 


# Each subdirectory must supply rules for building sources it contributes
SWCs/DoorLock_indication.o: ../SWCs/DoorLock_indication.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -I"F:/DOOR_Project/CAN_Module/Common_Module" -I"F:/DOOR_Project/CAN_Module/RTOS/inc" -I"F:/DOOR_Project/CAN_Module/CMSIS_V5" -I"F:/DOOR_Project/CAN_Module/CMSIS_V5" -I"F:/DOOR_Project/CAN_Module/PWM_Module" -I"F:/DOOR_Project/CAN_Module/RTE" -I"F:/DOOR_Project/CAN_Module/DIO_Module" -I"F:/DOOR_Project/CAN_Module/SWCs" -I"F:/DOOR_Project/CAN_Module/PORT_Module" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"SWCs/DoorLock_indication.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
SWCs/ECU_Abstraction_SWC.o: ../SWCs/ECU_Abstraction_SWC.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -I"F:/DOOR_Project/CAN_Module/Common_Module" -I"F:/DOOR_Project/CAN_Module/RTOS/inc" -I"F:/DOOR_Project/CAN_Module/CMSIS_V5" -I"F:/DOOR_Project/CAN_Module/CMSIS_V5" -I"F:/DOOR_Project/CAN_Module/PWM_Module" -I"F:/DOOR_Project/CAN_Module/RTE" -I"F:/DOOR_Project/CAN_Module/DIO_Module" -I"F:/DOOR_Project/CAN_Module/SWCs" -I"F:/DOOR_Project/CAN_Module/PORT_Module" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"SWCs/ECU_Abstraction_SWC.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
SWCs/LED_Actuator.o: ../SWCs/LED_Actuator.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -I"F:/DOOR_Project/CAN_Module/Common_Module" -I"F:/DOOR_Project/CAN_Module/RTOS/inc" -I"F:/DOOR_Project/CAN_Module/CMSIS_V5" -I"F:/DOOR_Project/CAN_Module/CMSIS_V5" -I"F:/DOOR_Project/CAN_Module/PWM_Module" -I"F:/DOOR_Project/CAN_Module/RTE" -I"F:/DOOR_Project/CAN_Module/DIO_Module" -I"F:/DOOR_Project/CAN_Module/SWCs" -I"F:/DOOR_Project/CAN_Module/PORT_Module" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"SWCs/LED_Actuator.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
SWCs/Read_Door_State.o: ../SWCs/Read_Door_State.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -I"F:/DOOR_Project/CAN_Module/Common_Module" -I"F:/DOOR_Project/CAN_Module/RTOS/inc" -I"F:/DOOR_Project/CAN_Module/CMSIS_V5" -I"F:/DOOR_Project/CAN_Module/CMSIS_V5" -I"F:/DOOR_Project/CAN_Module/PWM_Module" -I"F:/DOOR_Project/CAN_Module/RTE" -I"F:/DOOR_Project/CAN_Module/DIO_Module" -I"F:/DOOR_Project/CAN_Module/SWCs" -I"F:/DOOR_Project/CAN_Module/PORT_Module" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"SWCs/Read_Door_State.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

