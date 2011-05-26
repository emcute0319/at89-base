
/*****************************************************************************
 * Register: 0x80 - 0x87
 ****************************************************************************/
#if ( !defined(_CPU_AT89C2051_) && !defined(_CPU_AT89C4051_) )
SFR(P0, 0x80);
 SBIT(P0_0, P0, 0);
 SBIT(P0_1, P0, 1);
 SBIT(P0_2, P0, 2);
 SBIT(P0_3, P0, 3);
 SBIT(P0_4, P0, 4);
 SBIT(P0_5, P0, 5);
 SBIT(P0_6, P0, 6);
 SBIT(P0_7, P0, 7);
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
 SBIT(IT0, TCON, 0);
 SBIT(IE0, TCON, 1);
 SBIT(IT1, TCON, 2);
 SBIT(IE1, TCON, 3);
 SBIT(TR0, TCON, 4);
 SBIT(TF0, TCON, 5);
 SBIT(TR1, TCON, 6);
 SBIT(TF1, TCON, 7);

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
 SBIT(P1_0, P1, 0);
 SBIT(P1_1, P1, 1);
 SBIT(P1_2, P1, 2);
 SBIT(P1_3, P1, 3);
 SBIT(P1_4, P1, 4);
 SBIT(P1_5, P1, 5);
 SBIT(P1_6, P1, 6);
 SBIT(P1_7, P1, 7);

#if ( defined(_CPU_AT89C52_) || defined(_CPU_AT89S52_) )
 /* Second function of this port */
 sbit T2    = 0x90;     /* External input to Timer/Counter 2, clock out */
 sbit T2EX  = 0x91;     /* Timer/Counter 2 capture/reload trigger & dir ctl */
#endif


/*****************************************************************************
 * Register: 0x98 - 0x9F
 ****************************************************************************/
SFR(SCON, 0x98);
 SBIT(RI,  SCON, 0);
 SBIT(TI,  SCON, 1);
 SBIT(RB8, SCON, 2);
 SBIT(TB8, SCON, 3);
 SBIT(REN, SCON, 4);
 SBIT(SM2, SCON, 5);
 SBIT(SM1, SCON, 6);
 SBIT(SM0, SCON, 7);

SFR(SBUF, 0x99);


/*****************************************************************************
 * Register: 0xA0 - 0xA7
 ****************************************************************************/
#if ( !defined(_CPU_AT89C2051_) && !defined(_CPU_AT89C4051_) )
SFR(P2, 0xA0);
 SBIT(P2_0, P2, 0);
 SBIT(P2_1, P2, 1);
 SBIT(P2_2, P2, 2);
 SBIT(P2_3, P2, 3);
 SBIT(P2_4, P2, 4);
 SBIT(P2_5, P2, 5);
 SBIT(P2_6, P2, 6);
 SBIT(P2_7, P2, 7);
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
 SBIT(EX0, IE, 0);       /* 1=Enable External interrupt 0  */
 SBIT(ET0, IE, 1);       /* 1=Enable Timer 0 interrupt     */
 SBIT(EX1, IE, 2);       /* 1=Enable External interrupt 1  */
 SBIT(ET1, IE, 3);       /* 1=Enable Timer 1 interrupt     */
 SBIT(ES,  IE, 4);       /* 1=Enable Serial port interrupt */
#if ( defined(_CPU_AT89C52_) || defined(_CPU_AT89S52_) )
 SBIT(ET2, IE, 5);       /* 1=Enable Timer 2 interrupt     */
#endif
 SBIT(EA,  IE, 7);       /* 0=Disable all interrupts       */


/*****************************************************************************
 * Register: 0xB0 - 0xB7
 ****************************************************************************/
SFR(P3, 0xB0);
 SBIT(P3_0, P3, 0);
 SBIT(P3_1, P3, 1);
 SBIT(P3_2, P3, 2);
 SBIT(P3_3, P3, 3);
 SBIT(P3_4, P3, 4);
 SBIT(P3_5, P3, 5);
 SBIT(P3_6, P3, 6);
 SBIT(P3_7, P3, 7);

 /* Second function of this port */
 SBIT(RXD,  P3, 0);       /* Serial data input */
 SBIT(TXD,  P3, 1);       /* Serial data output */
 SBIT(INT0, P3, 2);       /* External interrupt 0 */
 SBIT(INT1, P3, 3);       /* External interrupt 1 */
 SBIT(T0,   P3, 4);       /* Timer 0 external input */
 SBIT(T1,   P3, 5);       /* Timer 1 external input */
 SBIT(WR,   P3, 6);       /* External data memory write strobe */
 SBIT(RD,   P3, 7);       /* External data memory read strobe */


/*****************************************************************************
 * Register: 0xB8 - 0xBF
 ****************************************************************************/
SFR(IP, 0xB8);
 SBIT(PX0, IP, 0);
 SBIT(PT0, IP, 1);
 SBIT(PX1, IP, 2);
 SBIT(PT1, IP, 3);
 SBIT(PS,  IP, 4);
#if ( defined(_CPU_AT89C52_) || defined(_CPU_AT89S52_) )
 SBIT(PT2, IP, 5);
#endif


/*****************************************************************************
 * Register: 0xC0 - 0xC7
 ****************************************************************************/


/*****************************************************************************
 * Register: 0xC8 - 0xCF
 ****************************************************************************/
#if ( defined(_CPU_AT89C52_) || defined(_CPU_AT89S52_) )
SFR(T2CON, 0xC8);
 SBIT(CP_RL2, T2CON, 0);    /* 0=Reload, 1=Capture select                      */
 SBIT(C_T2,   T2CON, 1);    /* 0=Timer, 1=Counter                              */
 SBIT(TR2,    T2CON, 2);    /* 0=Stop timer, 1=Start timer                     */
 SBIT(EXEN2,  T2CON, 3);    /* Timer 2 external enable                         */
 SBIT(TCLK,   T2CON, 4);    /* 0=Serial clock uses Timer 1 overflow, 1=Timer 2 */
 SBIT(RCLK,   T2CON, 5);    /* 0=Serial clock uses Timer 1 overflow, 1=Timer 2 */
 SBIT(EXF2,   T2CON, 6);    /* Timer 2 external flag                           */
 SBIT(TF2,    T2CON, 7);    /* Timer 2 overflow flag                           */
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
 SBIT(P,   PSW, 0);
 SBIT(FL,  PSW, 1);
 SBIT(OV,  PSW, 2);
 SBIT(RS0, PSW, 3);
 SBIT(RS1, PSW, 4);
 SBIT(F0,  PSW, 5);
 SBIT(AC,  PSW, 6);
 SBIT(CY,  PSW, 7);


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


