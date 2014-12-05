

module: cpptest
{
    use math_util;
    use math;

    \: add (float; float a, float b) { a + b; }
    \: sub (float; float a, float b) { a - b; }
    \: times (float; float a, float b) { a * b; }
    \: div (float; float a, float b) { a / b; }

    \: foo (float; float a, float b) { add(times(a,b), div(a,b)); }

    \: bar (float; float a, float b, float c)
    { 
        sub(foo(a,b), foo(c,b));
    }
    
    \: utiltest (float; float a, float b, float c)
    {
        linstep(a, b, c) * smoothstep(b, a, c) * sin(a) * cos(a) * tan(a);
    }
    
    \: r (float; float s) { random(s); }

    \: ack (int; int m, int n) 
    {
        m == 0 ? (n+1) : (n == 0 ? ack(m-1, 1) : ack(m-1, ack(m, n-1)));
    }

    \: ack_long (int; int m, int n) 
    {
        if (m == 0)
        {
            return n + 1;
        }
        else
        {
            if (n == 0)
            { 
                return ack_long(m-1, 1);
            }
            else
            {
                return ack_long(m-1, ack_long(m, n-1));
            }
        }
    }


    \: tak (int; int x, int y, int z)
    {
        y >= x ? z : tak(tak(x-1,y,z), tak(y-1,z,x), tak(z-1,x,y));
    }

    \: factorial (int; int x)
    {
        x == 1 ? 1 : x * factorial(x-1);
    }

    \: factorial_tail_recursive (int; int n)
    {
        \: iterate (int; int n, int acc)
        {
            n <= 1 ? acc : iterate(n-1, acc*n);
        }

        iterate(n, 1);
    }
}
