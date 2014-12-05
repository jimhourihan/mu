
char f = 'f', a = 'a', b = 'b', c = 'c';

assert( f + 1 == 'g' );
assert( f - 1 == 'e' );
assert( f - 'a' == 5 );

assert( a < f && a <= f && f <= f && f >= a && f >= f );
assert( a++ == 'a' ); 
a--;
assert( ++a == b ); 
a--;
assert( b-- == 'b' );
b++;
assert( --b == a);
