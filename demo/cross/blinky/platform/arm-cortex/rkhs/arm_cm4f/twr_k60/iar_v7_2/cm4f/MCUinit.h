/*
** ###################################################################
**     This code is generated by the Device Initialization Tool.
**     It is overwritten during code generation.
**     USER MODIFICATION ARE PRESERVED ONLY INSIDE EXPLICITLY MARKED SECTIONS.
**
**     Project     : DeviceInitialization
**     Processor   : MK60DN512VLQ10
**     Version     : Component 01.000, Driver 01.04, CPU db: 3.00.000
**     Datasheet   : K60P144M100SF2V2RM Rev. 1, Jan 2012
**     Compiler    : CodeWarrior ARM C Compiler
**     Date/Time   : 2013-04-24, 08:57, # CodeGen: 18
**     Abstract    :
**
**     Contents    :
**         Function "MCU_init" initializes selected peripherals
**
**     Copyright : 1997 - 2012 Freescale, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################
*/

#ifndef __DeviceInitialization_H
#define __DeviceInitialization_H 1

/* Include shared modules, which are used for whole project */


/* User declarations and definitions */
/*   Code, declarations and definitions here will be preserved during code generation */
/* End of user declarations and definitions */


#if !defined(PE_ISR)
  #define PE_ISR(ISR_name) void ISR_name(void)
#endif

void __init_hardware(void);
/*
** ===================================================================
**     Method      :  __init_hardware (component MK60DN512LQ10)
**
**     Description :
**         Initialization code for CPU core and a clock source.
** ===================================================================
*/


void MCU_init(void);
/*
** ===================================================================
**     Method      :  MCU_init (component MK60DN512LQ10)
**
**     Description :
**         Device initialization code for selected peripherals.
** ===================================================================
*/


PE_ISR(isr_default);
/*
** ===================================================================
**     Interrupt handler : isr_default
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/



PE_ISR(isrINT_NMI);
/*
** ===================================================================
**     Interrupt handler : isrINT_NMI
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/


PE_ISR(isrINT_UART3_RX_TX);
/*
** ===================================================================
**     Interrupt handler : isrINT_UART3_RX_TX
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/



PE_ISR(isrINT_UART3_ERR);
/*
** ===================================================================
**     Interrupt handler : isrINT_UART3_ERR
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/






/* END DeviceInitialization */

#endif
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.0 [05.03]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/