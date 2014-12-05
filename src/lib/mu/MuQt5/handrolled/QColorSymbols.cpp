
//
//  This is for QGradient

Context::TypeVector types;
types.push_back(c->doubleType());
types.push_back(this);
c->arrayType((const Type*)c->tupleType(types), 1, 0);
