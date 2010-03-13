
/*****************************************************************************
 * Register: 0x80 - 0x87
 ****************************************************************************/
#if ( !defined(_CPU_AT89C2051_) && !defined(_CPU_AT89C4051_) )
sfr   P0    = 0x80;
 sbit P0_0  = 0x80;
 sbit P0_1  = 0x81;
 sbit P0_2  = 0x82;
 sbit P0_3  = 0x83;
 sbit P0_4  = 0x84;
 sbit P0_5  = 0x85;
 sbit P0_6  = 0x86;
 sbit P0_7  = 0x87;
#endif

sfr SP      = 0x81;
sfr DPL     = 0x82;
sfr DPH     = 0x83;

#if ( defined(_CPU_AT89S51_) || defined(_CPU_AT89S52_) )
sfr DP1H    = 0x84;
sfr DP1L    = 0x85;
#endif

sfr PCON    = 0x87;
 #define IDL_BIT    0
 #define STOP_BIT   1
 #define PD_BIT     1    /* Alternate definition */
 #define GF0_BIT    2
 #define GF1_BIT    3
 #define SMOD_BIT   7


/*****************************************************************************
 * Register: 0x88 - 0x8F
 ****************************************************************************/
sfr   TCON  = 0x88;
 sbit IT0   = 0x88;
 sbit IE0   = 0x89;
 sbit IT1   = 0x8A;
 sbit IE1   = 0x8B;
 sbit TR0   = 0x8C;
 sbit TF0   = 0x8D;
 sbit TR1   = 0x8E;
 sbit TF1   = 0x8F;

sfr TMOD    = 0x89;
 #define T0_M0_BIT   0
 #define T0_M1_BIT   1
 #define T0_CT_BIT   2
 #define T0_GATE_BIT 3
 #define T1_M0_BIT   4
 #define T1_M1_BIT   5
 #define T1_CT_BIT   6
 #define T1_GATE_BIT 7

sfr TL0     = 0x8A;
sfr TL1     = 0x8B;
sfr TH0     = 0x8C;
sfr TH1     = 0x8D;

#if ( defined(_CPU_AT89S51_) || defined(_CPU_AT89S52_) )
sfr AUXR    = 0x8E;
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
sfr   P1    = 0x90;
 sbit P1_0  = 0x90;
 sbit P1_1  = 0x91;
 sbit P1_2  = 0x92;
 sbit P1_3  = 0x93;
 sbit P1_4  = 0x94;
 sbit P1_5  = 0x95;
 sbit P1_6  = 0x96;
 sbit P1_7  = 0x97;

#if ( defined(_CPU_AT89C52_) || defined(_CPU_AT89S52_) )
 /* Second function of this port */
 sbit T2    = 0x90;     /* External input to Timer/Counter 2, clock out */
 sbit T2EX  = 0x91;     /* Timer/Counter 2 capture/reload trigger & dir ctl */
#endif


/*****************************************************************************
 * Register: 0x98 - 0x9F
 ****************************************************************************/
sfr   SCON  = 0x98;
 sbit RI    = 0x98;
 sbit TI    = 0x99;
 sbit RB8   = 0x9A;
 sbit TB8   = 0x9B;
 sbit REN   = 0x9C;
 sbit SM2   = 0x9D;
 sbit SM1   = 0x9E;
 sbit SM0   = 0x9F;

sfr SBUF    = 0x99;


/*****************************************************************************
 * Register: 0xA0 - 0xA7
 ****************************************************************************/
#if ( !defined(_CPU_AT89C2051_) && !defined(_CPU_AT89C4051_) )
sfr   P2    = 0xA0;
 sbit P2_0  = 0xA0;
 sbit P2_1  = 0xA1;
 sbit P2_2  = 0xA2;
 sbit P2_3  = 0xA3;
 sbit P2_4  = 0xA4;
 sbit P2_5  = 0xA5;
 sbit P2_6  = 0xA6;
 sbit P2_7  = 0xA7;
#endif

#if ( defined(_CPU_AT89S51_) || defined(_CPU_AT89S52_) )
sfr AUXR1   = 0xA2;
 /* =0, Selects DPTR Registers DP0L, DP0H;
  * =1, Selects DPTR Registers DP1L, DP1H.
  */
 #define DPS_BIT    0

sfr WDTRST  = 0xA6;
#endif


/*****************************************************************************
 * Register: 0xA8 - 0xAF
 ****************************************************************************/
