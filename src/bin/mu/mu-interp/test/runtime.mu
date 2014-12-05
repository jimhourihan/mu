
let pname = runtime.lookup_name("+");
assert(pname == "+");

(int;int,int) plus = runtime.lookup_function(pname);
assert(plus(1,2) == 3);
