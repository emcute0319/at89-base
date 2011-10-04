'''
*******************************************************************************
 Desc    : A script used to convert the hardware definitions.
 Note    : N/A
 History : 2011-09-13    Panda.Xiong     Create
*******************************************************************************
'''


def _io_port_def(name, fout, sRegName, ss):
    sPort = 'IO_PORT_%s_%s' % (name, sRegName)
    fout.write('#define %-25s %s\n' % (sPort, ss))

def _io_pin_def(name, fout, sRegName, ss):
    sPort = 'IO_PIN_%s_%s' % (name, sRegName)
    fout.write('#define %-25s %s\n' % (sPort, ss))



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

        _io_port_def(name, fout, 'DDR',  'DDR%s' % (port))  # define IO Port direction
        _io_port_def(name, fout, 'PORT', 'PORT%s'% (port))  # define IO Port output
        _io_port_def(name, fout, 'PIN',  'PIN%s' % (port))  # define IO Port input
        _io_port_def(name, fout, 'DESC', '"%s"'  % (desc))  # define IO Port description

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

        _io_pin_def(name, fout, 'DDR',    'DDR%s_DD%s%s'   % (port, port, bit))  # define IO direction
        _io_pin_def(name, fout, 'PORT',   'PORT%s_PORT%s%s'% (port, port, bit))  # define IO output
        _io_pin_def(name, fout, 'PIN',    'PIN%s_PIN%s%s'  % (port, port, bit))  # define IO input
        _io_pin_def(name, fout, 'MODE',   mode)                                  # define IO mode
        _io_pin_def(name, fout, 'INIT',   init_val)                              # define IO initial value
        _io_pin_def(name, fout, 'PIN_NO', pin)                                   # define IO pin number
        _io_pin_def(name, fout, 'DESC',   '"%s"'  % (desc))                      # define IO description

        fout.write('\n')

    else:
        # do nothing
        pass

fout.flush()
fout.close()
fin.close()
