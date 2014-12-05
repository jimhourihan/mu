require math;

module: tupletest
{
    \: foo (void; int i)
    {
        let t = ("bar", i, math.pi);
        print("%s %d %f\n" % t);
        t._2 *= 2.0;
        print("2 pi is %f\n" % t._2);
    }

    \: pattern (void;)
    {
        let (a, b, (c, d)) = (1, 2, (3, 4));
        print("a b c d = %d %d %d %d\n" % (a, b, c, d));
    }

    \: bar (void;)
    {
        print("%s %s %s %s\n" % ((1, "one"), 
                                 (2, "two"), 
                                 (3, "big", math.pi), 
                                 '\u0065'));

        print("%d %s %d %s %d %s %f %c\n" % (1, "one", 
                                 2, "two", 
                                 3, "big", math.pi, 
                                 '\u0065'));
    }

    \: baz ((float, float, float); float a)
    {
        (a, a*2, a*3);
    }

    \: test (void;)
    {
        int x = 1;
        foo(int(baz(x)._2));
        bar();
        pattern();
    }

}
