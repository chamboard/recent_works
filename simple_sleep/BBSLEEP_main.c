// ***********************************************************************************************
// CHANTILLY 0xBB sleep utility
//
// ***********************************************************************************************
// simple as a tutorial !
// contact: admin@eihis.com
//
//
// nb : strongly needs code cleanup and optimisation, just here as a basis 
// to understand the 0xBB and chantilly access routines from the libraries
//
// ***********************************************************************************************
#include <stdint.h>
#include <stdio.h>
//
//
//
//#define  _MODEL_B2
#define _MODEL_BP
// verbose ?
//#define _VERBOSE
//
#ifdef _MODEL_B2
	#include <CHANTILLY_B2.h>
	#pragma message "Compiling for RPI model 2B+"
#else
	#include <CHANTILLY_BP.h>
	#pragma message "Compiling for RPI model B+"
#endif
//
#define _BB_BOARD 0x07
//

int main(int argc, char* argv[])
{
	uint32_t errors;
	uint8_t poweroff_mode[4];
	uint32_t poweroff_seconds;
	uint16_t poweroff_secs16;
	// chan tx/rx buffer
	uint8_t rxb[256];
	uint8_t txb[256];
	//
	//
	//printf("performing bbhalt..\n");fflush(stdout);
	//
	//return 0;
	//
	if(CHAN_setup("BBSLEEP",1)!=0) { printf("Error opening Chantilly, quit\n"); CHAN_close();exit(-1);} // try a close
	// get args
	//printf("BBHALT..\n");fflush(stdout);	
	errors=0;
	// straight to the goal ( see BB Halt for other behaviour )
	// set poweroff mode = 0 : cut power to the host only
	txb[0]=0;
	txb[1]=0;	// unused
	//
	errors+=CHAN_addr(_BB_BOARD,0x120);
	errors+=CHAN_setBytes(_BB_BOARD,2,txb);
	//
	// use a default 10s delay before cutting the hosts power
	poweroff_secs16=(uint16_t) 10;
	errors+=CHAN_addr(_BB_BOARD,0x114);
	errors+=CHAN_setBytes(_BB_BOARD,2,(uint8_t*) &poweroff_secs16);
	//
	// execute poweroff , mode 0 = host only, as written into the 0xBB's ram values
	//
	CHAN_command(_BB_BOARD,0x06);// shutdown command for 0xBB board
	printf("Going to sleep ...\n");fflush(stdout);
	// some delay (cache) TODO : check minimal times
	usleep(100000);
	CHAN_close();
	usleep(100000);
	//
#ifdef _VERBOSE	
		printf("BBsleep, exit ,errors:%d\n",errors);fflush(stdout);
		printf("Performing system halt...\n");fflush(stdout);
#endif
	//
	system("halt");
	
	return 0;
}
