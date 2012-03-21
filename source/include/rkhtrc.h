/*
 *	file: rkhtrc.h
 *	Last updated for version: 1.0.00
 *	Date of the last update:  May 28, 2010
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
 * 	\file rkhtrc.h
 * 	\brief
 *	Platform-independent interface for RKH trace facility.
 *
 * 	When a program needs to be traced, it has to generate some information 
 * 	each time it reaches a "significant step" (certain instruction in the 
 * 	program's source code). In the standard terminology, this step is called 
 * 	a trace point, and the tracing information which is generated at that 
 * 	point is called a trace event. A program containing one or more of this 
 * 	trace points is named instrumented application.
 *
 * 	There is one class of trace events: RKH trace events, which are generated 
 * 	by the RKH source code.
 * 	
 * 	The definition of events and the mapping between these and their 
 * 	corresponding names is hard-coded in the RKH implementation. Therefore, 
 * 	these events are common for all the state machine applications and never 
 * 	change (they are always traced). 
 * 	The trace events are associated with a integer value and are explicity 
 * 	listed and defined (enumerated) as shown below in this file.
 * 		
 *	The standard defines that the trace system has to store some information 
 *	for each trace event (also named arguments) being generated, including, 
 *	at least, the following:
 *
 * 	- the trace event identifier (RKHTR_EVENTS enumerated list),
 * 	- instrumented application (state machine),
 * 	- a timestamp (optional),
 * 	- any extra data that the system wants to associate with the event 
 * 	(optional).
 *
 * 	When the system or an application trace an event, all the information 
 * 	related to it has to be stored somewhere before it can be retrieved, in 
 * 	order to be analyzed. This place is a trace stream. Formally speaking, a 
 * 	trace stream is defined as a non-persistent, internal (opaque) data 
 * 	object containing a sequence of trace events plus some internal 
 * 	information to interpret those trace events.
 *	
 *	Also, the streams also support filtering. The application can define and 
 *	apply a filter to a trace stream. Basically, the filter establishes which 
 *	event types the stream is accepting (and hence storing) and which are not.
 *	Therefore, trace events corresponding to types which are filtered out 
 *	from a certain stream will not be stored in the stream. The stream in the 
 *	system can potentially be applied a different filter. This filter can be 
 *	applied, removed or changed at any time.
 */


#ifndef __RKHTRC_H__
#define __RKHTRC_H__


#include "rkhtype.h"
#include "rkhcfg.h"
#include <string.h>


/**
 * 	\brief
 * 	Enable or disable the trace facility for a instrumented state machine.
 * 	It's used as argument of rkh_trc_control() function.
 */

typedef enum
{
	RKH_TRC_STOP, RKH_TRC_START
} RKHTR_CTRL;


/**
 * 	\brief
 * 	RKH trace events.
 */

typedef enum rkh_trc_events
{
	/* --- Memory Pool (MP) ------------------ */
	RKH_TRCE_MP_INIT,
	RKH_TRCE_MP_GET,
	RKH_TRCE_MP_PUT,
	
	/* --- Queue (RQ) ------------------------ */
	RKH_TRCE_RQ_INIT,
	RKH_TRCE_RQ_GET,
	RKH_TRCE_RQ_FIFO,
	RKH_TRCE_RQ_LIFO,
	RKH_TRCE_RQ_FULL,
	RKH_TRCE_RQ_DPT,

	/* --- State Machine Application (SMA) --- */
	RKH_TRCE_SMA_ACT,
	RKH_TRCE_SMA_TERM,
	RKH_TRCE_SMA_GET,
	RKH_TRCE_SMA_FIFO,
	RKH_TRCE_SMA_LIFO,
	RKH_TRCE_SMA_REG,
	RKH_TRCE_SMA_UNREG,

	/* --- State machine (SM) ---------------- */
	RKH_TRCE_SM_INIT,
	RKH_TRCE_SM_CLRH,
	RKH_TRCE_SM_DCH,
	RKH_TRCE_SM_TRN,
	RKH_TRCE_SM_STATE,
	RKH_TRCE_SM_ENSTATE,
	RKH_TRCE_SM_EXSTATE,
	RKH_TRCE_SM_NENEX,
	RKH_TRCE_SM_NTRNACT,
	RKH_TRCE_SM_CSTATE,
	RKH_TRCE_SM_DCH_RC,

	/* --- Timer (TIM) ----------------------- */
	RKH_TRCE_TIM_INIT,
	RKH_TRCE_TIM_START,
	RKH_TRCE_TIM_RESTART,
	RKH_TRCE_TIM_STOP,

	/* --- Framework (RKH) ------------------- */
	RKH_TRCE_RKH_INIT,
	RKH_TRCE_RKH_EN,
	RKH_TRCE_RKH_EX,
	RKH_TRCE_RKH_EPREG,
	RKH_TRCE_RKH_AE,
	RKH_TRCE_RKH_GC,
	RKH_TRCE_RKH_GCR,
	RKH_TRCE_RKH_DEFER,
	RKH_TRCE_RKH_RCALL,

	RKH_TRCE_USER
	 
} RKH_TRC_EVENTS;


