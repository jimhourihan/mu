
//
//  Short func form
//

\: sum (float; float a, float b) { a + b; }
\: (float; float a, float b) { a + b; }
\: ($T; $T a, $T b) { \. a + b; }
\: nmap (void; $T a, $Q b, int n) { repeat(n) a(b); }

//
//  function 
//

function: sum (float; float a, float b) { a + b; }
function: (float; float a, float b) { a + b; }

\: (float; float a, float b) a + b
\: (;float a, float b) a + b

Foo[] foo_array;
map(foo_array, $1.bar());   // $ syntax would be really nice as lambda expr
map(foo_array, \: (Foo; Foo f) { f.bar(); })


//
//  Should it be more like ML or Haskel?
//

\: sum (float; float a, float b) { a + b; }

\: car (; a) { a[0]; }
\: cdr (; a) { a[1:];  }        // [1,size)

//
//  This brings up the point that some basic type inferencing should
//  be acceptable. For example, the sum function above should not
//  require the retun type since it can be inferred:

\: sum (; float a, float b) { a + b; } // inferred float return type

//
//  Template
//
//  "$" indicates that the following identifier is a "type-variable" a
//  variable whose value is a type. The identifier may appear multiple
//  times.
//
//  There is special syntax for arrays and lists:
//
//  $T[n] is a fixed size array of some type.
//  $T[] is a dynamic array of some type
//  $T[n,m] fixed 2-d array
//

//typeless? matches whatever it can?

\: sum (; a, b) { a + b; }

\: sum ($T[n]; $T[n] a, $T[n] b) 
{ 
    $T[n] c; 
    for (int i; i < n; i++) c[i] = a[i] + b[i];
    c;
}

\: sum ($T; $T a, $T b) { a + b; }

\: sum (float; float a, float b) { a + b; }

// tick syntax? (I guess its just like dollar) is this what ML does?  need
// to fix mu-mode.el font-lock for "'" if this is the case (how do you do
// that anyway?)

