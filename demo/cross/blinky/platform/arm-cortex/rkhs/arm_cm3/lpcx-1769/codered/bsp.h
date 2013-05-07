/*
 *	file: bsp.h
 *	Last updated for version: 2.0
 *	Date of the last update:  Feb 28, 2012
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
 * RKH web site:	http://sourceforge.net/projects/rkh-reactivesys/
 * e-mail:			francuccilea@gmail.com
 */


#ifndef __BSP_H__
#define __BSP_H__


#include "rkh.h"
#include "LPC17xx.h"


#define BSP_KERNEL_IRQ_PRIO		255
#define BSP_HIGHEST_IRQ_PRI		5


void bsp_init( int argc, char *argv[] );
void bsp_led_on( void );
void bsp_led_off( void );

#ifdef DEBUG
#define reset_now()		__asm volatile	("	bkpt 0x00FF\n" )
#else					
#define reset_now()		NVIC_SystemReset()
#endif


#endif