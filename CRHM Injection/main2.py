#shift all scope opening braces to the next line

mdf = open('CRHMmain.cpp.mdf')
mdf2 = open('CRHMmain.cpp.mdf2', 'w')

for line in mdf:

    try:
        if line.strip()[-1] == '{' and line.strip() != '{':
            x = line.strip()[:-1] + '\n'
            print x

            y = '{\n'
            print y

            mdf2.write(x + y)

        else:
            mdf2.write(line)
            print line

    except:
        pass
