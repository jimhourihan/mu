\: foo (void;)
{
    let list = [1,2,3];
    \: bar (void;) { for_each (l; list) print(l); }
    \: baz (void;) { bar(); }

    baz();
}

// should print "123"
foo();
