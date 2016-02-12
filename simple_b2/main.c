#include <stdio.h>
#include <CHANTILLY_B2.h>   // local dir

void main(void)
{
    int32_t res;
    uint32_t errors=0;
    uint8_t mybuffer[256];
    bus_struct  my_bus;
    res=CHAN_setup("my application",1);     // gives a name to the first chantilly access opener (this program)
    
    if (res>0) 
    { 
        printf("Error, used by PID {%d}\n",res);  // another program already opened a chantilly direct access
        // Try to Close it
        CHAN_close();
        exit(0);
    }
    if (res==0)     {printf("Success Opening ....\n");}
    // Now,get the power supply raw ADCs values of the BusBoard
    // we point to offset 0x100 into the BusBoard's RAM ( Busboard addr is always 7 )
    errors=CHAN_addr(0x07,0x100);  
    // we read 32 bytes from the BusBoard to our local byte buffer              
    errors+=CHAN_getBytes(0x07,32,mybuffer);    
    // now, mybuffer[0...31] holds the byte values of the BusBoard's RAM values [0x100 .. 0x11f ]
    // we won't use all the bytes : remember that's just a test program.
    // we use a built-in library function, to generate a 16bit (uint16_t) number from 2 consecutive bytes into a source buffer :
    // an alternate method would be to convert the value to a float value ( see paragraph below this sample code )
    printf("Main VDC in (10 bits ADC ) is %d\n",CHAN_getADCfrom(&mybuffer[0])); // 0x100(L)+0x101(H) see 0xBB memmap for details
    printf("3.3 VDC (10 bits ADC ) is %d\n",CHAN_getADCfrom(&mybuffer[4]));     // 0x104(L)+0x105(H) idem
    // conversion MACROS to float , human readable values will be detailled later..
    printf("access errors :%d\n",errors);   // any access errors ? displays it ( should never happen )
    // 
    // checkbus function test
    // check the board information at address7 ( that is, the busboard for this example )
    // populates the my_bus structure with relevant informations
    // last parameter '1' tells the function to display (printf) the results on terminal
    CHAN_checkBUS(&my_bus,7,1);
    //
    // whatever the result, let's try  a close()    
    //
    res=CHAN_close();
    if(res>0) { printf("Chan_setup by processId{%d} , with hot-stop disabled\n"); }
    else if (res<0) { printf("Error, other{%d}\n",res);}
    else {printf("success\n");} 
}
