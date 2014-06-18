/**
 * \cond
 *  --------------------------------------------------------------------------
 *
 *                                Framework RKH
 *                                -------------
 *
 * 	          State-machine framework for reactive embedded systems            
 * 	        
 * 	                    Copyright (C) 2010 Leandro Francucci.
 * 	        All rights reserved. Protected by international copyright laws.
 *
 *
 * 	RKH is free software: you can redistribute it and/or modify it under the 
 * 	terms of the GNU General Public License as published by the Free Software 
 * 	Foundation, either version 3 of the License, or (at your option) any 
 * 	later version.
 *
 *  RKH is distributed in the hope that it will be useful, but WITHOUT ANY 
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for 
 *  more details.
 *
 *  You should have received a copy of the GNU General Public License along 
 *  with RKH, see copying.txt file.
 *
 * 	Contact information:
 * 	RKH web site:	http://sourceforge.net/projects/rkh-reactivesys/
 * 	e-mail:			francuccilea@gmail.com
 *
 *  --------------------------------------------------------------------------
 *  File                     : rkhport.c
 *	Last updated for version : v2.4.04
 *	By                       : LF
 *  --------------------------------------------------------------------------
 *  \endcond
 *
 * 	\file
 * 	\ingroup 	prt
 *
 * 	\brief 		Visual Studio 2008 Single-Thread port (win32)
 */


#include "rkh.h"


RKH_MODULE_NAME( rkhport )
RKH_MODULE_VERSION( rkhport, 1.00 )
RKH_MODULE_DESC( rkhport, "Windows 32-bits (single thread)" )


CRITICAL_SECTION csection;		/* Win32 critical section */
HANDLE sma_is_rdy;          	/* Win32 event to signal when SMAs are ready */
RKHRG_T rkhrg;					/* ready group of SMAs */

extern rkhui8_t running;


const 
char *
rkh_get_port_version( void )
{
	return RKH_MODULE_GET_VERSION();
}


const 
char *
rkh_get_port_desc( void )
{
	return RKH_MODULE_GET_DESC();
}


void 
rkh_init( void )
{
    InitializeCriticalSection( &csection );
    sma_is_rdy = CreateEvent( NULL, FALSE, FALSE, NULL );	
}


void 
rkh_enter( void )
{
	rkhui8_t prio;
	RKHSMA_T *sma;
	RKHEVT_T *e;
	RKH_SR_ALLOC();

    RKH_HK_START();
	RKH_TR_FWK_EN();
    running = 1;

    while( running )
	{
        RKH_ENTER_CRITICAL( dummy );
        if( rkh_rdy_isnot_empty( rkhrg ) ) 
		{
			rkh_rdy_findh( rkhrg, prio );
            RKH_EXIT_CRITICAL( dummy );

            sma = rkh_sptbl[ prio ];
            e = rkh_sma_get( sma );
            rkh_dispatch( sma, e );
            RKH_GC( e );
        }
        else
            rkh_hk_idle();
    }

    RKH_HK_EXIT();
    CloseHandle( sma_is_rdy );
    DeleteCriticalSection( &csection );	
}


void 
rkh_exit( void )
{
	RKH_HK_EXIT();
	RKH_TR_FWK_EX();
	running = 0;
}


void 
rkh_sma_activate(	RKHSMA_T *sma, const RKHEVT_T **qs, RKH_RQNE_T qsize, 
						void *stks, rkhui32_t stksize )
{
    ( void )stks;
    ( void )stksize;
	RKH_SR_ALLOC();

	rkh_rq_init( &sma->equeue, (const void **)qs, qsize, sma );
	rkh_sma_register( sma );
    rkh_init_hsm( sma );
	RKH_TR_SMA_ACT( sma, RKH_GET_PRIO(sma) );
}


void 
rkh_sma_terminate( RKHSMA_T *sma )
{
	RKH_SR_ALLOC();

	rkh_sma_unregister( sma );
	RKH_TR_SMA_TERM( sma, RKH_GET_PRIO(sma) );
}