\: sum ('t[]; 't[] a, 't[] b)
{
    't[] c;
    for (int i; i < n; i++) c[i] = a[i] + b[i];
    c;
}

//
//  rewriting
//  (this syntax seems ill thought-out)
//

rule: (variable int index, int start, int end, block b)
{
    for (index = start; index < end; index++) b => 
    index_loop (index; start, end) b;
}

//
//  Meta module and templates/rewriting?
//

rule: (type A, type B, function C)
{
    \: C (A; B b);

        =>

    \: (A[]; B[] bseq) 
    {
        A[] out;
        for_each (b, bseq) { out.push_back(C(b)); }
        out;
    }
}


macro: for_each (mu.assembler as)
{
    require mu;
    mu.context parse_context, output_context;
    mu.assembler as;

    parse_context.expect("(");

    let loopvar = parse_context.identifier();

    parse_context.expect(";");

    let collection_expr = parse_context.expression();

    collection_type t = context_expr.type(); // dynamic cast will throw

    as.push_anonymous_scope();
    as.declare_stack_variable(loopvar, t);

    parse.expect(")", "{");

    let block = parse.statement_list();

    parse.expect("}");
}

//
//  IO STREAMS
//

io.out << format("My name is \"%s\" and I'm %d years old.\n", "jim", 6)
       << io.endl;

io.out.write() // of each type
io.out.write(float) // of each type
io.out.write(int) // of each type


//
//  lists using typemodifier for lists makes it pretty
//  straightforward, but then (like vector) there are problems
//  indicating more complex types (like a list of vectors?)
//

let numbers = [1, 2, 3, 4];
let morenumbers = 0 : numbers;

// see also section on s-expr

//
//  [] could mean "sequence" so that it also applies to lists and
//  sets. There would be a special cookie syntax for making lists or
//  hash tables?
//

string_list = [string];

[string][2] string_list = {{"a", "b"}, {}}

int[string] string_to_int_map = {"foo" : 10,
                                 "bar" : 20};
list int string_list

hash int[string] hashed_map;

sort(array, (>))

let x = [1, 2, 3, 4];


//
//  foreach
//

for_each (i; array) print(i + "\n");

for (i; array) print(i + "\n");

//
//  repeat
//

repeat (int i = 1; 10) print(i + "\n");
repeat (float i = 1; 10; .1) print(i + "\n");

//
//  iterator type?
//

iterator float[] i = array.begin();

for (iterator float i = array.begin(); i != array.end(); ++i)
{
    i = 1.0;
}

iterate (i; array) print(i + "\n");


//
//   let -- implicit declaration
//

let x = 5;  // x => int

let x = myFunction(); // x => function return type
let x = y;            // x => y's type

//
//  Continuations ala scheme
//
//  call_cc is a strange type of template function that always returns
//  the same type as the function is calls. 
//

global continuation gk = nil;

\: cfunc (int; continuation k) { k(48); }
\: dfunc (int; continuation k) { cfunc(k) + 10; }

assert( call_cc(cfunc) == call_cc(dfunc) );

//
//  Special form that just gets the current continuaion
//

continuation k = call_cc();

// or simply

continuation k;

//  if implemented using threads,  



//
//  Tuples
//
//  Definitely need tuples. The definition should be like ML: a fixed
//  "array" of any types. There will need to be a special syntax to
//  declare them.
//
    
tuple_type := (string, int);

tuple_type goo = {"hello", 10};  // tuple
// or
let goo = ("hello", 10);

// use comma (tuple) expression
// comma operator cons' up a tuple type
// type syntax just like usage

let x = (1, 2, 3);  // type is (int, int, int)

// assignment w/pattern

let (a, b, c) = (1, 2, 3);

//
//  Other -- counting for

for (int i; 1, 10)


//
//  Function type syntax
//

takes_two_floats := (float; float);

takes_a_float := (float; float);
takes_a_float foo = sin;
assert( foo(1.0) == sin(1.0) );

//
//  Partial evaluation / explicit closures
//

\: add (int; int a, int b) { a + b; };

let add1 = addN(1,),
    add2 = addN(2,);

-or-

let add1 = addN(1,_),
           addN(2,_);

assert(add1(2) == 3 && add2(2) == 4);

//
//  argument rearrangement?
//

\: foo (void; int a, string b) { ... }

foo($2,$1); // => \: (void; string a, int b) { foo(b,a); }

//
//  Should the empty argument syntax be a closure or force partial
//  eval? It seems like creating the closure is the first step in
//  partial eval, so perhaps it should always occur.
//
//  maybe an "eval" keyword
//

addN(1,)

//
//  Problem: how do you distinguish between a "closure" type operation
//  and an actual partial evaluation -- or is that even necessary?
//  Also, how do you do partial eval on a function with one argument?
//  Since there are no commas in the syntax, its ambiguous. This of
//  course makes no difference unless the function you're calling is
//  not mapped.
//

//
//  Here's a useful example:
//

\: baked_seed_random (float; float s) { math.seed(s); math.random(); }

(void;float) my_rand       = reduce(baked_seed_random, 1.0);
(void;float) my_other_rand = apply(baked_seed_random, 2.0);

let x = \: baked_seed_random (1.0)


// Symbol quoting?

serialize(stream, obj);
deserialize(stream, #type);

//
//  ML isms. Type constraints
//

//  Type is ('a; 'a)
\: ident (x) { x; }


// Type is ('r; 'a, 'b)
\: add (a, b) { a + b }

// 
//  With named return value
//

\: add ('a[] n; 'a[] a, 'a b) 
{ 
    for_each (x; a) n.push_back(x + b); 
}

//
//  Symbol quoting

let x = dynamic_cast(#float, int)

//
//  Recursive types. this is reserved already. I don't think it will
//  be ambiguous to use in a type declaration as well as as a
//  variable.
//

FuncThatTakesItselfType     := (void; this);
FuncThatReturnsItselfType   := (this;);

//
//  constructs (lighting loop in dusty)
//

illuminance (L; true)
{
    color += L;
}

//
//  Get a function object out of an operator
//

let x = (+);

//
//  Better polymorphism with type classes
//

struct: Foo (Num a, Array b, Num c)
{
    a number;
    b arrayOfStuff;
    c anotherNumber;
}

Bar := Foo(float,string[],int);

Bar(3.14, string[] {"a", "b"}, 123);

\: add (Num 'a; Num 'a a, Num 'a b) { a + b; };

\: add (Num B; Num A a, A b) { a + b; };

//
//  type categories (type classes) constraint types?
//
//  'a through 'z are predefined as identity
//
//  Some new operators:
//
//      >   --> is a super set of (includes)
//      <   --> is a sub set of   (member of)
//      ==  --> matches
//
//  also need:
//
//      function == type
//      nil == type
//      function 
//  
//  type catagory expressions are basically functions which take a
//  type as input and return a boolean.  perhaps the 'symbol is
//  nothing special, it just a way to identify a type class pattern.
//

type: BinaryRelation = (bool; 'a, 'a);
type: BinaryOperator = ('a; 'a, 'a);


\: exists (bool; (;) f) { f != nil; }
\: commutative (bool; (;) f) { property(f, "commutative"); }

type: Eq ('a) = exists(BinaryRelation((==)));

type: Ord ('a) = Eq('a) &&
    exists(BinaryRelation((>)) &&
           exists(BinaryRelation((<))) &&
           exists(BinaryRelation((>=))) &&
           exists(BinaryRelation((<=)));
           
type: Number ('a) = Ord('a) &&
                    exists(BinaryOperator((+)) &&
                    exists(BinaryOperator((-))) &&
                    exists(BinaryOperator((*))) &&
                    exists(BinaryOperator((/))) &&
                    commutative(BinaryOperator((+))) &&
                    !commutative(BinaryOperator((-))) &&
                    commutative(BinaryOperator((*))) &&
                    !commutative(BinaryOperator((/)));

\: min (Ord a, Ord b) { a < b ? a : b; }

//
//  Definition of the type pattern expression operators
//



//
//  Ignoring arguments (automatically)
//

\: add (int; int a, int b) { a + b; }

Add3Func := (int;int,int,int);

\: takes_a_func (void; Add3Func func)
{
    // blah
}

takes_a_func(add); // this can be ok because add can be made into this:

\: add_with_ignored_argument (int; int a, int b, int c)
{
    add(a, b);
}

//
//  slice notation

slice a = 1:10; // [1,10]
slice b = 1::2; // [1,size) by 2
slice c = 1:10:2; // [1,10] by 2
slice d = :10; // [0,10]

slice a = 1..10         // probably better [1,9])
slice b = 1..10..2       // probably better

slice foo = bar["one".."ten"]


//
//  Get rid of relational operators and make them all relative to
//  compare() function
//

operator: <  (bool; 'a a, 'a b) { compare(a,b) <  0; }
operator: <= (bool; 'a a, 'a b) { compare(a,b) <= 0; }
operator: >  (bool; 'a a, 'a b) { compare(a,b) >  0; }
operator: >= (bool; 'a a, 'a b) { compare(a,b) >= 0; }
operator: == (bool; 'a a, 'a b) { compare(a,b) == 0; }
operator: != (bool; 'a a, 'a b) { compare(a,b) != 0; }

//
//  simple class
//

class: Point
{
    float x;
    float y;
    float z;

    method: Point (Point; float a, float b, float c) { x=a; y=b; z=c; }
}

Point p = Point.new()

//
//  interface
//

interface: Thingable
{
    function: flooper (int; string a) { int(a); }
}

Thingable foo = bar;

//
//  All classes can have type expressions in them. So they're somewhat
//  like a function.
//

class: map ('key_type, 'value_type)
{
    'key_type    key;
    'value_type  value;
    this         left;
    this         right;

    method: find ('value_type; 'key_type k)
    {
        if (key == k) return value;
        else if (k < key && left != nil) return left.find(k);
        else if (right != nil) return right.find(k);
    }

    method: insert (void; 'key_type k, 'value_type v)
    {
        if (k == key) 
        {
            value = v;
        }
        else if (k < key)
        {
            if (left)
            {
                left.insert(k, v);
            }
            else
            {
                left = map(k, v)
            }
        }
        else if (right)
        {
            right.insert(k, v);
        }
        else
        {
            right = map(k, v);
        }
    }
}

map x = {"feb", 2, {"jan", 1}, {"march", 3}};
               

//
//  Type patterns.  Patten matching is depth first. 'N and 'M have
//  type "size" or something. The first type pattern determines the
//  meanings of the type/index variables.
//

Matrix   := 'a[#'N,#'M];
VectorN  := 'a[#N];
VectorM  := 'a[#M];

operator: * (VectorN; Matrix m, VectorM a)
{
    VectorN b;

    for_index (i, j; m)
    {
        b[i] += dot(m[i::'N], a);
    }

    b;
}

//
//  Let's say I have x of type (float;float) and y of type
//  (float;float,float) and I want z == y(x(_1),_2).
//  This example is a bit simpler with closures.
//

F1 := (float;float);
F2 := (float;float,float);

// with closures

\: compose (F1 a, F2 b)
{
    \: (float x, float y) { b(a(x),y); }
}


//
//  Constant suffix functions
//

1f -> 1.0       \: f (float; int x) { float(x); }
1.0i            \: i (complex; float x) { complex(0.0, x); }
1.0 + 1.0i
"f.+"r          \: R (regex; string s) { regex(s); }

1.0 + 1i + 2k + 3j

cross(N, 1y);

//
//  Variable attributes
//

float output x = 10.0;

//
//  Additional require parameters
//

require extra_stuff from "."

//
//  Character constant
//

let foo = 'a';


//
//  sparse?
//

sparse float[,] x;
sparse float[];
sparse float[1000,1000];
sparse float[100000];

//
//  Array (List?) Sugar?
//

let x = ["foo", "bar"];
x => string[]


//
//  Macros again. Some syntax stolen from metamorphic macros. The
//  implementation of those looks pretty cool, but 
//
//  These special types #type could be implemented as classes in
//  mu. These are "parts of speech" in the grammar (nonterminals) and
//  cause parser invocation for their part. The result is assigned to
//  the variable.
//
//  The # operator would generate a symbol.  all of the internal Mu
//  symbols and their hierarchy would need to be reflected in mu
//  itself for this to work.
//

syntax: #float pi ::= 3.141529

syntax: #stmt for_index (#id<ID> ; #expr<seq>) #stmt<S> ::=
{
    use mu;
    push_scope();       // anonymous
    declare(#int, ID),

    let e = call("__simple_block",
                 call("__for",
                      call("=", ID, 0),
                      call("<", ID, call("size", seq)),
                      call("_++", "i"),
                      S));

    pop_scope();
    e;
}


//
//  symbolic expressions ala lisp. The difference being they are
//  staticially typed. This could make macros much easier to grok.
//  This would be an overloading of the list syntactic sugar if it
//  coexisted with the list syntax
//

let x  = 1.0,
    e0 = [namespace, "foo", 
          [let, symbol("a"), x],
          [atan, [cos, [sin, 1.0]], reference("a")];
           

//
//  cond ala lisp? This could be created in Mu itself if lazy
//  evaluation were available:
//

function: cond ('a; 
                lazy bool test1, lazy 'a expr1, 
                lazy bool test2, lazy 'a expr2, 
                lazy 'a expr3)
{
    //
    //  If you write it like this instead of using cond it is lazy!
    //

    test1 ? expr1 : (test2 ? expr2 : expr3);
}

let y = cond(x > 1.0, sin(x),
             x < 1.0, cos(x),
             atan(x));

//
//  All of this can be achieved through a function called memoize()
//  which somehow builds a lambda expression with caching built
//  in. The parser could just substitute memoize(expr) in place of
//  expr at the point where the call occurs.
//

foo(memoize(expensive()), 1.0);

//
//  Parameterized types. One way to do this is with a type modifier,
//  however, that is very limited.
//
//  Type construction call is parameterized_type '(' type, ... ')'
//

quatf := quaternion(float);

//
//  provide instead of empty modules?
//

provide foo;

//
//  Guards?
//  Seems over the top. Just use case expression/statement instead
//
          ));


\: fact (int; int a) => case a of
           (0      -> 1;
            a > 0  -> a * fact(a-1));
           
//
//  conditional expression
//

let x = if foo > bar then 10 else 20;

//
//  Stolen from python: triple quote
//

""" 
foo bar 
is the foest of the bar 'foo' is the bar
"""

let Num      'a,
    Num[4,4] 'M,
    Ord      'c;
    

function: add ('a; 'a x, 'a y) { x + y; }

//
//  Haskellesque
//

Vec := vector float[3];
type Vec = vector float[3];

datatype A (Num a, Ord b)
{
    a[] array;
    a thing;
    (a,b) foo;
};

typeclass Group
{
    operator: + (Group; Group, Group);
}

typeclass Ring : Group
{
    operator: * (Ring; Ring, Ring);
}


//
//  Enum
//

union: Weekday { Monday | Tuesday | Wednesday | Thursday | Friday } 

//
//  Tree
//

union: Tree { Leaf int | Node (Tree,Tree,int) }

//
//  Need the -> keyword because we're using '{' '}' in patterns as well.
//  If no keyword, its ambiguous what a pattern is versus an action.
//

\: succ (Weekday; Weekday day)
{
    case (day)
    {
        Monday -> { return Tuesday; }
        Tuesday -> { return Wednesday; }
        Wednesday -> { return Thursday; }
        Thursday  -> { return Friday; }
        Friday -> { return Saturday; }
        Saturday -> { return Sunday; }
        Sunday -> { return Monday; }
    }
}


case (tree)
{
    Tree.Node (left, right, mid)
    {
        left + right + mid;
    }
    
    Tree.Leaf (value)
    {
        print("value = %d\n" % value);
    }

    default
    {
        print("bad");
    }
}

let q = 1 + case tree of
                Node (foo, bar) => 1 
                Leaf val => 2 ;
    
//
//  Pattern match
//

}}

let x = case tree of (Node (l, r, m) -> 1 ; Leaf v -> 2)

let z = let x = 10, y = 50, z = 100 
        in x + y + z ;

let (x, y, z) = (1, 2, 3), w = 10;
let ((x,,),) = ((1,2,3), 4);
let ((x,_,_),_) = ((1,2,3),4);

for_each ((name, value); nameValuePairs)
{
}


//
//  Alternative syntax for "messages"
//

Foo a;
let foo = ;

//
//  extended case statement/expression. Allow matching strings against
//  regex perhaps the rule is: "anything that can be matched using a
//  match function?"
//
//  Add a match operator?
//

string foo;

case (foo)
{
    "bar"    -> print("*foo == bar\n"); 
    "f.+" r  -> print("foo matches f.+\n"); 
    _        -> whatever; 
}

let x = case foo of 
    "bar" -> 1,
    "f.+"r -> 2;

int a;

case (a)
{
    1 -> one;
    2 -> two;
    8 -> eight;
    _ -> other;
}

//
//  addressing evaluation at parse and compile time
//

when_parsing
{
    // use mu.parser implicit

    if (system.system2("date") == "tues")
    {
        load_module("tuesday_module");
    }
    else
    {
        load_module("not_tuesday_module");
    }

    set_function_attributes(Pure);
}

when_compiling
{
    // use mu.compiler implicit
    inline(regex("doSomething.*"));
}

when_compiling("muc")   // if there are multiple compilers this addreses the named one
{
}


//
//  OO functions
//

//
//  Classes
//  The OO needs to be syntactic sugar (like obj-c is syntactic sugar on C)
//

mu.name funcName = mu.name("Class.someFunction");
mu.name sig      = mu.name("(void;int,int)");

".*"r

(void;int,int) F = mu.function(funcName, sig);
(void;int,int) F = mu.method(funcName, sig);

//  This makes for the 


//
//  OBJ-c interface. Messages are juxtaposed with colons at ends of keywords
//  if this can be seemless integrated into the syntax, that would make Cocoa
//  much easier.
//

// [foo blah with: blablah]


//
//  New Function Type syntax:
//

BinaryOp = int, int -> int;
BiggerOp = (int,int -> int), float -> bool;

\: add ('a a, 'a b -> 'a)
{
}


\: foo ('a a -> 'c) 'c(a);

float x = foo<float>(1)


//
//  Blocks, closures, automatic parameters
//

//
// NOTE: '1 is a parameter placeholder variable (slot)
// (aka placeholders in the lambda boost library)
// This syntax allows for both economical lambda expression creation
// (similar to boost, but generalized) as well as a mechanism to generalize
// currying with parameter reordering (not just partial application/evaluation 
// of a particular slot)

foo( \: sin(x) );                 // expression closure
foo( \: sin('1) );                // expression automatic parameter
foo( \: (float x) { sin(x); } );  // expression with formal parameter
foo( \: { sin(x); print(x); } );  // block closure

foo( sin('1) );                   // implicit automatic closure

// permutting curry

foo(int a, int b);

let swappedFoo = foo('2, '1);

let result = zip(array0, array1, sin('1) + cos(1.0 - '2));
let result = map(array, (sin('1) + cos(0)) / 2.0);

//
//  System F with dependant types
//
//  Note that this is not OVERLOADING which is accomplished using
//  similar syntax.
//

\: TupleN ('a, int n)
{
    if n <= 0 then 'a else 'a * TupleN('a, n-1);
}

// (*;*,int) => TupleN

(*;int) IntTuple = TupleN(int, '1);

(*;*) TripleTuple = TupleN('1, 3);

TripleTuple(int) i = (1,2,3);

\: Int () { 'int; }


//
//  autoload
//

autoload: wipes construct (Widget; string);

//  becomes:

module: wipes
{
    global (Widget; string) __autoload_construct = \: (Widget; string name)
    {
        runtime.load_module("wipes");
        let Fname = runtime.intern_name("wipes.construct");
        (Widget;string) F = runtime.lookup_function(Fname);
        __autoload_construct = F;
        F(name);
    }
}

// and add instantiation point:

wipes.construct("foo")

// this is generated:

wipes.__autoload_construct("foo")

// so that the first time it loads the module and subsequent times it
// goes through a thunk to the actual function.


//
//  Structural types. These would be supertypes to all nominal types
//  (like class or struct). Anyplace a structural type is accepted a
//  compatible nominal type may be used (since its a subtype)
//

struct: Nominal { int a; int b; }
{int a, int b} x = Nominal(1,2);    // ok ==> {int a,int b} :> Nominal

//

//
//  Short func form
//

\: sum (float; float a, float b) { a + b; }
\: (float; float a, float b) { a + b; }
\: ($T; $T a, $T b) { \. a + b; }
\: nmap (void; $T a, $Q b, int n) { repeat(n) a(b); }

//
//  function 
//

function: sum (float; float a, float b) { a + b; }
function: (float; float a, float b) { a + b; }

\: (float; float a, float b) a + b
\: (;float a, float b) a + b

Foo[] foo_array;
map(foo_array, $1.bar());   // $ syntax would be really nice as lambda expr
map(foo_array, \: (Foo; Foo f) { f.bar(); })


//
//  Should it be more like ML or Haskel?
//

\: sum (float; float a, float b) { a + b; }

\: car (; a) { a[0]; }
\: cdr (; a) { a[1:];  }        // [1,size)

//
//  This brings up the point that some basic type inferencing should
//  be acceptable. For example, the sum function above should not
//  require the retun type since it can be inferred:

\: sum (; float a, float b) { a + b; } // inferred float return type

//
//  Template
//
//  "$" indicates that the following identifier is a "type-variable" a
//  variable whose value is a type. The identifier may appear multiple
//  times.
//
//  There is special syntax for arrays and lists:
//
//  $T[n] is a fixed size array of some type.
//  $T[] is a dynamic array of some type
//  $T[n,m] fixed 2-d array
//

//typeless? matches whatever it can?

\: sum (; a, b) { a + b; }

\: sum ($T[n]; $T[n] a, $T[n] b) 
{ 
    $T[n] c; 
    for (int i; i < n; i++) c[i] = a[i] + b[i];
    c;
}

\: sum ($T; $T a, $T b) { a + b; }

\: sum (float; float a, float b) { a + b; }

// tick syntax? (I guess its just like dollar) is this what ML does?  need
// to fix mu-mode.el font-lock for "'" if this is the case (how do you do
// that anyway?)

\: sum ('t[]; 't[] a, 't[] b)
{
    't[] c;
    for (int i; i < n; i++) c[i] = a[i] + b[i];
    c;
}

//
//  rewriting
//  (this syntax seems ill thought-out)
//

rule: (variable int index, int start, int end, block b)
{
    for (index = start; index < end; index++) b => 
    index_loop (index; start, end) b;
}

//
//  Meta module and templates/rewriting?
//

rule: (type A, type B, function C)
{
    \: C (A; B b);

        =>

    \: (A[]; B[] bseq) 
    {
        A[] out;
        for_each (b, bseq) { out.push_back(C(b)); }
        out;
    }
}


macro: for_each (mu.assembler as)
{
    require mu;
    mu.context parse_context, output_context;
    mu.assembler as;

    parse_context.expect("(");

    let loopvar = parse_context.identifier();

    parse_context.expect(";");

    let collection_expr = parse_context.expression();

    collection_type t = context_expr.type(); // dynamic cast will throw

    as.push_anonymous_scope();
    as.declare_stack_variable(loopvar, t);

    parse.expect(")", "{");

    let block = parse.statement_list();

    parse.expect("}");
}

//
//  IO STREAMS
//

io.out << format("My name is \"%s\" and I'm %d years old.\n", "jim", 6)
       << io.endl;

io.out.write() // of each type
io.out.write(float) // of each type
io.out.write(int) // of each type


//
//  lists using typemodifier for lists makes it pretty
//  straightforward, but then (like vector) there are problems
//  indicating more complex types (like a list of vectors?)
//

let numbers = [1, 2, 3, 4];
let morenumbers = 0 : numbers;

// see also section on s-expr

//
//  [] could mean "sequence" so that it also applies to lists and
//  sets. There would be a special cookie syntax for making lists or
//  hash tables?
//

string_list = [string];

[string][2] string_list = {{"a", "b"}, {}}

int[string] string_to_int_map = {"foo" : 10,
                                 "bar" : 20};
list int string_list

hash int[string] hashed_map;

sort(array, (>))

let x = [1, 2, 3, 4];


//
//  foreach
//

for_each (i; array) print(i + "\n");

for (i; array) print(i + "\n");

//
//  repeat
//

repeat (int i = 1; 10) print(i + "\n");
repeat (float i = 1; 10; .1) print(i + "\n");

//
//  iterator type?
//

iterator float[] i = array.begin();

for (iterator float i = array.begin(); i != array.end(); ++i)
{
    i = 1.0;
}

iterate (i; array) print(i + "\n");


//
//   let -- implicit declaration
//

let x = 5;  // x => int

let x = myFunction(); // x => function return type
let x = y;            // x => y's type

//
//  Continuations ala scheme
//
//  call_cc is a strange type of template function that always returns
//  the same type as the function is calls. 
//

global continuation gk = nil;

\: cfunc (int; continuation k) { k(48); }
\: dfunc (int; continuation k) { cfunc(k) + 10; }

assert( call_cc(cfunc) == call_cc(dfunc) );

//
//  Special form that just gets the current continuaion
//

continuation k = call_cc();

// or simply

continuation k;

//  if implemented using threads,  



//
//  Tuples
//
//  Definitely need tuples. The definition should be like ML: a fixed
//  "array" of any types. There will need to be a special syntax to
//  declare them.
//
    
tuple_type := (string, int);

tuple_type goo = {"hello", 10};  // tuple
// or
let goo = ("hello", 10);

// use comma (tuple) expression
// comma operator cons' up a tuple type
// type syntax just like usage

let x = (1, 2, 3);  // type is (int, int, int)

// assignment w/pattern

let (a, b, c) = (1, 2, 3);

//
//  Other -- counting for

for (int i; 1, 10)


//
//  Function type syntax
//

takes_two_floats := (float; float);

takes_a_float := (float; float);
takes_a_float foo = sin;
assert( foo(1.0) == sin(1.0) );

//
//  Partial evaluation / explicit closures
//

\: add (int; int a, int b) { a + b; };

let add1 = addN(1,),
    add2 = addN(2,);

-or-

let add1 = addN(1,_),
           addN(2,_);

assert(add1(2) == 3 && add2(2) == 4);

//
//  argument rearrangement?
//

\: foo (void; int a, string b) { ... }

foo($2,$1); // => \: (void; string a, int b) { foo(b,a); }

//
//  Should the empty argument syntax be a closure or force partial
//  eval? It seems like creating the closure is the first step in
//  partial eval, so perhaps it should always occur.
//
//  maybe an "eval" keyword
//

addN(1,)

//
//  Problem: how do you distinguish between a "closure" type operation
//  and an actual partial evaluation -- or is that even necessary?
//  Also, how do you do partial eval on a function with one argument?
//  Since there are no commas in the syntax, its ambiguous. This of
//  course makes no difference unless the function you're calling is
//  not mapped.
//

//
//  Here's a useful example:
//

\: baked_seed_random (float; float s) { math.seed(s); math.random(); }

(void;float) my_rand       = reduce(baked_seed_random, 1.0);
(void;float) my_other_rand = apply(baked_seed_random, 2.0);

let x = \: baked_seed_random (1.0)


// Symbol quoting?

serialize(stream, obj);
deserialize(stream, #type);

//
//  ML isms. Type constraints
//

//  Type is ('a; 'a)
\: ident (x) { x; }


// Type is ('r; 'a, 'b)
\: add (a, b) { a + b }

// 
//  With named return value
//

\: add ('a[] n; 'a[] a, 'a b) 
{ 
    for_each (x; a) n.push_back(x + b); 
}

//
//  Symbol quoting

let x = dynamic_cast(#float, int)

//
//  Recursive types. this is reserved already. I don't think it will
//  be ambiguous to use in a type declaration as well as as a
//  variable.
//

FuncThatTakesItselfType     := (void; this);
FuncThatReturnsItselfType   := (this;);

//
//  constructs (lighting loop in dusty)
//

illuminance (L; true)
{
    color += L;
}

//
//  Get a function object out of an operator
//

let x = (+);

//
//  Better polymorphism with type classes
//

struct: Foo (Num a, Array b, Num c)
{
    a number;
    b arrayOfStuff;
    c anotherNumber;
}

Bar := Foo(float,string[],int);

Bar(3.14, string[] {"a", "b"}, 123);

\: add (Num 'a; Num 'a a, Num 'a b) { a + b; };

\: add (Num B; Num A a, A b) { a + b; };

//
//  type categories (type classes) constraint types?
//
//  'a through 'z are predefined as identity
//
//  Some new operators:
//
//      >   --> is a super set of (includes)
//      <   --> is a sub set of   (member of)
//      ==  --> matches
//
//  also need:
//
//      function == type
//      nil == type
//      function 
//  
//  type catagory expressions are basically functions which take a
//  type as input and return a boolean.  perhaps the 'symbol is
//  nothing special, it just a way to identify a type class pattern.
//

type: BinaryRelation = (bool; 'a, 'a);
type: BinaryOperator = ('a; 'a, 'a);


\: exists (bool; (;) f) { f != nil; }
\: commutative (bool; (;) f) { property(f, "commutative"); }

type: Eq ('a) = exists(BinaryRelation((==)));

type: Ord ('a) = Eq('a) &&
    exists(BinaryRelation((>)) &&
           exists(BinaryRelation((<))) &&
           exists(BinaryRelation((>=))) &&
           exists(BinaryRelation((<=)));
           
type: Number ('a) = Ord('a) &&
                    exists(BinaryOperator((+)) &&
                    exists(BinaryOperator((-))) &&
                    exists(BinaryOperator((*))) &&
                    exists(BinaryOperator((/))) &&
                    commutative(BinaryOperator((+))) &&
                    !commutative(BinaryOperator((-))) &&
                    commutative(BinaryOperator((*))) &&
                    !commutative(BinaryOperator((/)));

\: min (Ord a, Ord b) { a < b ? a : b; }

//
//  Definition of the type pattern expression operators
//



//
//  Ignoring arguments (automatically)
//

\: add (int; int a, int b) { a + b; }

Add3Func := (int;int,int,int);

\: takes_a_func (void; Add3Func func)
{
    // blah
}

takes_a_func(add); // this can be ok because add can be made into this:

\: add_with_ignored_argument (int; int a, int b, int c)
{
    add(a, b);
}

//
//  slice notation

slice a = 1:10; // [1,10]
slice b = 1::2; // [1,size) by 2
slice c = 1:10:2; // [1,10] by 2
slice d = :10; // [0,10]

slice a = 1..10         // probably better [1,9])
slice b = 1..10..2       // probably better

slice foo = bar["one".."ten"]


//
//  Get rid of relational operators and make them all relative to
//  compare() function
//

operator: <  (bool; 'a a, 'a b) { compare(a,b) <  0; }
operator: <= (bool; 'a a, 'a b) { compare(a,b) <= 0; }
operator: >  (bool; 'a a, 'a b) { compare(a,b) >  0; }
operator: >= (bool; 'a a, 'a b) { compare(a,b) >= 0; }
operator: == (bool; 'a a, 'a b) { compare(a,b) == 0; }
operator: != (bool; 'a a, 'a b) { compare(a,b) != 0; }

//
//  simple class
//

class: Point
{
    float x;
    float y;
    float z;

    method: Point (Point; float a, float b, float c) { x=a; y=b; z=c; }
}

Point p = Point.new()

//
//  interface
//

interface: Thingable
{
    function: flooper (int; string a) { int(a); }
}

Thingable foo = bar;

//
//  All classes can have type expressions in them. So they're somewhat
//  like a function.
//

class: map ('key_type, 'value_type)
{
    'key_type    key;
    'value_type  value;
    this         left;
    this         right;

    method: find ('value_type; 'key_type k)
    {
        if (key == k) return value;
        else if (k < key && left != nil) return left.find(k);
        else if (right != nil) return right.find(k);
    }

    method: insert (void; 'key_type k, 'value_type v)
    {
        if (k == key) 
        {
            value = v;
        }
        else if (k < key)
        {
            if (left)
            {
                left.insert(k, v);
            }
            else
            {
                left = map(k, v)
            }
        }
        else if (right)
        {
            right.insert(k, v);
        }
        else
        {
            right = map(k, v);
        }
    }
}

map x = {"feb", 2, {"jan", 1}, {"march", 3}};
               

//
//  Type patterns.  Patten matching is depth first. 'N and 'M have
//  type "size" or something. The first type pattern determines the
//  meanings of the type/index variables.
//

Matrix   := 'a[#'N,#'M];
VectorN  := 'a[#N];
VectorM  := 'a[#M];

operator: * (VectorN; Matrix m, VectorM a)
{
    VectorN b;

    for_index (i, j; m)
    {
        b[i] += dot(m[i::'N], a);
    }

    b;
}

//
//  Let's say I have x of type (float;float) and y of type
//  (float;float,float) and I want z == y(x(_1),_2).
//  This example is a bit simpler with closures.
//

F1 := (float;float);
F2 := (float;float,float);

// with closures

\: compose (F1 a, F2 b)
{
    \: (float x, float y) { b(a(x),y); }
}


//
//  Constant suffix functions
//

1f -> 1.0       \: f (float; int x) { float(x); }
1.0i            \: i (complex; float x) { complex(0.0, x); }
1.0 + 1.0i
"f.+"r          \: R (regex; string s) { regex(s); }

1.0 + 1i + 2k + 3j

cross(N, 1y);

//
//  Variable attributes
//

float output x = 10.0;

//
//  Additional require parameters
//

require extra_stuff from "."

//
//  Character constant
//

let foo = 'a';


//
//  sparse?
//

sparse float[,] x;
sparse float[];
sparse float[1000,1000];
sparse float[100000];

//
//  Array (List?) Sugar?
//

let x = ["foo", "bar"];
x => string[]


//
//  Macros again. Some syntax stolen from metamorphic macros. The
//  implementation of those looks pretty cool, but 
//
//  These special types #type could be implemented as classes in
//  mu. These are "parts of speech" in the grammar (nonterminals) and
//  cause parser invocation for their part. The result is assigned to
//  the variable.
//
//  The # operator would generate a symbol.  all of the internal Mu
//  symbols and their hierarchy would need to be reflected in mu
//  itself for this to work.
//

syntax: #float pi ::= 3.141529

syntax: #stmt for_index (#id<ID> ; #expr<seq>) #stmt<S> ::=
{
    use mu;
    push_scope();       // anonymous
    declare(#int, ID),

    let e = call("__simple_block",
                 call("__for",
                      call("=", ID, 0),
                      call("<", ID, call("size", seq)),
                      call("_++", "i"),
                      S));

    pop_scope();
    e;
}


//
//  symbolic expressions ala lisp. The difference being they are
//  staticially typed. This could make macros much easier to grok.
//  This would be an overloading of the list syntactic sugar if it
//  coexisted with the list syntax
//

let x  = 1.0,
    e0 = [namespace, "foo", 
          [let, symbol("a"), x],
          [atan, [cos, [sin, 1.0]], reference("a")];
           

//
//  cond ala lisp? This could be created in Mu itself if lazy
//  evaluation were available:
//

function: cond ('a; 
                lazy bool test1, lazy 'a expr1, 
                lazy bool test2, lazy 'a expr2, 
                lazy 'a expr3)
{
    //
    //  If you write it like this instead of using cond it is lazy!
    //

    test1 ? expr1 : (test2 ? expr2 : expr3);
}

let y = cond(x > 1.0, sin(x),
             x < 1.0, cos(x),
             atan(x));

//
//  All of this can be achieved through a function called memoize()
//  which somehow builds a lambda expression with caching built
//  in. The parser could just substitute memoize(expr) in place of
//  expr at the point where the call occurs.
//

foo(memoize(expensive()), 1.0);

//
//  Parameterized types. One way to do this is with a type modifier,
//  however, that is very limited.
//
//  Type construction call is parameterized_type '(' type, ... ')'
//

quatf := quaternion(float);

//
//  provide instead of empty modules?
//

provide foo;

//
//  Guards?
//  Seems over the top. Just use case expression/statement instead
//
          ));


\: fact (int; int a) => case a of
           (0      -> 1;
            a > 0  -> a * fact(a-1));
           
//
//  conditional expression
//

let x = if foo > bar then 10 else 20;

//
//  Stolen from python: triple quote
//

""" 
foo bar 
is the foest of the bar 'foo' is the bar
"""

let Num      'a,
    Num[4,4] 'M,
    Ord      'c;
    

function: add ('a; 'a x, 'a y) { x + y; }

//
//  Haskellesque
//

Vec := vector float[3];
type Vec = vector float[3];

datatype A (Num a, Ord b)
{
    a[] array;
    a thing;
    (a,b) foo;
};

typeclass Group
{
    operator: + (Group; Group, Group);
}

typeclass Ring : Group
{
    operator: * (Ring; Ring, Ring);
}


//
//  Enum
//

union: Weekday { Monday | Tuesday | Wednesday | Thursday | Friday } 

//
//  Tree
//

union: Tree { Leaf int | Node (Tree,Tree,int) }

//
//  Need the -> keyword because we're using '{' '}' in patterns as well.
//  If no keyword, its ambiguous what a pattern is versus an action.
//

\: succ (Weekday; Weekday day)
{
    case (day)
    {
        Monday -> { return Tuesday; }
        Tuesday -> { return Wednesday; }
        Wednesday -> { return Thursday; }
        Thursday  -> { return Friday; }
        Friday -> { return Saturday; }
        Saturday -> { return Sunday; }
        Sunday -> { return Monday; }
    }
}


case (tree)
{
    Tree.Node (left, right, mid)
    {
        left + right + mid;
    }
    
    Tree.Leaf (value)
    {
        print("value = %d\n" % value);
    }

    default
    {
        print("bad");
    }
}

let q = 1 + case tree of
                Node (foo, bar) => 1 
                Leaf val => 2 ;
    
//
//  Pattern match
//

}}

let x = case tree of (Node (l, r, m) -> 1 ; Leaf v -> 2)

let z = let x = 10, y = 50, z = 100 
        in x + y + z ;

let (x, y, z) = (1, 2, 3), w = 10;
let ((x,,),) = ((1,2,3), 4);
let ((x,_,_),_) = ((1,2,3),4);

for_each ((name, value); nameValuePairs)
{
}


//
//  Alternative syntax for "messages"
//

Foo a;
let foo = ;

//
//  extended case statement/expression. Allow matching strings against
//  regex perhaps the rule is: "anything that can be matched using a
//  match function?"
//
//  Add a match operator?
//

string foo;

case (foo)
{
    "bar"    -> print("*foo == bar\n"); 
    "f.+" r  -> print("foo matches f.+\n"); 
    _        -> whatever; 
}

let x = case foo of 
    "bar" -> 1,
    "f.+"r -> 2;

int a;

case (a)
{
    1 -> one;
    2 -> two;
    8 -> eight;
    _ -> other;
}

//
//  addressing evaluation at parse and compile time
//

when_parsing
{
    // use mu.parser implicit

    if (system.system2("date") == "tues")
    {
        load_module("tuesday_module");
    }
    else
    {
        load_module("not_tuesday_module");
    }

    set_function_attributes(Pure);
}

when_compiling
{
    // use mu.compiler implicit
    inline(regex("doSomething.*"));
}

when_compiling("muc")   // if there are multiple compilers this addreses the named one
{
}


//
//  OO functions
//

//
//  Classes
//  The OO needs to be syntactic sugar (like obj-c is syntactic sugar on C)
//

mu.name funcName = mu.name("Class.someFunction");
mu.name sig      = mu.name("(void;int,int)");

".*"r

(void;int,int) F = mu.function(funcName, sig);
(void;int,int) F = mu.method(funcName, sig);

//  This makes for the 


//
//  OBJ-c interface. Messages are juxtaposed with colons at ends of keywords
//  if this can be seemless integrated into the syntax, that would make Cocoa
//  much easier.
//

// [foo blah with: blablah]


//
//  New Function Type syntax:
//

BinaryOp = int, int -> int;
BiggerOp = (int,int -> int), float -> bool;

\: add ('a a, 'a b -> 'a)
{
}


\: foo ('a a -> 'c) 'c(a);

float x = foo<float>(1)


//
//  Blocks, closures, automatic parameters
//

//
// NOTE: '1 is a parameter placeholder variable (slot)
// (aka placeholders in the lambda boost library)
// This syntax allows for both economical lambda expression creation
// (similar to boost, but generalized) as well as a mechanism to generalize
// currying with parameter reordering (not just partial application/evaluation 
// of a particular slot)

foo( \: sin(x) );                 // expression closure
foo( \: sin('1) );                // expression automatic parameter
foo( \: (float x) { sin(x); } );  // expression with formal parameter
foo( \: { sin(x); print(x); } );  // block closure

foo( sin('1) );                   // implicit automatic closure

// permutting curry

foo(int a, int b);

let swappedFoo = foo('2, '1);

let result = zip(array0, array1, sin('1) + cos(1.0 - '2));
let result = map(array, (sin('1) + cos(0)) / 2.0);

//
//  System F with dependant types
//
//  Note that this is not OVERLOADING which is accomplished using
//  similar syntax.
//

\: TupleN ('a, int n)
{
    if n <= 0 then 'a else 'a * TupleN('a, n-1);
}

// (*;*,int) => TupleN

(*;int) IntTuple = TupleN(int, '1);

(*;*) TripleTuple = TupleN('1, 3);

TripleTuple(int) i = (1,2,3);

\: Int () { 'int; }


//
//  autoload
//

autoload: wipes construct (Widget; string);

//  becomes:

module: wipes
{
    global (Widget; string) __autoload_construct = \: (Widget; string name)
    {
        runtime.load_module("wipes");
        let Fname = runtime.intern_name("wipes.construct");
        (Widget;string) F = runtime.lookup_function(Fname);
        __autoload_construct = F;
        F(name);
    }
}

// and add instantiation point:

wipes.construct("foo")

// this is generated:

wipes.__autoload_construct("foo")

// so that the first time it loads the module and subsequent times it
// goes through a thunk to the actual function.


//
//  Structural types. These would be supertypes to all nominal types
//  (like class or struct). Anyplace a structural type is accepted a
//  compatible nominal type may be used (since its a subtype)
//

struct: Nominal { int a; int b; }
{int a, int b} x = Nominal(1,2);    // ok ==> {int a,int b} :> Nominal

//
//  Structure syntax means you can build complex types using union
//

union: Nominal
{
    A float |
    B {int a, int b} |
    C {Nominal next, Nominal prev} |
    Nil
};

Nominal x = B(1,2);
Nominal y = A(1.234);
Nominal z = C(x, y);
        
Nominal C {xp, yp} = z;
//  Structure syntax means you can build complex types using union
//

union: Nominal
{
    A float |
    B {int a, int b} |
    C {Nominal next, Nominal prev} |
    Nil
};

Nominal x = B(1,2);
Nominal y = A(1.234);
Nominal z = C(x, y);
        
Nominal C {xp, yp} = z;

//
//  Default values for records:
//

class: Foo { int a = 1; int b = 2; }

//
//  Keyword assignment
//


\: foo (void; int num, int denom) { a / b; }

foo(denom = 2, num = 1);

//  works for struct init too:

setFoo( Foo { a = 1, b = 2 } );


//
//  Extend interface to encompass haskell-like typeclass + java OO
//  interface. They are essentially the same idea
//

interface: Eq [T]
{
    operator: == (bool; T a, T b);
}

Eq [int]:
{
    operator: == (bool, int a, int b) { int_equal(a, b); }
}

\: member [* T] (bool; Eq[T] a, [T] l) mapTrue(a, l, (==));
