
module: partial {

    \: foo (int; int a, string b, float c, (int,float) d)
    {
        print("%d, %s, %f, %s\n" % (a, b, c, d));
        let x = a, (y, _) = d;
        return x + y;
    }

    \: test (int;)
    {
        let add10 = foo(, "two", 3.14, (10, 9.87654321)); 
        return add10(113);
    }
}
