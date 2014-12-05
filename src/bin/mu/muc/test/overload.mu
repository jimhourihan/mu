
module: overload {

    \: id (int a) { a; }
    \: id (float b) { b; }
    \: id (string c) { c; }

    \: closure ((void;); string a)
    {
        \: (void;) { print("a = %s\n" % a); };
    }

    \: closure ((void;); int a)
    {
        \: (void;) { print("a = %d\n" % a); };
    }
}
