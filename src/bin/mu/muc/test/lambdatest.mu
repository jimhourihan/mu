
module: lambdatest
{
    \: dummy (int; int x)
    {
        print("called dummy with (%d)\n" % x);
        return x;
    }

    \: assignment (void; int x)
    {
        let d = dummy;
        print("d(x) = %d\n" % d(x));    // should not re-enter interpreted code
    }

    \: anon (void;)
    {
        (\: (void; int i) { print("%d\n" % i); })(321);
    }

    \: addEleven (int; int a)
    {
        \: G (int; int b) { a + b; }

        G(11);
    }

    \: partialMakeAddN (int N) 
    { 
        \: F (int a, int b) { a + b; }; 
        F(N,);
    }

    \: closureMakeAddN (int N) 
    { 
        \: (int a) { a + N; }; 
    }

    \: reduce_limits (void;)
    {
        use math_util;
        F := (int; int, int);

        \: e (int a, int b) { seed(a); random(b); }             // not pure
        \: f (int a, int b) { int(a + b + math.sin(a + b)); }   // pure
        \: g (F u, int x)   { u(u(x, u(x,1)),1); }              // maybe pure

        //
        // This should reduce to the constant 14 because g is maybe pure, f is
        // pure, and the rest in constant.
        //

        g(f, f(1,2) + f(2,1));  

        //
        //  This should never reduce because although e is constant it is not pure
        //  and since g is maybe pure it cannot be reduced.
        //

        g(e, f(1,2) + f(2,1));  // not reduce because e is not pure

        //
        //  Same exersize, but with non-primitive type
        //  

        S := (string; string, string);

        \: s (string a, string b) { b + a; }                    // pure
        \: np (string a, string b) { print(""); a; }            // not pure
        \: t (S u, string x) { u(u(x, u(x, "A")), "B"); }       // maybe pure

        t(s, s("E", "F") + s("G", "H"));    // reduce to constant "BAFEHGFEHG" 
        t(np, s("E", "F") + s("G", "H"));   // do not reduce
    }
}
