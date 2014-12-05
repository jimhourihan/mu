

module: primitive
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
        if m == 0 then (n+1) else (if n == 0 then ack(m-1, 1) else ack(m-1, ack(m, n-1)));
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


    \: tak (float; float x, float y, float z)
    {
        if y >= x then z else tak(tak(x-1,y,z), tak(y-1,z,x), tak(z-1,x,y));
    }

    \: tak_test (float; float n)
    {
        tak(n * 3.0, n * 2.0, n * 1.0);
    }

    \: factorial (int; int x)
    {
        if x == 1 then 1 else x * factorial(x-1);
    }

    \: factorial_tail_recursive (int; int n)
    {
        \: iterate (int; int n, int acc)
        {
            if n <= 1 then acc else iterate(n-1, acc*n);
        }

        iterate(n, 1);
    }

    \: assert_test (void;)
    {
        assert(1 == 2);
    }

    \: harmonic_sum (float; float n)
    {
        float partialSum = 0;

        for (float i=1.0; i <= n; i++)
        {
            partialSum += 1.0 / i;
        }

        return partialSum;
    }
}
