/********************************************************************
 * Automatically generated by ARUnit
 * Filename: Rte_DoorLock_indication_.c
 * Generated on: Sun Oct 22 16:43:23 EEST
 ********************************************************************/

#include "string.h"
#include "Rte_DoorLock_indication.h"


Rte_DE_myuint8 DoorLock_indication_RP_SR_DOOR_State_Door_State;
Rte_DE_myuint8 DoorLock_indication_PP_SR_LED_State_LED_State;


const Rte_CDS_DoorLock_indication Rte_Instance_DoorLock_indication = {
&DoorLock_indication_RP_SR_DOOR_State_Door_State,
&DoorLock_indication_PP_SR_LED_State_LED_State
};

const Rte_CDS_DoorLock_indication * const Rte_Inst_DoorLock_indication = &Rte_Instance_DoorLock_indication;




void Rte_IWrite_DoorLock_indication_DoorLock_indication_PP_SR_LED_State_LED_State (myuint8 LED_State)
{
	(Rte_Inst_DoorLock_indication)->DoorLock_indication_PP_SR_LED_State_LED_State->value = LED_State;
}
myuint8* Rte_IWriteRef_DoorLock_indication_DoorLock_indication_PP_SR_LED_State_LED_State(void)
{
	return &(Rte_Inst_DoorLock_indication)->DoorLock_indication_PP_SR_LED_State_LED_State->value;
}
myuint8 Rte_IRead_DoorLock_indication_DoorLock_indication_RP_SR_DOOR_State_Door_State (void)
{
	return (Rte_Inst_DoorLock_indication)->DoorLock_indication_RP_SR_DOOR_State_Door_State->value;
}