use test;

base_class base = a_class("BASE");
a_class a = base;

try
{
    b_class b = base;
}
catch (exception exc)
{
    print("CAUGHT: " + string(exc) + "\n");
}