sfr   IE    = 0xA8;
 sbit EX0   = 0xA8;       /* 1=Enable External interrupt 0  */
 sbit ET0   = 0xA9;       /* 1=Enable Timer 0 interrupt     */
 sbit EX1   = 0xAA;       /* 1=Enable External interrupt 1  */
 sbit ET1   = 0xAB;       /* 1=Enable Timer 1 interrupt     */
 sbit ES    = 0xAC;       /* 1=Enable Serial port interrupt */
#if ( defined(_CPU_AT89C52_) || defined(_CPU_AT89S52_) )
 sbit ET2   = 0xAD;       /* 1=Enable Timer 2 interrupt     */
#endif
 sbit EA    = 0xAF;       /* 0=Disable all interrupts       */


/*****************************************************************************
 * Register: 0xB0 - 0xB7
 ****************************************************************************/
sfr   P3    = 0xB0;
 sbit P3_0  = 0xB0;
 sbit P3_1  = 0xB1;
 sbit P3_2  = 0xB2;
 sbit P3_3  = 0xB3;
 sbit P3_4  = 0xB4;
 sbit P3_5  = 0xB5;
 sbit P3_6  = 0xB6;
 sbit P3_7  = 0xB7;

 /* Second function of this port */
 sbit RXD   = 0xB0;       /* Serial data input */
 sbit TXD   = 0xB1;       /* Serial data output */
 sbit INT0  = 0xB2;       /* External interrupt 0 */
 sbit INT1  = 0xB3;       /* External interrupt 1 */
 sbit T0    = 0xB4;       /* Timer 0 external input */
 sbit T1    = 0xB5;       /* Timer 1 external input */
 sbit WR    = 0xB6;       /* External data memory write strobe */
 sbit RD    = 0xB7;       /* External data memory read strobe */


/*****************************************************************************
 * Register: 0xB8 - 0xBF
 ****************************************************************************/
sfr   IP    = 0xB8;
 sbit PX0   = 0xB8;
 sbit PT0   = 0xB9;
 sbit PX1   = 0xBA;
 sbit PT1   = 0xBB;
 sbit PS    = 0xBC;
#if ( defined(_CPU_AT89C52_) || defined(_CPU_AT89S52_) )
 sbit PT2   = 0xBD;
#endif


/*****************************************************************************
 * Register: 0xC0 - 0xC7
 ****************************************************************************/


/*****************************************************************************
 * Register: 0xC8 - 0xCF
 ****************************************************************************/
#if ( defined(_CPU_AT89C52_) || defined(_CPU_AT89S52_) )
sfr T2CON   = 0xC8;
 sbit CP_RL2= 0xC8;     /* 0=Reload, 1=Capture select                      */
 sbit C_T2  = 0xC9;     /* 0=Timer, 1=Counter                              */
 sbit TR2   = 0xCA;     /* 0=Stop timer, 1=Start timer                     */
 sbit EXEN2 = 0xCB;     /* Timer 2 external enable                         */
 sbit TCLK  = 0xCC;     /* 0=Serial clock uses Timer 1 overflow, 1=Timer 2 */
 sbit RCLK  = 0xCD;     /* 0=Serial clock uses Timer 1 overflow, 1=Timer 2 */
 sbit EXF2  = 0xCE;     /* Timer 2 external flag                           */
 sbit TF2   = 0xCF;     /* Timer 2 overflow flag                           */
sfr T2MOD   = 0xC9;
 #define DCEN_BIT   0   /* 1=Timer 2 can be configured as up/down counter  */
 #define T2OE_BIT   1   /* Timer 2 output enable                           */
sfr RCAP2L  = 0xCA;
sfr RCAP2H  = 0xCB;
sfr TL2     = 0xCC;
sfr TH2     = 0xCD;
#endif


/*****************************************************************************
 * Register: 0xD0 - 0xD7
 ****************************************************************************/
sfr   PSW   = 0xD0;
 sbit P     = 0xD0;
 sbit FL    = 0xD1;
 sbit OV    = 0xD2;
 sbit RS0   = 0xD3;
 sbit RS1   = 0xD4;
 sbit F0    = 0xD5;
 sbit AC    = 0xD6;
 sbit CY    = 0xD7;


/*****************************************************************************
 * Register: 0xD8 - 0xDF
 ****************************************************************************/


/*****************************************************************************
 * Register: 0xE0 - 0xE7
 ****************************************************************************/
sfr ACC     = 0xE0;


/*****************************************************************************
 * Register: 0xE8 - 0xEF
 ****************************************************************************/


/*****************************************************************************
 * Register: 0xF0 - 0xF7
 ****************************************************************************/
sfr B       = 0xF0;


/*****************************************************************************
 * Register: 0xF8 - 0xFF
 ****************************************************************************/