/** 
 * 	\brief
 * 	Defines the size of trace timestamp. 
 *
 * 	The valid values [in bits] are 8, 16 or 32. Default is 16. This type is 
 * 	configurable via the RKH_TRC_SIZEOF_TSTAMP preprocessor option.
 */

#if RKH_TRC_SIZEOF_TSTAMP == 8
	typedef rkhui8_t RKHTS_T;
	#define RKH_TRC_TSTAMP()					\
				RKH_TRC_UI8( rkh_trc_getts() )
#elif RKH_TRC_SIZEOF_TSTAMP == 16
	typedef rkhui16_t RKHTS_T;
	#define RKH_TRC_TSTAMP()					\
				RKH_TRC_UI16( rkh_trc_getts() )
#elif RKH_TRC_SIZEOF_TSTAMP == 32
	typedef rkhui32_t RKHTS_T;
	#define RKH_TRC_TSTAMP()					\
				RKH_TRC_UI32( rkh_trc_getts() )
#else
	typedef rkhui16_t RKHTS_T;
	#define RKH_TRC_TSTAMP()					\
				RKH_TRC_UI16( rkh_trc_getts() )
#endif


#define RKH_TRC_BEGIN( treid )		\
			RKH_SR_CRITICAL_;		\
			RKH_ENTER_CRITICAL_();	\
			rkh_trc_begin();		\
			RKH_TRC_HDR( treid )

#define RKH_TRC_END()				\
			RKH_EXIT_CRITICAL_()

#define RKH_TRC_UI8( d )	\
			rkh_trc_ui8( (d) )

#define RKH_TRC_UI16( d )	\
			rkh_trc_ui16( (d) )

#define RKH_TRC_UI32( d )	\
			rkh_trc_ui32( (d) )


#if RKH_TRC_EN_TSTAMP == 1
	#define RKH_TRC_HDR( treid ) 		\
				RKH_TRC_UI8( treid );	\
				RKH_TRC_TSTAMP()
#else
	#define RKH_TRC_HDR( treid ) 		\
				RKH_TRC_UI8( treid )
#endif


#if RKH_TRC_SIZEOF_POINTER == 16
	#define RKH_TRC_SYM( sym )	\
				RKH_TRC_UI16( (rkhui16_t)sym )
#elif RKH_TRC_SIZEOF_POINTER == 32
	#define RKH_TRC_SYM( sym )	\
				RKH_TRC_UI32( (rkhui32_t)sym )
#else
	#define RKH_TRC_SYM( sym )	\
				RKH_TRC_UI32( (rkhui32_t)sym )
#endif


#if RKH_TIMER_SIZEOF_NTIMER == 8
	#define RKH_TRC_NTICK( nt )	\
				RKH_TRC_UI8( nt )
#elif RKH_TIMER_SIZEOF_NTIMER == 16
	#define RKH_TRC_NTICK( nt )	\
				RKH_TRC_UI16( nt )
#elif RKH_TIMER_SIZEOF_NTIMER == 32
	#define RKH_TRC_NTICK( nt )	\
				RKH_TRC_UI32( nt )
#else
	#define RKH_TRC_NTICK( nt )	\
				RKH_TRC_UI8( nt )
