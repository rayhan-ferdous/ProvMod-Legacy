def remove_comments(infname, outfname):

    fin = open(infname)
    fout = open(outfname, 'w')

    for line in fin:
        if '//' in line:
            fout.write( line[ : line.index('//') ] + '\n' )
        else:
            fout.write(line)

def fn_start_inspect(infname):
    fin = open(infname)

    prev = ''
    for line in fin:
        if line == '{\n':
            print prev


        prev = line

def fn_inject(infname, outfname):

    fin = open(infname)
    fout = open(outfname, 'w')

    save = ''
    prev = ''
    for line in fin:
        print line

        if len(line.strip()) == 0:
            pass

        elif line.strip() == '{' and line[0] == '{':
            injection_msg = 'freopen(\"injection.xml", "a", stdout); printf("<' + '-'.join(prev.strip().split()) + '>\\n\"); fclose(stdout);'
            fout.write('{\n' + injection_msg + '\n')
            save = prev

        elif line.strip() == '}' and line[0] == '}':
            injection_msg = 'freopen(\"injection.xml", "a", stdout); printf("</' + '-'.join(save.strip().split()) + '>\\n\"); fclose(stdout);'
            fout.write(injection_msg + '\n' + '}\n')

        elif line.strip().split()[0][0:6] == 'return':
            injection_msg = '{' + 'freopen(\"injection.xml", "a", stdout); printf("</' + '-'.join(save.strip().split()) + '>\\n\"); fclose(stdout);' + line.strip() + '}'
            fout.write(injection_msg + '\n')

        else:
            fout.write(line)

        prev = line




def fn_inject_inspect(infname):
    fin = open(infname)

    for line in fin:
        if 'start_@ ' in line or 'end_@ ' in line:
            print line

