'''
*******************************************************************************
 Desc    : A script used to convert the hardware definitions.
 Note    : N/A
 History : 2011-09-13    Panda.Xiong     Create
*******************************************************************************
'''

import sys
import time
import re

sCurrentTime = time.strftime("%Y/%m/%d %M:%H:%S", time.localtime())

sNotes = '''
/*
 * This is automatically generated file, do not modify it !!!
 * Create Time: %s
 */

''' % (sCurrentTime)

in_file  = sys.argv[1]
out_file = sys.argv[2]

# open file
fin  = file(in_file, 'r')
fout = file(out_file, 'w')

fout.write(sNotes)

# parse file line by line
vLine = 0
for line in fin:
    vLine += 1

    line.strip()

    if line[0:15] == 'DECLARE_IO_PORT':
        # IO Port

        s_regex = r'^\((\w+),\s*_PORT\(([A-Z])\),\s*"([^"]+)"\)'
        p = re.compile(s_regex)
        result = p.split(line[15:])[1:-1]

        if not result:
            print '*** Error: Parsing failed at line %d. -1' % (vLine)
            sys.exit(-1)

        (name, port, desc) = result

        fout.write('/* %s */\n' % (name))

        # define IO direction
        sRegName = 'DDR'
        sPort = 'IO_PORT_%s_%s' % (name, sRegName)
        fout.write('#define %-25s %s%s\n' % (sPort, sRegName, port))

        # define IO output
        sRegName = 'PORT'
        sPort = 'IO_PORT_%s_%s' % (name, sRegName)
        fout.write('#define %-25s %s%s\n' % (sPort, sRegName, port))

        # define IO input
        sRegName = 'PIN'
        sPort = 'IO_PORT_%s_%s' % (name, sRegName)
        fout.write('#define %-25s %s%s\n' % (sPort, sRegName, port))

        # define IO description
        sRegName = 'DESC'
        sPort = 'IO_PORT_%s_%s' % (name, sRegName)
        fout.write('#define %-25s "%s"\n' % (sPort, desc))

        fout.write('\n')

    elif line[0:14] == 'DECLARE_IO_PIN':
        # IO Pin

        s_regex = r'^\((\w+),\s*_IO\(([A-Z]),\s*([0-7])\),\s*(\w+),\s*(\w+),\s*(\w+),\s*"([^"]+)"\)'
        p = re.compile(s_regex)
        result = p.split(line[14:])[1:-1]

        if not result:
            print '*** Error: Parsing failed at line %d. -2' % (vLine)
            sys.exit(-1)

        (name, port, bit, mode, init_val, pin, desc) = result

        fout.write('/* %s */\n' % (name))

        # define IO direction
        sRegName = 'DDR'
        sPort = 'IO_PIN_%s_%s' % (name, sRegName)
        fout.write('#define %-25s %s%s_%s%s%s\n' % (sPort, sRegName, port, sRegName, port, bit))

        # define IO output
        sRegName = 'PORT'
        sPort = 'IO_PIN_%s_%s' % (name, sRegName)
        fout.write('#define %-25s %s%s_%s%s%s\n' % (sPort, sRegName, port, sRegName, port, bit))

        # define IO input
        sRegName = 'PIN'
        sPort = 'IO_PIN_%s_%s' % (name, sRegName)
        fout.write('#define %-25s %s%s_%s%s%s\n' % (sPort, sRegName, port, sRegName, port, bit))

        # define IO mode
        sRegName = 'MODE'
        sPort = 'IO_PIN_%s_%s' % (name, sRegName)
        fout.write('#define %-25s %s\n' % (sPort, mode))

        # define IO initial value
        sRegName = 'INIT'
        sPort = 'IO_PIN_%s_%s' % (name, sRegName)
        fout.write('#define %-25s %s\n' % (sPort, init_val))

        # define IO pin number
        sRegName = 'PIN_NO'
        sPort = 'IO_PIN_%s_%s' % (name, sRegName)
        fout.write('#define %-25s %s\n' % (sPort, pin))

        # define IO description
        sRegName = 'DESC'
        sPort = 'IO_PIN_%s_%s' % (name, sRegName)
        fout.write('#define %-25s "%s"\n' % (sPort, desc))

        fout.write('\n')

    else:
        # do nothing
        pass

fout.flush()
fout.close()
fin.close()
