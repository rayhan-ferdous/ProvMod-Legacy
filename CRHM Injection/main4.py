#testing locations with specifier starting tokens

mdf2 = open('CRHMmain.cpp.mdf2')

testword = 'void __fastcall'

prevline = ''
for line in mdf2:
    try:
        if line.strip() == '{':
            if prevline[0:len(testword)] == testword:
                print prevline.strip()
                print line.strip()
                print '=== === ==='


    except:
        pass


    prevline = line
