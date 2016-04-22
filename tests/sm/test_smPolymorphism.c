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
 *  \file       test_smPolymorphism.c
 *  \ingroup    test_sm
 *  \brief      Unit test for state machine module.
 *
 *  \addtogroup test
 *  @{
 *  \addtogroup test_sm State Machine
 *  @{
 *  \brief      Unit test for state machine module.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2016.12.15  LeFr  v2.4.05  ---
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "unity_fixture.h"
#include "unitrazer.h"
#include "rkh.h"
#include "common.h"
#include "smPolymorphism.h"
#include "MockrkhportTest.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
TEST_GROUP(polymorphism);

/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void
checkVtbl(RKH_SMA_T *me, RKHActivate activate, RKHTask task, 
          RKHPostFifo postFifo, RKHPostLifo postLifo)
{
    TEST_ASSERT_EQUAL_PTR(activate, me->vptr->activate);
    TEST_ASSERT_EQUAL_PTR(task, me->vptr->task);
    TEST_ASSERT_EQUAL_PTR(postFifo, me->vptr->post_fifo);
    TEST_ASSERT_EQUAL_PTR(postLifo, me->vptr->post_lifo);
}

static void
testActivate(RKH_SMA_T *me, const RKH_EVT_T **qSto, RKH_RQNE_T qSize,
             void *stkSto, rui32_t stkSize)
{
}

static void
testTask(RKH_SMA_T *me, void *arg)
{
}

static void
testPostFifo(RKH_SMA_T *me, const RKH_EVT_T *e, const void *const sender)
{
}

static void
testPostLifo(RKH_SMA_T *me, const RKH_EVT_T *e, const void *const sender)
{
}

/* ---------------------------- Global functions --------------------------- */
TEST_SETUP(polymorphism)
{
    sm_init();

    RKH_FILTER_OFF_ALL_SIGNALS();
    RKH_FILTER_OFF_GROUP_ALL_EVENTS(RKH_TG_SM);
    RKH_FILTER_OFF_EVENT(RKH_TE_FWK_ASSERT);

    /* Restore the default virtual table of RKH_SMA_T class */
    singleton->vptr = &rkhSmaVtbl;
}

TEST_TEAR_DOWN(polymorphism)
{
    sm_verify(); /* Makes sure there are no unused expectations, if */
                 /* there are, this function causes the test to fail. */
    sm_cleanup();
}

/**
 *  \addtogroup test_smPolymorphism Polymorphism test group
 *  @{
 *  \name Test cases of polimorphism group
 *  @{
 */

TEST(polymorphism, defaultVirtualFunctions)
{
    checkVtbl(singleton, 
              rkh_sma_activate, NULL, rkh_sma_post_fifo, rkh_sma_post_lifo);

    TEST_ASSERT_EQUAL_PTR(&rkhSmaVtbl, singleton->vptr);
}

TEST(polymorphism, callVirtualFunction)
{
    rkh_sma_activate_Expect(singleton, NULL, 0, NULL, 0);
    rkh_sma_post_fifo_Expect(singleton, NULL, NULL);
    rkh_sma_post_lifo_Expect(singleton, NULL, NULL);

    RKH_SMA_ACTIVATE(singleton, NULL, 0, NULL, 0);
    RKH_SMA_POST_FIFO(singleton, NULL, NULL);
    RKH_SMA_POST_LIFO(singleton, NULL, NULL);
}

TEST(polymorphism, setVirtualTable)
{
    const RKHSmaVtbl *vptr;
    static const RKHSmaVtbl vtbl =
    {
        testActivate, testTask, testPostFifo, testPostLifo
    };

    vptr = singleton->vptr = &vtbl;

    checkVtbl(singleton, 
              testActivate, testTask, testPostFifo, testPostLifo);
}

TEST(polymorphism, runtimeSingletonAOCtor)
{
    Singleton_ctor(8);
    TEST_ASSERT_EQUAL(8, Singleton_getFoo());

    RKH_SMA_ACTIVATE(singleton, NULL, 0, NULL, 0);
    TEST_ASSERT_EQUAL(0, Singleton_getFoo());
}

TEST(polymorphism, runtimeMultipleAOCtorWithVtblForObj)
{
    Multiple_ctor(multA, 2, Multiple_postFifoA);
    Multiple_ctor(multB, 4, Multiple_postFifoB);

    checkVtbl((RKH_SMA_T *)multA, 
              rkh_sma_activate, NULL, Multiple_postFifoA, rkh_sma_post_lifo);

    TEST_ASSERT_EQUAL(2, Multiple_getFoobar(multA));
    TEST_ASSERT_EQUAL(4, Multiple_getFoobar(multB));

    RKH_SMA_POST_FIFO((RKH_SMA_T *)multA, NULL, NULL);
    RKH_SMA_POST_FIFO((RKH_SMA_T *)multB, NULL, NULL);

    TEST_ASSERT_EQUAL(0, Multiple_getFoobar(multA));
    TEST_ASSERT_EQUAL(8, Multiple_getFoobar(multB));
}

TEST(polymorphism, runtimeMultipleAOCtorWithVtblForType)
{
    Command_ctor(cmdSignal, 128); 
    Command_ctor(cmdRegister, 64); 

    checkVtbl((RKH_SMA_T *)cmdSignal, 
              rkh_sma_activate, Command_task, 
              Command_postFifo, Command_postLifo);

    checkVtbl((RKH_SMA_T *)cmdRegister, 
              rkh_sma_activate, Command_task, 
              Command_postFifo, Command_postLifo);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/* ------------------------------ End of file ------------------------------ */