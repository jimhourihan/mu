#!/usr/bin/env python

import sys

IM = 139968
IA = 3877
IC = 29573

LAST = 42
def gen_random(max):
    global LAST
    LAST = (LAST * IA + IC) % IM
    return( (max * LAST) / IM )

def main(N):

    if N < 1:
        N = 1
    gr = gen_random
    for i in xrange(1,N):
        gr(100.0)
    print "%.9f" % gr(100.0)

main(1000000)