#endif


#if RKH_MP_SIZEOF_NBLOCK == 8
	#define RKH_TRC_NBLK( nb )	\
				RKH_TRC_UI8( nb )
#elif RKH_MP_SIZEOF_NBLOCK == 16
	#define RKH_TRC_NBLK( nb )	\
				RKH_TRC_UI16( nb )
#elif RKH_MP_SIZEOF_NBLOCK == 32
	#define RKH_TRC_NBLK( nb )	\
				RKH_TRC_UI32( nb )
#else
	#define RKH_TRC_NBLK( nb )	\
				RKH_TRC_UI8( nb )
#endif


#if RKH_RQ_SIZEOF_NELEM == 8
	#define RKH_TRC_NE( ne )	\
				RKH_TRC_UI8( ne )
#elif RKH_MP_SIZEOF_NELEM == 16
	#define RKH_TRC_NE( ne )	\
				RKH_TRC_UI16( ne )
#elif RKH_MP_SIZEOF_NELEM == 32
	#define RKH_TRC_NE( ne )	\
				RKH_TRC_UI32( ne )
#else
	#define RKH_TRC_NE( ne )	\
				RKH_TRC_UI8( ne )
#endif


#if RKH_SIZEOF_EVENT == 8
	#define RKH_TRC_SIG( e )	\
				RKH_TRC_UI8( e )
#elif RKH_SIZEOF_EVENT == 16
	#define RKH_TRC_SIG( e )	\
				RKH_TRC_UI16( e )
#elif RKH_SIZEOF_EVENT == 32
	#define RKH_TRC_SIG( e )	\
				RKH_TRC_UI32( e )
#else
	#define RKH_TRC_SIG( e )	\
				RKH_TRC_UI8( e )
#endif


#if RKH_SIZEOF_ESIZE == 8
	#define RKH_TRC_ES( es )	\
				RKH_TRC_UI8( es )
#elif RKH_SIZEOF_ESIZE == 16
	#define RKH_TRC_ES( es )	\
				RKH_TRC_UI16( es )
#elif RKH_SIZEOF_ESIZE == 32
	#define RKH_TRC_ES( es )	\
				RKH_TRC_UI32( es )
#else
	#define RKH_TRC_ES( es )	\
				RKH_TRC_UI8( es )
#endif


