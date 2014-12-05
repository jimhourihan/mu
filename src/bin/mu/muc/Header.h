//******************************************************************************
// Copyright (c) 2003 Tweak Inc. 
// All rights reserved.
//******************************************************************************
#ifndef __muc__Header__h__
#define __muc__Header__h__

namespace Muc {

typedef unsigned int        uint32;
typedef int                 int32;
typedef unsigned short      uint16;
typedef unsigned char       uint8;
typedef float               float32;
typedef double              float64;

struct Header
{
    static const uint32 Magic = 0x0000af9f;
    static const uint32 Cigam = 0x9faf0000;

    uint32  magic;
};


struct NameTableHeader
{
    uint32  size;
};

struct SymbolTableHeader
{
    uint32  size;
};

struct Symbol
{
    uint32  name;
    uint32  parent;
}

} // $NAMESPACE

#endif // __muc__Header__h__
