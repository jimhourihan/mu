
vec4 := vector float[4];
vec3 := vector float[3];
vec2 := vector float[2];

module: stringtest
{
    \: concat (string; string a, string b) { a + b; }
    \: concat (string; string a, string b, string c)
    {
        string s = string();
        s += a;
        s += b;
        s += c;
        return s;
    }

    \: primitiveConcat (string; string a, int b, float c, byte d, bool e)
    {
        a + " " + string(b) + " " + string(c) + " " + string(d) + " " + string(e);
    }

    \: vecConcat (string; vector float[2] a, vector float[3] b, vector float[4] c)
    {
        a + " " + b + " " + c;
    }

    \: equality (bool; string a, string b)
    {
        a == b && !(a != b);
    }

    \: chartype (void;)
    {
        print("char = %c\n" % (("foo")[1] + 1));
    }

    \: format_test (void;)
    {
        print("%s is not enough\n" % (vector float[4])(1, 2, 3, 5));
        print("%s is not false\n" % true);
        print("%d should be 10\n" % "0123456789".size());
    }

    \: split (void;)
    {
        print("%s\n" % string.split("one two three", " "));
    }

    \: substr (void;)
    {
        print("%s\n" % string.substr("one two three", 4, 3));
    }

    \: test (string;)
    {
        v2 := vector float[2];
        v3 := vector float[3];
        v4 := vector float[4];

        split();
        substr();

        let s = 
            concat(vecConcat(v2(1,2), v3(3,4,5), v4(6,7,8,9)),
                   " ",
                   primitiveConcat("a", 1, math.pi, 128, true));

        if (s != "foobar")
        {
            if (!(s == "foobar"))
            {
                if (s == s)
                {
                    return s;
                }
            }
        }

        return "not ok";
    }

}
