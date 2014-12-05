module: list {

    \: allbut2 ([int]; [int] l)
    {
        let a : b : t = l;
        return t;
    }

    \: test (void;)
    {   
        let x = [1,2,3,4];
        print("allbut2 [1,2,3,4] = %s\n" % allbut2(x));
    }
}
