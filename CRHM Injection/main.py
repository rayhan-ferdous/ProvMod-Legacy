#remove all blank lines and comments

src = open('CRHMmain.cpp')
mdf = open('CRHMmain.cpp.mdf', 'w')

# modifying src
for line in src:
    if '//' in line:
        line = line[ : line.index('//')]+'\n'

    if len(line) == 1 and '\n' in line:
        pass
    else:
        print line[:-1]
        mdf.write(line)

