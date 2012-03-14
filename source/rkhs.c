/*
 *	file: rkhs.c
 *	Last updated for version: 1.0.00
 *	Date of the last update:  Feb 22, 2012
 *
 * 	Copyright (C) 2010 Leandro Francucci. All rights reserved.
 *
 * 	RKH is free software: you can redistribute it and/or modify
 * 	it under the terms of the GNU General Public License as published by
 * 	the Free Software Foundation, either version 3 of the License, or
 * 	(at your option) any later version.
 *
 *  RKH is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RKH, see copying.txt file.
 *
 * Contact information:
 * RKH web site:	http://
 * e-mail:			francuccilea@gmail.com
 */

/**
 * 	\file rkhs.c
 *	\brief
 *	This module implements a native, simple and cooperative scheduler called 
 *	RKS to deal with multiple event-driven state machines.
 *
 *	The RKS executes one state machine application or active object at a time 
 *	in the infinite loop (similar to the "superloop"). The RKS is engaged 
 *	after each event is processed in the run-to-completion (RTC) fashion to 
 *	choose the next highest-priority active object ready to process the next 
 *	event. The RKS scheduler is cooperative, which means that all active 
 *	objects cooperate to share a single CPU and implicitly yield to each other 
 *	after every RTC step. The kernel is nonpreemptive, meaning that every 
 *	active object must completely process an event before any other active 
 *	object can start processing another event. The ISRs can preempt the 
 *	execution of active objects at any time, but due to the simplistic nature 
 *	of the RKS, every ISR returns to exactly the preemption point. If the ISR 
 *	posts an event to any active object, the processing of this event won't 
 *	start until the current RTC step completes. The maximum time an event for 
 *	the highest-priority active object can be delayed this way is called the 
 *	task-level response. With the nonpreemptive RKS, the task-level response 
 *	is equal to the longest RTC step of all active objects in the system.
 */


#include "rkhassert.h"
#include "rkh.h"


RKH_THIS_MODULE( 5, rkhs );


#if RKH_EN_NATIVE_SCHEDULER == 1


RKHRG_T rkhrg;				/* ready group of SMAs */


void 
rkh_init( void )
{
}


void 
rkh_enter( void )
{
	RKHSMAT_T *shr;			/* SMA ready with highest priority */
	RKHEVT_T *e;
	rkhui8_t prio;

	/* Invoke the start hook */
	rkh_hk_start();

    FOREVER
	{
		RKH_DIS_INTERRUPT();

        if( rkh_rdy_isnot_empty( rkhrg ) )
		{
			rkh_rdy_findh( rkhrg, prio );
            shr = rkh_sptbl[ prio ];
			RKH_ENA_INTERRUPT();

            e = rkh_sma_get( shr );
			rkh_dispatch( shr, e );
            rkh_gc( e );
        }
        else 
		/*
		 * rkh_hk_idle() must be called with interrupts DISABLED because the 
		 * determination of the idle condition (no events in the queues) can 
		 * change at any time by an interrupt posting events to a queue. The 
		 * rkh_hk_idle() MUST enable interrups internally, perhaps at the 
		 * same time as putting the CPU into a power-saving mode.
		 */			
            rkh_hk_idle();
    }
	
}


void 
rkh_exit( void )
{
	rkh_hk_exit();			/* Invoke the exit hook */
}


void 
rkh_sma_activate(	RKHSMA_T *sma, const RKHEVT_T **qs, RKH_RQNE_T qsize, 
						void *stks, rkhui32_t stksize )
{
	RKHREQUIRE( ( 0 < prio ) && ( prio <= (rkhui8_t)RKH_MAX_SMA ) 
						&& ( stks == ( void * )0 ) );
    ( void )stksize;
	rkh_rq_init( &sma->equeue, qs, qsize, sma );
	rkh_sma_register( sma );
    rkh_init_hsm( sma );
}


void 
rkh_sma_terminate( RKHSMA_T *sma )
{
	rkh_sma_unregister( sma );
}

#endif