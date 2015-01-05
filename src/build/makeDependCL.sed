/#line/!d
s/^ *#line [0-9]* "//
s/" *$//
s,[Cc]:,/cygdrive/c,g
s,\\\\,/,g
s/ /\\ /g
s/$/ \\/
/^[^/]/d