#if RKH_TRC_EN == 1
	/* --- Memory Pool (MP) ------------------ */
	#if RKH_TRC_ALL == 1 || RKH_TRC_EN_MP == 1
		#define RKH_TRCR_MP_INIT( mp, nblock )				\
					RKH_TRC_BEGIN( RKH_TRCE_MP_INIT );		\
						RKH_TRC_SYM( mp ); 					\
						RKH_TRC_NBLK( nblock ); 			\
					RKH_TRC_END()

		#define RKH_TRCR_MP_GET( mp, nfree )				\
					RKH_TRC_BEGIN( RKH_TRCE_MP_GET );		\
						RKH_TRC_SYM( mp ); 					\
						RKH_TRC_NBLK( nfree ); 				\
					RKH_TRC_END()
	
		#define RKH_TRCR_MP_PUT( mp, nfree )				\
					RKH_TRC_BEGIN( RKH_TRCE_MP_PUT );		\
						RKH_TRC_SYM( mp ); 					\
						RKH_TRC_NBLK( nfree ); 				\
					RKH_TRC_END()
	#else
		#define RKH_TRCR_MP_INIT( mp, nblock )
		#define RKH_TRCR_MP_GET( mp, nfree )
		#define RKH_TRCR_MP_PUT( mp, nfree )
	#endif

	/* --- Queue (RQ) ------------------------ */
	#if RKH_TRC_ALL == 1 || RKH_TRC_EN_RQ == 1
		#define RKH_TRCR_RQ_INIT( q, nelem, sma )			\
					RKH_TRC_BEGIN( RKH_TRCE_RQ_INIT );		\
						RKH_TRC_SYM( q ); 					\
						RKH_TRC_SYM( sma ); 				\
						RKH_TRC_NE( nelem ); 				\
					RKH_TRC_END()

		#define RKH_TRCR_RQ_GET( q, qty )					\
					RKH_TRC_BEGIN( RKH_TRCE_RQ_GET );		\
						RKH_TRC_SYM( q ); 					\
						RKH_TRC_NE( qty ); 					\
					RKH_TRC_END()
	
		#define RKH_TRCR_RQ_FIFO( q, qty )					\
					RKH_TRC_BEGIN( RKH_TRCE_RQ_FIFO );		\
						RKH_TRC_SYM( q ); 					\
						RKH_TRC_NE( qty ); 					\
					RKH_TRC_END()

		#define RKH_TRCR_RQ_LIFO( q, qty )					\
					RKH_TRC_BEGIN( RKH_TRCE_RQ_LIFO );		\
						RKH_TRC_SYM( q ); 					\
						RKH_TRC_NE( qty ); 					\
					RKH_TRC_END()

		#define RKH_TRCR_RQ_FULL( q )						\
					RKH_TRC_BEGIN( RKH_TRCE_RQ_FULL );		\
						RKH_TRC_SYM( q ); 					\
					RKH_TRC_END()

		#define RKH_TRCR_RQ_DEPLETE( q )					\
					RKH_TRC_BEGIN( RKH_TRCE_RQ_DPT );		\
						RKH_TRC_SYM( q ); 					\
					RKH_TRC_END()
	#else
		#define RKH_TRCR_RQ_INIT( q, nelem, sma )
		#define RKH_TRCR_RQ_GET( q, qty )
		#define RKH_TRCR_RQ_FIFO( q, qty )
		#define RKH_TRCR_RQ_LIFO( q, qty )
		#define RKH_TRCR_RQ_FULL( q )
		#define RKH_TRCR_RQ_DEPLETE( q )
	#endif

	/* --- State Machine Application (SMA) --- */
	#if RKH_TRC_ALL == 1 || RKH_TRC_EN_SMA == 1
		#define RKH_TRCR_SMA_ACT( sma )						\
					RKH_TRC_BEGIN( RKH_TRCE_SMA_ACT );		\
						RKH_TRC_SYM( sma ); 				\
					RKH_TRC_END()

		#define RKH_TRCR_SMA_TERM( sma )					\
					RKH_TRC_BEGIN( RKH_TRCE_SMA_TERM );		\
						RKH_TRC_SYM( sma ); 				\
					RKH_TRC_END()

		#define RKH_TRCR_SMA_GET( sma, ev )					\
					RKH_TRC_BEGIN( RKH_TRCE_SMA_GET );		\
						RKH_TRC_SYM( sma ); 				\
						RKH_TRC_SIG( ev->e ); 				\
					RKH_TRC_END()

		#define RKH_TRCR_SMA_FIFO( sma, ev )				\
					RKH_TRC_BEGIN( RKH_TRCE_SMA_FIFO );		\
						RKH_TRC_SYM( sma ); 				\
						RKH_TRC_SIG( ev->e ); 				\
					RKH_TRC_END()

		#define RKH_TRCR_SMA_LIFO( sma, ev )				\
					RKH_TRC_BEGIN( RKH_TRCE_SMA_LIFO );		\
						RKH_TRC_SYM( sma ); 				\
						RKH_TRC_SIG( ev->e ); 				\
					RKH_TRC_END()

		#define RKH_TRCR_SMA_REG( sma, prio )				\
					RKH_TRC_BEGIN( RKH_TRCE_SMA_REG );		\
						RKH_TRC_SYM( sma ); 				\
						RKH_TRC_UI8( prio ); 				\
					RKH_TRC_END()

		#define RKH_TRCR_SMA_UNREG( sma, prio )				\
					RKH_TRC_BEGIN( RKH_TRCE_SMA_UNREG );	\
						RKH_TRC_SYM( sma ); 				\
						RKH_TRC_UI8( prio ); 				\
					RKH_TRC_END()
	#else
		#define RKH_TRCR_SMA_ACT( sma )
		#define RKH_TRCR_SMA_TERM( sma )
		#define RKH_TRCR_SMA_GET( sma, e )
		#define RKH_TRCR_SMA_FIFO( sma, e )
		#define RKH_TRCR_SMA_LIFO( sma, e )
		#define RKH_TRCR_SMA_REG( sma, prio )
		#define RKH_TRCR_SMA_UNREG( sma, prio )
	#endif

	/* --- State machine (SM) ---------------- */
	#if RKH_TRC_ALL == 1 || RKH_TRC_EN_SM == 1
		#define RKH_TRCR_SM_INIT( sma, is )					\
					RKH_TRC_BEGIN( RKH_TRCE_SM_INIT );		\
						RKH_TRC_SYM( sma ); 				\
						RKH_TRC_SYM( is ); 					\
					RKH_TRC_END()

		#define RKH_TRCR_SM_DCH( sma, ev )					\
					RKH_TRC_BEGIN( RKH_TRCE_SM_DCH );		\
						RKH_TRC_SYM( sma ); 				\
						RKH_TRC_SIG( ev->e ); 				\
					RKH_TRC_END()

		#define RKH_TRCR_SM_CLRH( sma, h )					\
					RKH_TRC_BEGIN( RKH_TRCE_SM_CLRH );		\
						RKH_TRC_SYM( sma ); 				\
						RKH_TRC_SYM( h ); 					\
					RKH_TRC_END()

		#define RKH_TRCR_SM_TRN( sma, ss, ts )				\
					RKH_TRC_BEGIN( RKH_TRCE_SM_TRN );		\
						RKH_TRC_SYM( sma ); 				\
						RKH_TRC_SYM( ss ); 					\
						RKH_TRC_SYM( ts ); 					\
					RKH_TRC_END()

		#define RKH_TRCR_SM_STATE( sma, s )					\
					RKH_TRC_BEGIN( RKH_TRCE_SM_STATE );		\
						RKH_TRC_SYM( sma ); 				\
						RKH_TRC_SYM( s ); 					\
					RKH_TRC_END()

		#define RKH_TRCR_SM_ENSTATE( sma, s )				\
					RKH_TRC_BEGIN( RKH_TRCE_SM_ENSTATE );	\
						RKH_TRC_SYM( sma ); 				\
						RKH_TRC_SYM( s ); 					\
					RKH_TRC_END()

		#define RKH_TRCR_SM_EXSTATE( sma, s )				\
					RKH_TRC_BEGIN( RKH_TRCE_SM_EXSTATE );	\
						RKH_TRC_SYM( sma ); 				\
						RKH_TRC_SYM( s ); 					\
					RKH_TRC_END()

		#define RKH_TRCR_SM_NENEX( sma, nen, nex )			\
					RKH_TRC_BEGIN( RKH_TRCE_SM_NENEX );		\
						RKH_TRC_SYM( sma ); 				\
						RKH_TRC_UI8( nen ); 				\
						RKH_TRC_UI8( nex ); 				\
					RKH_TRC_END()

		#define RKH_TRCR_SM_NTRNACT( sma, nta )				\
					RKH_TRC_BEGIN( RKH_TRCE_SM_NTRNACT );	\
						RKH_TRC_SYM( sma ); 				\
						RKH_TRC_UI8( nta ); 				\
					RKH_TRC_END()

		#define RKH_TRCR_SM_CSTATE( sma, s )				\
					RKH_TRC_BEGIN( RKH_TRCE_SM_CSTATE );	\
						RKH_TRC_SYM( sma ); 				\
						RKH_TRC_SYM( s ); 					\
					RKH_TRC_END()

		#define RKH_TRCR_SM_DCH_RC( sma, rc )				\
					RKH_TRC_BEGIN( RKH_TRCE_SM_DCH_RC );	\
						RKH_TRC_SYM( sma ); 				\
						RKH_TRC_UI8( rc ); 					\
					RKH_TRC_END()
	#else
		#define RKH_TRCR_SM_INIT( sma, is )
		#define RKH_TRCR_SM_CLRH( sma, h )
		#define RKH_TRCR_SM_DCH( sma, e )
		#define RKH_TRCR_SM_TRN( sma, ss, ts )
		#define RKH_TRCR_SM_STATE( sma, s )
		#define RKH_TRCR_SM_ENSTATE( sma, s )
		#define RKH_TRCR_SM_EXSTATE( sma, s )
		#define RKH_TRCR_SM_NENEX( sma, nenex )
		#define RKH_TRCR_SM_NTRNACT( sma, nta )
		#define RKH_TRCR_SM_CSTATE( sma, s )
		#define RKH_TRCR_SM_DCH_RC( sma, rc )
	#endif

	/* --- Timer (TIM) ----------------------- */
	#if RKH_TRC_ALL == 1 || RKH_TRC_EN_TIM == 1
		#define RKH_TRCR_TIM_INIT( t, sig )					\
					RKH_TRC_BEGIN( RKH_TRCE_TIM_INIT );		\
						RKH_TRC_SYM( t ); 					\
						RKH_TRC_SIG( sig ); 				\
					RKH_TRC_END()

		#define RKH_TRCR_TIM_START(	t, nt, sma )			\
					RKH_TRC_BEGIN( RKH_TRCE_TIM_START );	\
						RKH_TRC_SYM( t ); 					\
						RKH_TRC_NTICK( nt ); 				\
						RKH_TRC_SYM( sma ); 				\
					RKH_TRC_END()
	
		#define RKH_TRCR_TIM_RESTART( t, nt )				\
					RKH_TRC_BEGIN( RKH_TRCE_TIM_RESTART );	\
						RKH_TRC_SYM( t ); 					\
						RKH_TRC_NTICK( nt ); 				\
					RKH_TRC_END()

		#define RKH_TRCR_TIM_STOP( t )						\
					RKH_TRC_BEGIN( RKH_TRCE_TIM_STOP );		\
						RKH_TRC_SYM( t ); 					\
					RKH_TRC_END()
	#else
		#define RKH_TRCR_TIM_INIT( t, sig )
		#define RKH_TRCR_TIM_START( t, nt, sma )
		#define RKH_TRCR_TIM_RESTART( t, nt )
		#define RKH_TRCR_TIM_STOP( t )
	#endif

	/* --- Framework (RKH) ----------------------- */
	#if RKH_TRC_ALL == 1 || RKH_TRC_EN_TIM == 1
		#define RKH_TRCR_RKH_INIT()							\
					RKH_TRC_BEGIN( RKH_TRCE_RKH_INIT );		\
					RKH_TRC_END()

		#define RKH_TRCR_RKH_EN()							\
					RKH_TRC_BEGIN( RKH_TRCE_RKH_EN );		\
					RKH_TRC_END()

		#define RKH_TRCR_RKH_EX()							\
					RKH_TRC_BEGIN( RKH_TRCE_RKH_EX );		\
					RKH_TRC_END()

		#define RKH_TRCR_RKH_EPREG( ssize, esize )			\
					RKH_TRC_BEGIN( RKH_TRCE_RKH_EPREG );	\
					RKH_TRC_UI32( ssize );					\
					RKH_TRC_ES( esize );					\
					RKH_TRC_END()

		#define RKH_TRCR_RKH_AE( esize, ev )					\
					RKH_TRC_BEGIN( RKH_TRCE_RKH_AE );		\
					RKH_TRC_ES( esize );					\
					RKH_TRC_SIG( ev->e );					\
					RKH_TRC_END()

		#define RKH_TRCR_RKH_GC( ev )						\
					RKH_TRC_BEGIN( RKH_TRCE_RKH_GC );		\
					RKH_TRC_SIG( ev->e );					\
					RKH_TRC_END()

		#define RKH_TRCR_RKH_GCR( ev )						\
					RKH_TRC_BEGIN( RKH_TRCE_RKH_GCR );		\
					RKH_TRC_SIG( ev->e );					\
					RKH_TRC_END()

		#define RKH_TRCR_RKH_DEFER( q, ev )					\
					RKH_TRC_BEGIN( RKH_TRCE_RKH_DEFER );	\
					RKH_TRC_SYM( q );						\
					RKH_TRC_SIG( ev->e );					\
					RKH_TRC_END()

		#define RKH_TRCR_RKH_RCALL( sma, ev )				\
					RKH_TRC_BEGIN( RKH_TRCE_RKH_RCALL );	\
					RKH_TRC_SYM( sma );						\
					RKH_TRC_SIG( ev->e );					\
					RKH_TRC_END()
	#else
		#define RKH_TRCR_RKH_INIT()
		#define RKH_TRCR_RKH_EN()
		#define RKH_TRCR_RKH_EX()
		#define RKH_TRCR_RKH_EPREG( ssize, esize )
		#define RKH_TRCR_RKH_AE( esize, e )
		#define RKH_TRCR_RKH_GC( e )
		#define RKH_TRCR_RKH_GCR( e )
		#define RKH_TRCR_RKH_DEFER( q, e )
		#define RKH_TRCR_RKH_RCALL( sma, e )
	#endif
