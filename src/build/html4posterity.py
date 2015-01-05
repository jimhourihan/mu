#!/usr/bin/python

import sys, re, string

MAGICRE   = re.compile(r".*(?P<label>magicparlabel-\d+).*")
TITLERE   = re.compile(r".*class='tocentry'>(?P<section>[0-9.]+\s)?(?P<title>[^<]+).*")
PRORE     = re.compile(r".*[^a-zA-Z]?PRO:")
CHAP1RE   = re.compile(r'^<h1 class="chapter_?">')
ENDBODYRE = re.compile(r'</body>')

#
#   PRORE:      replace "PRO" with <span class='pro'>PRO</span>
#   CHAP1RE:    put <div class='main'> around entire body of main text (but not TOC)

if __name__ == "__main__":
    trans = {}
    last = []
    addedMainDiv = False

    for line in sys.stdin:
        outLine = line
        m = MAGICRE.match(line)
        pro = PRORE.match(line)
        chap = CHAP1RE.match(line)
        bodyend = ENDBODYRE.match(line)
        if m and m.group('label') and m.group('label') in trans.keys():
            outLine = re.sub("magicparlabel-\d+",trans[m.group('label')],line)
        if "class='tocentry'" in line:
            label = m.group('label')
            t = TITLERE.match(line).groupdict()
            title = re.sub('[%s\s]' % re.escape(string.punctuation),"_",t['title'])
            level = 0
            if t['section']:
                level = t['section'].count(".")
            last = last[:level] + [title]
            final = "_".join(last)
            outLine = line.replace(label,final)
            if final in trans.values():
                print("ERROR: link title clash on '%s' from '%s'" % (final,line))
                sys.exit(1)
            trans[label] = final
        if pro:
            outLine = string.replace(outLine, "PRO:", "<span class='pro'>PRO</span>")
        if chap and not addedMainDiv:
            outLine = "<div class='main'>" + outLine
            addedMainDiv = True
        if bodyend and addedMainDiv:
            outLine = "</div>" + outLine

        sys.stdout.write(outLine)
