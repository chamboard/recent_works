// ***********************************************************************************************
// CHANTILLY 0xBB poweroff utility
//
// ***********************************************************************************************
// simple as a tutorial !
// contact: admin@eihis.com
//
// simple 0xBB halt command program
// if specified, executes host + 0xbb or host only shutdown,
// and sets time delay before shutdown,
// ie :
// bbhalt 1 30
// will poweroff host (raspberry pi) after 30s delay , then the 0xBB will also power off
// note : the 0xBB can poweroff itself only if the 'one button power on' electric wiring is used.
// refer to the included picture into this folder if needed
//
// if no arguments provided, ie :
// bbhalt
// uses default values (1,10) for the same function as the above details.
//
// nb : strongly needs code cleanup and optimisation, just here as a basis 
// to understand the 0xBB and chantilly access routines from the libraries
//
// ***********************************************************************************************
#include <stdint.h>
#include <stdio.h>
//
#define  _MODEL_B2
//#define _MODEL_BP
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
	//
	if(CHAN_setup("BBHALT",1)!=0) { printf("Error opening Chantilly, quit\n"); CHAN_close();exit(-1);} // try a close
	// get args
	errors=0;
	if(argc==3)	// arg[1]= 0/1 : host only or host+chantilly
	{	
		sscanf(argv[1],"%c",(char*) &poweroff_mode);
#ifdef _VERBOSE		
		printf("\tARG[1]  poweroff_mode  (%c)\n",(char)poweroff_mode[0]);fflush(stdout); 
#endif
		//
		sscanf(argv[2],"%d",&poweroff_seconds);
#ifdef _VERBOSE		
		printf("\tARG[2]  poweroff_seconds  (%3.3d)\n",(char)poweroff_seconds);fflush(stdout);
#endif
		//
		
		// set poweroff mode,
		if(poweroff_mode[0]=='1') {txb[0]=1;}else{txb[0]=0;}
		txb[1]=0;
#ifdef _VERBOSE		
		printf("txb[0]=%d  txb[1]=%d\n",txb[0],txb[1]);
#endif
		errors+=CHAN_addr(_BB_BOARD,0x120);
		errors+=CHAN_setBytes(_BB_BOARD,2,txb);
		// verify
		errors+=CHAN_addr(_BB_BOARD,0x120);
		errors+=CHAN_getBytes(_BB_BOARD,2,rxb);
#ifdef _VERBOSE		
		printf("now poweroff value[%02x] \n",rxb[0]);
#endif
		//
		// set delay for poweroff, immediate modification
		errors+=CHAN_addr(_BB_BOARD,0x114);
		errors+=CHAN_getBytes(_BB_BOARD,2,rxb);
#ifdef _VERBOSE		
		printf("LO/HI seconds poweroff original [%02x %02x] \n",rxb[0],rxb[1]);
#endif
		//
		poweroff_secs16=(uint16_t) poweroff_seconds;
		errors+=CHAN_addr(_BB_BOARD,0x114);
		errors+=CHAN_setBytes(_BB_BOARD,2,(uint8_t*) &poweroff_secs16);
		
	}
	else
	{
		// set poweroff mode, defaults
		txb[0]=1;
		txb[1]=0;
		//printf("txb[0]=%d  txb[1]=%d\n",txb[0],txb[1]);
		errors+=CHAN_addr(_BB_BOARD,0x120);
		errors+=CHAN_setBytes(_BB_BOARD,2,txb);
		//
		//
		poweroff_secs16=(uint16_t) 10;
		errors+=CHAN_addr(_BB_BOARD,0x114);
		errors+=CHAN_setBytes(_BB_BOARD,2,(uint8_t*) &poweroff_secs16);
		//
		//
	}
	//
	//
	// execute poweroff with selected mode or default, 0xBB's ram values
	//
	CHAN_command(_BB_BOARD,0x06);
#ifdef _VERBOSE	
		printf("Shutting down the system and BusBoard\n");fflush(stdout);
#endif
	//
	usleep(100000);
	CHAN_close();
	usleep(100000);
	//
#ifdef _VERBOSE	
		printf("BBhalt, exit ,errors:%d\n",errors);fflush(stdout);
		printf("Performing system halt...\n");fflush(stdout);
#endif
	//
	system("halt");
	
	return 0;
}
