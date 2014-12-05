
module: methodtest {

    class: Base
    {
        method: foo (void;) { print("Base.foo\n"); }
        int x;
    }

    class: Derived : Base
    {
        method: foo (void;) { print("Derived.foo\n"); }
    }

    \: test ()
    {
        Base a = Derived();
        Base b = Base();
        a.foo();
        b.foo();
    }

}