#endif


/**
 * 	\brief
 * 	Describes a trace event. 
 * 
 * 	Trace events are binary data consisting of a trace header and its 
 * 	associated event data. Every trace header is made up of a 1-byte ID and a 
 * 	timestamp. The number of bytes used by the timestamp is configurable by 
 * 	RKH_TRC_SIZEOF_TS (1, 2 or 4 bytes). After the timestamp follows the event 
 * 	data. The content and size of the data portion of a trace event is 
 * 	determined by the event ID. 
 *	All types of events are stored in a single ring buffer, called trace 
 *	stream, using a fixed event size of RKH_TRC_SIZEOF_EVENT bytes. In this 
 *	manner the recorder always holds the most recent history.
 *	On the other hand, all data are stored in little-endian order (least 
 *	significant byte first). Also, they are stored into the trace stream 1 
 *	byte at a time, thus avoiding any potential data misalignment problems.
 *	
 *	\note
 *	The timestamp is optional, thus it could be eliminated from the trace 
 *	event in compile-time with RKH_TRC_EN_TSTAMP = 0.
 *	\note
 *	The trace stream is an array of buffers.
 *
 */

typedef rkhui8_t RKH_TRCE_T[ RKH_TRC_SIZEOF_EVENT ];


/**
 * 	\brief
 * 	Initializes the RKH's trace record service.
 */

