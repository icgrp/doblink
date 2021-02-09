#!/usr/bin/python3
with open('dummy.v') as bla:
    for line in bla:
        string = ''
        for c in line:
            if c == '\t':
                string+='\\t'
            elif c != '\n':
                string+=c
        print('\'' + string + '\',')
