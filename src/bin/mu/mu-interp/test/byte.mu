
byte b = 10;
int i = 123;
b = i;
b = b >> 1;
b = b | byte(2);
assert(b == byte(63));
