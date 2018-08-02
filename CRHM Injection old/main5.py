#injection at function start
from data import newmodules as st

def found_any(st, prevline):
    for t in st:
        if prevline[0:len(t)] == t:
            return True

    return False

mdf2 = open('CRHMmain.cpp.mdf2')
mdf3 = open('CRHMmain.cpp.mdf3', 'w')

k = 1
prevline = ''
for line in mdf2:
    try:
        if line.strip() == '{':
            if found_any(st, prevline):
                #marking specified locations
                #print line
                #print '//raf835:injection'

                #injection
                x = line.strip()
                y = '//raf835:injection\n'
                z1 = 'freopen(\"d:\\\\injection.log\", \"a\", stdout);  '
                z2 = 'printf(\"newmodules sign# ' + str(k) + ' @ ' + prevline.strip() + '\\n\");  '
                z3 = 'fclose(stdout);\n'
                print x+y+z1+z2+z3
                mdf3.write(x+y+z1+z2+z3)

                k = k+1

            else:
                print line
                mdf3.write(line)

        else:
            print line
            mdf3.write(line)


    except:
        pass


    prevline = line
