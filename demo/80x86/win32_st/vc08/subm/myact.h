/*
 *	myact.h
 */


#ifndef __MYACT_H__
#define __MYACT_H__


#include "rkh.h"


/*
 *	Defines HSM init function
 */

/* ... */

/*
 *	Defines state entry functions
 */

/* ... */


/*
 *	Defines state exit functions
 */

/* ... */


/*
 *	Defines state preprocessor functions
 */

/* ... */


/*
 *	Defines transition action functions
 */

void act1( const struct rkhsma_t *sma, RKHEVT_T *pe );
void act2( const struct rkhsma_t *sma, RKHEVT_T *pe );
void act3( const struct rkhsma_t *sma, RKHEVT_T *pe );
void act4( const struct rkhsma_t *sma, RKHEVT_T *pe );
void act5( const struct rkhsma_t *sma, RKHEVT_T *pe );
void act6( const struct rkhsma_t *sma, RKHEVT_T *pe );
void act7( const struct rkhsma_t *sma, RKHEVT_T *pe );
void act8( const struct rkhsma_t *sma, RKHEVT_T *pe );
void terminate( const struct rkhsma_t *sma, RKHEVT_T *pe );


/*
 *	Defines branch's guards
 */

/* ... */

/*
 *	Defines guard functions
 */

/* ... */


#endif
