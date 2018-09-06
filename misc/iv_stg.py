#!/usr/bin/env python2

from collections import defaultdict
import stringtemplate3
import iv
import sys

STG = None

new = lambda inst: STG.getInstanceOf(inst)

def initialize_stg(stgfile='iv.st'):
    ''' Load the STG backend and set gobal STG pointer '''
    global STG

    # Load the file containing a group of templates
    STG = stringtemplate3.StringTemplateGroup(file=open(stgfile))

initialize_stg()

tpl = new("interface_view")

#tpl['arrsFunctNames'] = iv.functions.keys()
# all parameters in argv will be filted out
tpl['arrsThreadNames'] = [fName for fName in iv.functions.keys()
                         if fName.lower() not in sys.argv[1:] and
                         iv.functions[fName]['runtime_nature'] == iv.thread]

tpl['arrsPassiveNames'] = [fName for fName in iv.functions.keys()
                          if fName.lower() not in sys.argv[1:] and
                          iv.functions[fName]['runtime_nature'] != iv.thread]

connections = []  #  type: List[str]
for fromName, content in iv.functions.viewitems():
    group = defaultdict(list)

    if fromName in sys.argv[1:]:
        continue

    for iName, iContent in content['interfaces'].viewitems():
        if iContent['direction'] == iv.RI:
            if iName.lower() == content['interfaces'][iName]['distant_name']:
                text = iName
            else:
                text = '{} -> {}'.format(iName,
                                  content['interfaces'][iName]['distant_name'])
            group[iContent['distant_fv']].append(text)
    for destName, destContent in group.viewitems():
        if destName in sys.argv[1:]:
            continue
        tplConn                 = new("connection")
        tplConn['sFrom']        = fromName
        tplConn['sTo']          = destName
        tplConn['arrsMessages'] = destContent

        connections.append(str(tplConn))

tpl['arrsConnections'] = connections

print str(tpl).encode('latin1')
