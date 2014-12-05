module: vectest
{
    Vec3 := vector float[3];

    \: add (Vec3; Vec3 a, Vec3 b) { a + b; }
    \: sub (Vec3; Vec3 a, Vec3 b) { a - b; }
    \: times (Vec3; Vec3 a, Vec3 b) { a * b; }
    \: div (Vec3; Vec3 a, Vec3 b) { a / b; }

    \: foo (Vec3; Vec3 a, Vec3 b)
    {
        div(add(sub(b,a), times(a,b)), times(sub(a,b), b));
    }

    \: bar (float; Vec3 a, Vec3 b)
    {
        dot(cross(a,b), foo(a,b));
    }

    \: test (void;)
    {
        print("x = %f\n" % Vec3(3,2,1).x);
    }
}
