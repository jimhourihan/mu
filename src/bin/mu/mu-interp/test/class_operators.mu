
class: Foo
{
    operator: [] (int; Foo this, int index) { return n[index]; }
    operator: () (int; Foo this, int index) { return n[index]; }
    int[] n;
};

Foo f = {{1,2,3}};
assert(f[1] == 2);
assert(f(1) == 2);
