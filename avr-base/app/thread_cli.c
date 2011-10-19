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
 *   CLI thread, only support VT100.
 * HISTORY:
 *   2011.10.11        Panda.Xiong         Create/Update
 *
*****************************************************************************/

#include "protothread.h"
#include "cli_porting.h"


#if 1

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

static struct
{
    UINT8 CONST    *pName;
    void            (*pExec)(IN UINT8 vParam, IN UINT8 *aParam[]);
    UINT8 CONST    *pHelp;
} CONST aCmdTable[] = CLI_CMD_LIST;

#define cli_vt_DisplayPrompt()  CLI_VT_Printf("\n\r%s>", CLI_PROMPT)

/* read command */
static UINT8 *cli_vt_ReadCommand(void)
{
    SINT16  vReadKey;

    /* read key from VT */
    vReadKey = CLI_VT_ReadKey();

    if (vReadKey != -1)
    {
        static UINT8    aCmdBuf[CLI_CMD_BUF_MAX+1];
        static UINT8    vCmdBufCount = 0;
        UINT8   vKey = (UINT8)vReadKey;

        /* check input key */
        switch (vKey)
        {
            case VT_KEY_CR: /* enter */
            case VT_KEY_LF:
                /* command received */
                aCmdBuf[++vCmdBufCount] = '\0'; /* end with \0 */
                vCmdBufCount = 0;
                return aCmdBuf;

            case VT_KEY_BS:
                if (vCmdBufCount != 0)
                {
                    CLI_VT_Printf("\b \b");
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
                        CLI_VT_Printf("%c", vKey);
                    }
                }
                break;
        }
    }

    /* no command received yet */
    return NULL;
}

static UINT8 cli_vt_ParseCmd(IN OUT UINT8 *ptr, OUT UINT8 *param[])
{
    UINT8   n = 0;

    while (*ptr != '\0')
    {
        /* skip spaces */
        while (*ptr == ' ')
        {
            ptr++;
        }

        if (*ptr == '\0')
        {
            return n;
        }

        param[n++] = ptr;
        while (*ptr != ' ')
        {
            if (*ptr == '\0')
            {
                return n;
            }

            ptr++;
        }

        /* add end character to this parameter */
        *ptr++ = '\0';
    }

    return n;
}

static void cli_vt_ShowHelp(void)
{
    UINT8   vLoop;

    CLI_VT_Printf("\n\rAvailable Commands :");

    for (vLoop = 0; vLoop < COUNT_OF(aCmdTable); vLoop++)
    {
        CLI_VT_Printf("\n\r %s : %s",
                      aCmdTable[vLoop].pName,
                      aCmdTable[vLoop].pHelp);
    }
}

static SINT8 _strcmp(UINT8 *s1, UINT8 CONST *s2)
{
    for (; *s1 == *s2; ++s1, ++s2)
      if (*s1 == '\0')
        return 0;

    return ((*s1 < *s2)? -1 : +1);
}

#endif


static volatile PT_SCB vVT_Rx;

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_VECTOR_UART_RX
 * DESCRIPTION:
 *      UART Rx ISR.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.10.19        panda.xiong         Create/Update
 *****************************************************************************/
INTERRUPT_PROTO(DRV_VECTOR_UART_RX, USART_RXC);
INTERRUPT(DRV_VECTOR_UART_RX, USART_RXC)
{
    PT_SEM_SIGNAL(NULL, &vVT_Rx);
}


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
        PT_SEM_WAIT(pt, &vVT_Rx);

        /* read command */
        pCmd = cli_vt_ReadCommand();

        if (pCmd != NULL)
        {
            UINT8   vParam;
            UINT8  *aParam[CLI_MAX_PARAM];

            /* parse command line */
            vParam = cli_vt_ParseCmd(pCmd, aParam);

            if (vParam != 0)
            {
                UINT8   vLoop;

                if (_strcmp(aParam[0], "?") == 0)
                {
                    cli_vt_ShowHelp();
                }
                else
                {
                    /* search & execute command */
                    for (vLoop = 0; vLoop < COUNT_OF(aCmdTable); vLoop++)
                    {
                        if (_strcmp(aParam[0], aCmdTable[vLoop].pName) == 0)
                        {
                            aCmdTable[vLoop].pExec(vParam, aParam);
                            break;
                        }
                    }
                    if (vLoop == COUNT_OF(aCmdTable))
                    {
                        CLI_VT_Printf("\n\r Invalid command!");
                    }
                }
            }

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
    PT_SEM_INIT(&vVT_Rx, 0);

    /* display prompt */
    cli_vt_DisplayPrompt();
}

