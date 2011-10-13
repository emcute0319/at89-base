/******************************************************************************
 *
 * (C) Copyright 2007-2010
 *   This program is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU General Public License as
 *   published by the Free Software Foundation; either version 2 of
 *   the License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *   MA 02111-1307 USA
 *
 * FILE NAME:
 *   thread_cli.c
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2011.10.11        Panda.Xiong         Create/Update
 *
*****************************************************************************/

#include "protothread.h"


#if 1

#define CLI_PROMPT          ""
#define CLI_CMD_BUF_MAX     80

/* Define key ascii value */
#define VT_KEY_ESC          (27)
#define VT_KEY_CR           (13)  /* CR, '\n' */
#define VT_KEY_SPACE        (32)
#define VT_KEY_LF           (10)  /* LF, '\r' */
#define VT_KEY_TAB          (9)
#define VT_KEY_BS           (8)
#define VT_KEY_CTRL_D       (0x04)
#define VT_KEY_CTRL_L       (0x0C)
#define VT_KEY_CTRL_C       (0x03)
#define VT_KEY_CTRL_T       (0x14)
#define VT_KEY_CTRL_R       (0x12)
#define VT_KEY_CTRL_S       (0x13)
#define VT_KEY_CTRL_U       (0x15)
#define VT_KEY_CTRL_Z       (0x1A)

#define cli_vt_Printf(...)      DRV_UART_Printf(__VA_ARGS__)
#define cli_vt_ReadKey()        DRV_UART_ReadByte()

#define cli_vt_DisplayPrompt()  cli_vt_Printf("\n\r%s>", CLI_PROMPT)

/* init CLI VT driver */
static void cli_vt_Init(void)
{}

/* clear VT screen */
static void cli_vt_ClearScreen(void)
{}

/* read command */
static UINT8 *cli_vt_ReadCommand(void)
{
    static UINT8    aCmdBuf[CLI_CMD_BUF_MAX+1];
    static UINT8    vCmdBufCount = 0;
    UINT8   vKey;

    /* read key from VT */
    vKey = cli_vt_ReadKey();

    /* check input key */
    switch (vKey)
    {
        case VT_KEY_CR: /* enter */
        case VT_KEY_LF:
            /* received a command */
            aCmdBuf[++vCmdBufCount] = '\0'; /* end with \0 */
            vCmdBufCount = 0;
            return aCmdBuf;

        case VT_KEY_CTRL_Z: /* clear current command line */
            while (vCmdBufCount != 0)
            {
                cli_vt_Printf("\b \b");
                vCmdBufCount--;
            }
            break;

        case VT_KEY_BS:
            if (vCmdBufCount != 0)
            {
                cli_vt_Printf("\b \b");
                vCmdBufCount--;
            }
            break;

        default:
			if ((vKey < 0x20) || (vKey > 0x7F))
			{
                /* this is not a visible charactor */
			}
            else
            {
                /* if command buffer not full, record it */
                if (vCmdBufCount < COUNT_OF(aCmdBuf))
                {
                    aCmdBuf[++vCmdBufCount] = vKey;
                    cli_vt_Printf("%c", vKey);
                }
            }
            break;
    }

    /* not received a command yet */
    return NULL;
}

#endif


static volatile PT_SCB vVT_Rx;

/******************************************************************************
 * FUNCTION NAME:
 *      thread_Cli_Entry
 * DESCRIPTION:
 *      Cli Thread Entry.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      PT_HANDLE
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.3.24        Panda.Xiong         Create/Update
 *****************************************************************************/
PT_HANDLE thread_Cli_Entry(PT_TCB *pt)
{
    PT_BEGIN(pt);

    for (;;)
    {
        UINT8  *pCmd;

        /* wait for CLI input key */
        PT_SEM_WAIT(pt, vVT_Rx);

        /* read command */
        pCmd = cli_vt_ReadCommand();

        if (pCmd != NULL)
        {
            /* parse command line */
            //

            /* display prompt */
            cli_vt_DisplayPrompt();
        }
    }

    PT_END(pt);
}


/******************************************************************************
 * FUNCTION NAME:
 *      thread_Cli_Init
 * DESCRIPTION:
 *      N/A
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.4.6        PANDA         Create/Update
 *****************************************************************************/
void thread_Cli_Init(void)
{
    PT_SEM_INIT(vVT_Rx);

    cli_vt_Init();
    cli_vt_ClearScreen();

    /* display prompt */
    cli_vt_DisplayPrompt();
}