void rkh_trc_init( void );


/**
 * 	\brief
 * 	Starts or stops the tracing session. 
 * 	The stream can be in two different states: running (RKH_TRC_START) or 
 * 	suspended (RKH_TRC_STOP). These two states determine whether or not the 
 * 	stream is accepting events to be stored.
 *
 * 	\param opt		control option.
 */

void rkh_trc_control( HUInt opt );


/**
 * 	\brief
 *	Retrieves a pointer to oldest trace event in the trace stream. 
 *	Frequently, this function is used by the called trace analyzer.
 *
 * 	\returns
 * 	A pointer to the beginning of the buffer into which the trace event was 
 * 	stored if trace stream was not empty, otherwise NULL pointer.
 */

rkhui8_t *rkh_trc_get_oldest( void );


/**
 * 	\brief
 * 	Get the next trace event buffer from the trace stream. The retrieved 
 * 	buffer will be used to record a new trace event.
 *
 * 	\returns
 * 	A pointer to the beginning of the reserved buffer into which the trace 
 * 	event will be copied if trace stream was not stopped, otherwise NULL 
 * 	pointer.
 */

rkhui8_t *rkh_trc_get_nextbuf( void );


/**
 * 	\brief
 * 	Filters the types of events to be traced. 
 *
 * 	The stream is initially created with an empty filter (that is, without 
 * 	filtering any event type). If this is not the required behavior, the 
 * 	application can build a set of event types, include the appropriate event 
 * 	types in it, and apply it as a filter to the stream. After that, the 
 * 	stream will reject any event whose type is in the filter set.
 */

void rkh_trc_filter( void );


/**
 * 	\brief
 * 	Get a buffer from the trace stream. The retrieved buffer will be used 
 * 	to record a new trace event.
 */

void rkh_trc_begin( void );


/**
 * 	\brief
 * 	Store a 8-bit data into the current trace event buffer.
 */

void rkh_trc_ui8( rkhui8_t d );


/**
 * 	\brief
 * 	Store a 16-bit data into the current trace event buffer.
 */

void rkh_trc_ui16( rkhui16_t d );


/**
 * 	\brief
 * 	Store a 32-bit data into the current trace event buffer.
 */

void rkh_trc_ui32( rkhui32_t d );


#endif
