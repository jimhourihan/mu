
//
//  Test out the naked operator syntax
//

let add = (+);
(int; int, int) iadd = add;
let add1 = iadd(1,);

add1(2);

assert((int;int,int)((+))(1,2) == 3);     // explicit
//assert((+)(1,2) == 3);                  // implicit -- does not work yet
