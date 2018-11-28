// ----------------------------------------------------------------------------
// myClocks.c  (for lab_04a_clock project)  ('FR6989 Launchpad)
//
// This routine sets ACLK to run from VLO, then configures MCLK and SMCLK to
// run from the and high-freq internal clock source (DCO).
//    ACLK  = ~10KHz
//    SMCLK =  8MHz
//    MCLK  =  8MHz
// ----------------------------------------------------------------------------

//***** Header Files **********************************************************
//#include <stdbool.h>
#include <driverlib.h>
#include <myClocks.h>


//***** Defines ***************************************************************
#define LF_CRYSTAL_FREQUENCY_IN_HZ     32768
#define HF_CRYSTAL_FREQUENCY_IN_HZ     0                                        // FR6989 Launchpad does not ship with HF Crystal populated


//***** Global Variables ******************************************************
uint32_t myACLK  = 0;
uint32_t mySMCLK = 0;
uint32_t myMCLK  = 0;


//***** initClocks ************************************************************
void initClocks(void) {

    //**************************************************************************
    // Configure Oscillators
    //**************************************************************************
    // Set the crystal frequencies attached to the LFXT and HFXT oscillator pins
	// so that driverlib knows how fast they are (needed for the clock 'get' functions)
	CS_setExternalClockSource( LF_CRYSTAL_FREQUENCY_IN_HZ , HF_CRYSTAL_FREQUENCY_IN_HZ);

    // Verify if the default clock settings are as expected
    myACLK  = CS_getACLK();
    mySMCLK = CS_getSMCLK();
    myMCLK  = CS_getMCLK();

    // Set FRAM Controller waitstates to 1 when MCLK > 8MHz (per datasheet)
	// Please refer to the "Non-Volatile Memory" chapter for more details
	//FRAMCtl_configureWaitStateControl( FRAMCTL_ACCESS_TIME_CYCLES_1 );

    // Set DCO to run at 8MHz
    CS_setDCOFreq(  CS_DCORSEL_1, CS_DCOFSEL_3 );               //check page 174 for explanation                                // Set Frequency range (DCOR)
                                                                  // Set Frequency (DCOF)


    //**************************************************************************
    // Configure Clocks
    //**************************************************************************
    // Set ACLK to use VLO as its oscillator source (~10KHz)
    CS_initClockSignal( CS_ACLK,CS_VLOCLK_SELECT,  CS_CLOCK_DIVIDER_1 );                                                          // Clock you're configuring
                                                            // Clock source
                                                             // Divide down clock source by this much


    // Set SMCLK to use DCO as its oscillator source (DCO was configured earlier in this function for 8MHz)
    CS_initClockSignal( CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1 );
                                                                       // Clock you're configuring
                                                          // Clock source
                                                              // Divide down clock source by this much


    // Set MCLK to use DCO as its oscillator source (DCO was configured earlier in this function for 8MHz)
    CS_initClockSignal( CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1 );
                                                                        // Clock you're configuring
                                                            // Clock source
                                                              // Divide down clock source by this much


    // Verify that the modified clock settings are as expected
    myACLK  = CS_getACLK();
    mySMCLK = CS_getSMCLK();
    myMCLK  = CS_getMCLK();
}

