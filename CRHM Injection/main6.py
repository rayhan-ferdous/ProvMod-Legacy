# add watermark at the end of function scope

# base: all scope ending braces are lonely at their own line

mdf3 = open('CRHMmain.cpp.mdf3')
mdf4 = open('CRHMmain.cpp.mdf4', 'w')

score = 0
prevline = ''
watermark = ''


for line in mdf3:

    # print score
    mdf4.write(str(score) + ' >>>')

    if line.strip()[0] == '{':

        if '//raf835:injection' in line:

            watermark = prevline

            print line
            mdf4.write(line)

            score = score+1

        elif '//raf835:injection' not in line:
            print line
            mdf4.write(line)

            score = score + 1

        else:
            print '### problem ###'


    elif line.strip() == '}':


        if score > 0:

            mdf4.write(line)
            print line

            score = score-1

        elif score == 0:
            mdf4.write(line.strip() + '//raf835:end ' + watermark)
            print line.strip() + '//raf835:end ' + watermark

        else:
            print '### problem ###'


    else:
        mdf4.write(line)
        print line











    prevline = line