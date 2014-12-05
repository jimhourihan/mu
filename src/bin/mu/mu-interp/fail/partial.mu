

//module: suffix {
    //\: pi (void; float f) { math.pi * f; }
//}

// \: foo ()
// {
//     string suffix = "foo";
// }


\: foo (int;)
{
    add(1,)(2);
}

\: add (int; int a, int b) { a + b; }
