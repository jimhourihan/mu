
module: regextest
{
    \: test (void;)
    {
        let r = regex("(([0-9]{3})[-.])?([0-9]{3})[-.]([0-9]{4})");

        print("%s\n" % regex.smatch(r, "555-1234"));

        if (regex.match(r, "555-1234"))
        {
            print("ok\n");
        }
    }
}
