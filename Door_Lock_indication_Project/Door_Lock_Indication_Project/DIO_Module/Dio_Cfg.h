/******************************************************************************
* @Module      :	 DIO
* @File Name   :	 Dio_Cfg.h
* @Description :	 the Pre-compile configuration of the AUTOSAR Basic Software module PORT Driver.
* Author       :	 Salama Mohamed
*******************************************************************************/
/******************************************************************************
* Project				: Door_Lock_Indication
* Platform				: STM32F103C8
* Autosar Version		: 4.8.0
* SW Version		    : 1.0.0
******************************************************************************/
#ifndef DIO_CFG_H_
#define DIO_CFG_H_
/*****************************************************************************
				General DIO module configuration parameters.
*****************************************************************************/
//Switches the development error detection and notification on or off.
#define DioDevErrorDetect			TRUE
//Adds / removes the service Dio_FlipChannel() from the code.
#define DioFlipChannelApi			FALSE
//Adds / removes the service Dio_MaskedWritePort() from the code.
#define DioMaskedWritePortApi		FALSE
//Adds / removes the service Dio_ GetVersionInfo() from the code.
#define DioVersionInfoApi			TRUE
/*****************************************************************************
				Configuration of individual DIO ports.
****************************************************************************/
//Numeric identifier of the DIO port.
#define DioPort_A				(Dio_PortType)0
#define DioPort_B				(Dio_PortType)1
#define DioPort_C				(Dio_PortType)2
//Channel Id of the DIO channel.
#define channel_0				(Dio_ChannelType)0
#define channel_1				(Dio_ChannelType)1
#define channel_2				(Dio_ChannelType)2
#define channel_3				(Dio_ChannelType)3
#define channel_4				(Dio_ChannelType)4
#define channel_5				(Dio_ChannelType)5
#define channel_6				(Dio_ChannelType)6
#define channel_7				(Dio_ChannelType)7
#define channel_8				(Dio_ChannelType)8
#define channel_9				(Dio_ChannelType)9
#define channel_10				(Dio_ChannelType)10
#define channel_11				(Dio_ChannelType)11
#define channel_12				(Dio_ChannelType)12
#define channel_13				(Dio_ChannelType)13
#define channel_14				(Dio_ChannelType)14
#define channel_15				(Dio_ChannelType)15
#define channel_16				(Dio_ChannelType)16
#define channel_17				(Dio_ChannelType)17
#define channel_18				(Dio_ChannelType)18
#define channel_19				(Dio_ChannelType)19
#define channel_20				(Dio_ChannelType)20
#define channel_21				(Dio_ChannelType)21
#define channel_22				(Dio_ChannelType)22
#define channel_23				(Dio_ChannelType)23
#define channel_24				(Dio_ChannelType)24
#define channel_25				(Dio_ChannelType)25
#define channel_26				(Dio_ChannelType)26
#define channel_27				(Dio_ChannelType)27
#define channel_28				(Dio_ChannelType)28
#define channel_29				(Dio_ChannelType)29
#define channel_30				(Dio_ChannelType)30
#define channel_31				(Dio_ChannelType)31
#define channel_32				(Dio_ChannelType)32
#define channel_45				(Dio_ChannelType)45
#define channel_46				(Dio_ChannelType)46
#define channel_47				(Dio_ChannelType)47
//Number of channel
#define MAX_Number_Channel		(Dio_ChannelType)47
#define DIO_INSTANCE_ZERO			0
#endif /* DIO_CFG_H_ */
