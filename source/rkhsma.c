/*
 *  --------------------------------------------------------------------------
 *
 *                                Framework RKH
 *                                -------------
 *
 *            State-machine framework for reactive embedded systems
 *
 *                      Copyright (C) 2010 Leandro Francucci.
 *          All rights reserved. Protected by international copyright laws.
 *
 *
 *  RKH is free software: you can redistribute it and/or modify it under the
 *  terms of the GNU General Public License as published by the Free Software
 *  Foundation, either version 3 of the License, or (at your option) any
 *  later version.
 *
 *  RKH is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *  more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with RKH, see copying.txt file.
 *
 *  Contact information:
 *  RKH web site:   http://sourceforge.net/projects/rkh-reactivesys/
 *  e-mail:         francuccilea@gmail.com
 *  ---------------------------------------------------------------------------
 */

/**
 *  \file       rkhsma.c
 *  \ingroup    sch
 *
 *  \brief      Implements the SMA(active object) registration.
 */

/* ----------------------------- Include files ----------------------------- */

#include "rkhassert.h"
#include "rkh.h"

RKH_MODULE_NAME(rkhsma)

/* ----------------------------- Local macros ------------------------------ */
/* ---------------------------- Local constants ---------------------------- */

/*
 *  String describing the RKH version.
 */
RKHROM char rkh_version[] =
{
    (char)((rui8_t)((RKH_VERSION_CODE >> 12)    & 0x0F) + (rui8_t)'0'),
    (char)'.',
    (char)((rui8_t)((RKH_VERSION_CODE >> 8)     & 0x0F) + (rui8_t)'0'),
    (char)'.',
    (char)((rui8_t)((RKH_VERSION_CODE >> 4)     & 0x0F) + (rui8_t)'0'),
    (char)((rui8_t)(RKH_VERSION_CODE            & 0x0F) + (rui8_t)'0'),
    (char)'\0',
};

#ifndef R_TRC_AO_NAME_EN
RKHROM char noname[] = "null";
#endif

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */

RKH_SMA_T *rkh_sptbl[RKH_CFG_FWK_MAX_SMA];  /* registered SMA table */

/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */

void
rkh_sma_register(RKH_SMA_T *sma)
{
    rui8_t prio = RKH_GET_PRIO(sma);
    RKH_SR_ALLOC();

    RKH_REQUIRE((prio <= (rui8_t)RKH_LOWEST_PRIO) &&
                (rkh_sptbl[prio] == (RKH_SMA_T *)0));

    RKH_ENTER_CRITICAL_();
    rkh_sptbl[prio] = sma;
    RKH_TR_SMA_REG(sma, prio);
    RKH_EXIT_CRITICAL_();
}

void
rkh_sma_unregister(RKH_SMA_T *sma)
{
    rui8_t prio = RKH_GET_PRIO(sma);
    RKH_SR_ALLOC();

    RKH_REQUIRE((prio <= (rui8_t)RKH_CFG_FWK_MAX_SMA) &&
                (rkh_sptbl[prio] == sma));

    RKH_ENTER_CRITICAL_();
    rkh_sptbl[prio] = (RKH_SMA_T *)0;
    RKH_TR_SMA_UNREG(sma, prio);
    RKH_EXIT_CRITICAL_();
}
/* ------------------------------ End of file ------------------------------ */
