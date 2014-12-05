require autodoc;
require math;
require runtime;
require math_util;

function: shite (void;)
{
    int x = 1.0;
    print(x + "\n");
}

float[3,3,3] a;
vec := vector float[3];

try
{
    string sym = "float[3,3,3]";
    string doc = autodoc.document_symbol(sym, 0, autodoc.Text);

    print("Documentation for symbol: " + sym + "\n");
    print("\n");
    print(doc + "\n");
}
catch (exception exc)
{
    print("caught: ");
    print(exc);
    print("\n");
}
