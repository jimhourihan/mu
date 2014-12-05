
module: types {

    class: simple { int _int; }

    class: TestClass
    {
        class: Nested { int x; }

          STRING := string;

        int a;
        float b;
        string c;

        method: f (void;) { print("TESTCLASS\n"); }
    }

    //
    //  Make sure the name of this class causes its hash to preceed
    //  its super class's name
    //

    class: DerivedX : TestClass 
    {
        bool x;
        method: f (void;) { print("DERIVED\n"); }
    }

    union: Onion
    {
        class: Foo { int a; }

        PurpleOnion int |
        YellowOnion float |
        GreenOnion string |
        Monion Foo
    }

    union: Enumtest { Red | Green | Blue | Yellow | Magenta | White | Black }
}

//types.Onion.GreenOnion("foo");
