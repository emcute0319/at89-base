
/*****************************************************************************
 * Register: 0x80 - 0x87
 ****************************************************************************/
#if ( !defined(_CPU_AT89C2051_) && !defined(_CPU_AT89C4051_) )
SFR(P0, 0x80);
 SBIT(P0_0, 0x80, 0);
 SBIT(P0_1, 0x80, 1);
 SBIT(P0_2, 0x80, 2);
 SBIT(P0_3, 0x80, 3);
 SBIT(P0_4, 0x80, 4);
 SBIT(P0_5, 0x80, 5);
 SBIT(P0_6, 0x80, 6);
 SBIT(P0_7, 0x80, 7);
#endif

SFR(SP, 0x81);
SFR(DPL, 0x82);
SFR(DPH, 0x83);

#if ( defined(_CPU_AT89S51_) || defined(_CPU_AT89S52_) )
SFR(DP1H, 0x84);
SFR(DP1L, 0x85);
#endif

SFR(PCON, 0x87);
 #define IDL_BIT    0
 #define STOP_BIT   1
 #define PD_BIT     1    /* Alternate definition */
 #define GF0_BIT    2
 #define GF1_BIT    3
 #define SMOD_BIT   7


/*****************************************************************************
 * Register: 0x88 - 0x8F
 ****************************************************************************/
SFR(TCON, 0x88);
 SBIT(IT0, 0x88, 0);
 SBIT(IE0, 0x88, 1);
 SBIT(IT1, 0x88, 2);
 SBIT(IE1, 0x88, 3);
 SBIT(TR0, 0x88, 4);
 SBIT(TF0, 0x88, 5);
 SBIT(TR1, 0x88, 6);
 SBIT(TF1, 0x88, 7);

SFR(TMOD, 0x89);
 #define T0_M0_BIT   0
 #define T0_M1_BIT   1
 #define T0_CT_BIT   2
 #define T0_GATE_BIT 3
 #define T1_M0_BIT   4
 #define T1_M1_BIT   5
 #define T1_CT_BIT   6
 #define T1_GATE_BIT 7

SFR(TL0, 0x8A);
SFR(TL1, 0x8B);
SFR(TH0, 0x8C);
SFR(TH1, 0x8D);

#if ( defined(_CPU_AT89S51_) || defined(_CPU_AT89S52_) )
SFR(AUXR, 0x8E);
 /* =0, ALE is emitted at a constant rate of 1/6 the oscillator frequency;
  * =1, ALE is active only during a MOVX or MOVC instruction.
  */
 #define DISALE_BIT   0

 /* =0, Reset pin is driven High after WDT times out;
  * =1, Reset pin is input only.
  */
 #define DISRTO_BIT   3

 /* =0, WDT continues to count in IDLE mode;
  * =1, WDT halts counting in IDLE mode.
  */
 #define WDIDLE_BIT   4
#endif


/*****************************************************************************
 * Register: 0x90 - 0x97
 ****************************************************************************/
SFR(P1, 0x90);
 SBIT(P1_0, 0x90, 0);
 SBIT(P1_1, 0x90, 1);
 SBIT(P1_2, 0x90, 2);
 SBIT(P1_3, 0x90, 3);
 SBIT(P1_4, 0x90, 4);
 SBIT(P1_5, 0x90, 5);
 SBIT(P1_6, 0x90, 6);
 SBIT(P1_7, 0x90, 7);

#if ( defined(_CPU_AT89C52_) || defined(_CPU_AT89S52_) )
 /* Second function of this port */
 sbit T2    = 0x90;     /* External input to Timer/Counter 2, clock out */
 sbit T2EX  = 0x91;     /* Timer/Counter 2 capture/reload trigger & dir ctl */
#endif


/*****************************************************************************
 * Register: 0x98 - 0x9F
 ****************************************************************************/
SFR(SCON, 0x98);
 SBIT(RI,  0x98, 0);
 SBIT(TI,  0x98, 1);
 SBIT(RB8, 0x98, 2);
 SBIT(TB8, 0x98, 3);
 SBIT(REN, 0x98, 4);
 SBIT(SM2, 0x98, 5);
 SBIT(SM1, 0x98, 6);
 SBIT(SM0, 0x98, 7);

SFR(SBUF, 0x99);


/*****************************************************************************
 * Register: 0xA0 - 0xA7
 ****************************************************************************/
#if ( !defined(_CPU_AT89C2051_) && !defined(_CPU_AT89C4051_) )
SFR(P2, 0xA0);
 SBIT(P2_0, 0xA0, 0);
 SBIT(P2_1, 0xA0, 1);
 SBIT(P2_2, 0xA0, 2);
 SBIT(P2_3, 0xA0, 3);
 SBIT(P2_4, 0xA0, 4);
 SBIT(P2_5, 0xA0, 5);
 SBIT(P2_6, 0xA0, 6);
 SBIT(P2_7, 0xA0, 7);
#endif

#if ( defined(_CPU_AT89S51_) || defined(_CPU_AT89S52_) )
SFR(AUXR1, 0xA2);
 /* =0, Selects DPTR Registers DP0L, DP0H;
  * =1, Selects DPTR Registers DP1L, DP1H.
  */
 #define DPS_BIT    0

SFR(WDTRST, 0xA6);
#endif


