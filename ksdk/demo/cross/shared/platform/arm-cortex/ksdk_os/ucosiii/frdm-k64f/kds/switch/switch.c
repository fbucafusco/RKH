/*
 * switch.c
 */

#include "mytypes.h"
#include "swhdl.h"
#include "switch.h"
#include "bsp.h"
#include "scevt.h"


static RKH_ROM_STATIC_EVENT( e_pause, PAUSE );
static SWITCH_ST switchs[SWITCHS_NUM] = 
{
	{ 0, rawsw1,	SW_RELEASED },
	{ 0, rawsw2,	SW_RELEASED },
};


#define SWITCH_EVT(s__, st__)					\
			do {								\
				if((st__) == SW_RELEASED)		\
					return;						\
				if((s__) == SW1_SWITCH)			\
					bsp_publish( &e_pause );	\
			} while(0)

			
void
switch_tick( void )
{
	SWITCH_ST *p;
	MUInt s;

	for( s = 0, p = switchs; p < &switchs[SWITCHS_NUM]; ++p, ++s ) 
	{
		p->state = (p->state<<1) | !(p->rawsw()); 
		if( (p->state == 0xFF) && (p->debsw != SW_PRESSED) )
		{
			p->debsw = SW_PRESSED;
			SWITCH_EVT( s, p->debsw );
		}
		else if( ( p->state == 0x00 ) && (p->debsw != SW_RELEASED) )
		{
			p->debsw = SW_RELEASED;
			SWITCH_EVT( s, p->debsw );
		}
	}

}

uchar
get_switch_state( uchar who )
{
	return switchs[who].debsw;
}
