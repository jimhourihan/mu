
module: simpletest
{
  Vec2 := vector float[2];

    \: foo (float; float a, float b) { (math.sin(a) + math.cos(b)) / a; }

    \: bar (float;) { foo(1,2); }

    \: ack (int; int m, int n) 
    {
        if m == 0 then (n+1) else (if n == 0 then ack(m-1, 1) else ack(m-1, ack(m, n-1)));
    }

    \: looptest (void;)
    {
        for (int i=0; i < 10; i++)
        {
            print("%d " %  i);
        }

        print("\n");
    }

    \: vtest (Vec2;)
    {
        Vec2 x = Vec2(1,2);
        x = x + Vec2(3,4);
        return x;
    }

    // \: afunctest (int; int a, int b)
    // {
    //     return (\: (int; int x, int y) { x + y; })(a,b);
    // }

    \: nested (int; int a, int b)
    {
        \: add (int; int x, int y) { return x + y; }
        return add(a,b);
    }

    module: submodule
    {
        \: x (int; int a, int b) { a + b; }
    }

    \: voidFunc (void;)
    {
        let x = true;
        if (x) return;
    }
}
