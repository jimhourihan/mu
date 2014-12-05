
class: Foo { int i; string x; }

module: modinit {

    print("initializing modinit module\n");
    global Foo[] x = {{1, "one"}, {2, "two"}};
    print("here\n");
    global float pi = 3.14;
    global string name = "modinit name global";

    \: foo () { ; }
}
