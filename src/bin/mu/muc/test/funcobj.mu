
module: funcobj {

\: add_func ((int;int,int);)
{
    (int;int,int) F = (+);
    return F;
}

\: test (void;)
{
    print("%d should be 3\n" % add_func()(1,2));
    let F = add_func;
    print("%d should be 3\n" % F()(1,2));
    let G = \: (int; int a, int b) { a + b; };
    print("%d should be 4\n" % G(2,2));
}

}