/*****************************************************************************
 * Register: 0xA8 - 0xAF
 ****************************************************************************/
SFR(IE, 0xA8);
 SBIT(EX0, 0xA8, 0);       /* 1=Enable External interrupt 0  */
 SBIT(ET0, 0xA8, 1);       /* 1=Enable Timer 0 interrupt     */
 SBIT(EX1, 0xA8, 2);       /* 1=Enable External interrupt 1  */
 SBIT(ET1, 0xA8, 3);       /* 1=Enable Timer 1 interrupt     */
 SBIT(ES,  0xA8, 4);       /* 1=Enable Serial port interrupt */
#if ( defined(_CPU_AT89C52_) || defined(_CPU_AT89S52_) )
 SBIT(ET2, 0xA8, 5);       /* 1=Enable Timer 2 interrupt     */
#endif
 SBIT(EA,  0xA8, 7);       /* 0=Disable all interrupts       */


/*****************************************************************************
 * Register: 0xB0 - 0xB7
 ****************************************************************************/
SFR(P3, 0xB0);
 SBIT(P3_0, 0xB0, 0);
 SBIT(P3_1, 0xB0, 1);
 SBIT(P3_2, 0xB0, 2);
 SBIT(P3_3, 0xB0, 3);
 SBIT(P3_4, 0xB0, 4);
 SBIT(P3_5, 0xB0, 5);
 SBIT(P3_6, 0xB0, 6);
 SBIT(P3_7, 0xB0, 7);

 /* Second function of this port */
 SBIT(RXD,  0xB0, 0);       /* Serial data input */
 SBIT(TXD,  0xB0, 1);       /* Serial data output */
 SBIT(INT0, 0xB0, 2);       /* External interrupt 0 */
 SBIT(INT1, 0xB0, 3);       /* External interrupt 1 */
 SBIT(T0,   0xB0, 4);       /* Timer 0 external input */
 SBIT(T1,   0xB0, 5);       /* Timer 1 external input */
 SBIT(WR,   0xB0, 6);       /* External data memory write strobe */
 SBIT(RD,   0xB0, 7);       /* External data memory read strobe */


/*****************************************************************************
 * Register: 0xB8 - 0xBF
 ****************************************************************************/
SFR(IP, 0xB8);
 SBIT(PX0, 0xB8, 0);
 SBIT(PT0, 0xB8, 1);
 SBIT(PX1, 0xB8, 2);
 SBIT(PT1, 0xB8, 3);
 SBIT(PS,  0xB8, 4);
#if ( defined(_CPU_AT89C52_) || defined(_CPU_AT89S52_) )
 SBIT(PT2, 0xB8, 5);
#endif


/*****************************************************************************
 * Register: 0xC0 - 0xC7
 ****************************************************************************/


/*****************************************************************************
 * Register: 0xC8 - 0xCF
 ****************************************************************************/
#if ( defined(_CPU_AT89C52_) || defined(_CPU_AT89S52_) )
SFR(T2CON, 0xC8);
 SBIT(CP_RL2, 0xC8, 0);    /* 0=Reload, 1=Capture select                      */
 SBIT(C_T2,   0xC8, 1);    /* 0=Timer, 1=Counter                              */
 SBIT(TR2,    0xC8, 2);    /* 0=Stop timer, 1=Start timer                     */
 SBIT(EXEN2,  0xC8, 3);    /* Timer 2 external enable                         */
 SBIT(TCLK,   0xC8, 4);    /* 0=Serial clock uses Timer 1 overflow, 1=Timer 2 */
 SBIT(RCLK,   0xC8, 5);    /* 0=Serial clock uses Timer 1 overflow, 1=Timer 2 */
 SBIT(EXF2,   0xC8, 6);    /* Timer 2 external flag                           */
 SBIT(TF2,    0xC8, 7);    /* Timer 2 overflow flag                           */
SFR(T2MOD, 0xC9);
 #define DCEN_BIT   0   /* 1=Timer 2 can be configured as up/down counter  */
 #define T2OE_BIT   1   /* Timer 2 output enable                           */
SFR(RCAP2L, 0xCA);
SFR(RCAP2H, 0xCB);
SFR(TL2, 0xCC);
SFR(TH2, 0xCD);
#endif


/*****************************************************************************
 * Register: 0xD0 - 0xD7
 ****************************************************************************/
SFR(PSW, 0xD0);
 SBIT(P,   0xD0, 0);
 SBIT(FL,  0xD0, 1);
 SBIT(OV,  0xD0, 2);
 SBIT(RS0, 0xD0, 3);
 SBIT(RS1, 0xD0, 4);
 SBIT(F0,  0xD0, 5);
 SBIT(AC,  0xD0, 6);
 SBIT(CY,  0xD0, 7);


/*****************************************************************************
 * Register: 0xD8 - 0xDF
 ****************************************************************************/


/*****************************************************************************
 * Register: 0xE0 - 0xE7
 ****************************************************************************/
SFR(ACC, 0xE0);


/*****************************************************************************
 * Register: 0xE8 - 0xEF
 ****************************************************************************/


/*****************************************************************************
 * Register: 0xF0 - 0xF7
 ****************************************************************************/
SFR(B, 0xF0);


/*****************************************************************************
 * Register: 0xF8 - 0xFF
 ****************************************************************************/


