
operator: * (string; string s, int n)
{
    string ns = string(s);
    for (int i=1; i < n; i++) ns += s;
    ns;
}

assert( ("foo" * 4 + "\n") * 2 == "foofoofoofoo\nfoofoofoofoo\n");
