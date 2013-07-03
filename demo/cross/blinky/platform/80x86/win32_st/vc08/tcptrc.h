/*
 *	file: tcptrc.h
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
 * RKH web site:	http://sourceforge.net/projects/rkh-reactivesys/
 * e-mail:			lf@vxtsolutions.com.ar
 */

/**
 * 	\file tcptrc.h
 *
 *	\brief
 *  TCP/IP Trace support for Win32
 *
 * 	\warning
 * 	To use the windows socket must be added the "ws2_32.lib" library in 
 * 	Linker->Input->Additional Dependencies configuration.
 */


#ifndef __TCPTRC_H__
#define __TCPTRC_H__


#include <WinSock.h>
	

/**
 * 	\brief
 *	---.
 * 
 *	---.
 *
 * 	\param port 		---.
 * 	\param srvip 		---.
 * 	\param ps 			---.
 *
 * 	\returns
 * 	---.
 */

int tcp_trace_open( unsigned short port, char *srvip, SOCKET *ps );


/**
 * 	\brief
 *	---.
 * 
 *	---.
 *
 * 	\param s 			---.
 * 	\param c 			---.
 */

void tcp_trace_send( SOCKET s, char c );


/**
 * 	\brief
 *	---.
 * 
 *	---.
 *
 * 	\param s	 		---.
 */

void tcp_trace_close( SOCKET s );


#endif
