/********************************************************************
 * Automatically generated by ARUnit
 * Filename: Rte_ECU_Abstraction_SWC_.c
 * Generated on: Sun Oct 22 16:43:23 EEST
 ********************************************************************/

#include "string.h"
#include "Rte_ECU_Abstraction_SWC.h"


extern Rte_DE_myuint8 Read_Door_Sensor_PP_SR_DOOR_State_Sensor_Reading;


const Rte_CDS_ECU_Abstraction_SWC Rte_Instance_ECU_Abstraction_SWC = {
&Read_Door_Sensor_PP_SR_DOOR_State_Sensor_Reading
};

const Rte_CDS_ECU_Abstraction_SWC * const Rte_Inst_ECU_Abstraction_SWC = &Rte_Instance_ECU_Abstraction_SWC;




void Rte_IWrite_ECU_Abstraction_SWC_Read_Door_Sensor_PP_SR_DOOR_State_Sensor_Reading (myuint8 Sensor_Reading)
{
	(Rte_Inst_ECU_Abstraction_SWC)->Read_Door_Sensor_PP_SR_DOOR_State_Sensor_Reading->value = Sensor_Reading;
}
myuint8* Rte_IWriteRef_ECU_Abstraction_SWC_Read_Door_Sensor_PP_SR_DOOR_State_Sensor_Reading(void)
{
	return &(Rte_Inst_ECU_Abstraction_SWC)->Read_Door_Sensor_PP_SR_DOOR_State_Sensor_Reading->value;
}