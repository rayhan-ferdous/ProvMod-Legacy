#inspect nature of all scopes' openings
# inspect the beginning pattern for target scopes

mdf2 = open('CRHMmain.cpp.mdf2')


note = open('note2.txt', 'w')

s = set()

prevline = ''
for line in mdf2:
    try:
        if line.strip() == '{':
            s.add(prevline.strip().split()[0])

            print prevline.strip()
            #print line.strip()
            print prevline.strip().split()[0]
            print '=== === ==='


    except:
        pass


    prevline = line

#preparing note for later use

sorted(s)

for token in s:
    note.write(token + '\n')
