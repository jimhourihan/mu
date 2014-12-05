#ifndef __Mu__NodePrinter__h__
#define __Mu__NodePrinter__h__
//
//  Copyright (c) 2009, Jim Hourihan
//  All rights reserved.
// 
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions
//  are met:
//
//     * Redistributions of source code must retain the above
//       copyright notice, this list of conditions and the following
//       disclaimer.
//
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials
//       provided with the distribution.
//
//     * Neither the name of the Jim Hourihan nor the names of its
//       contributors may be used to endorse or promote products
//       derived from this software without specific prior written
//       permission.
// 
//  THIS SOFTWARE IS PROVIDED BY Jim Hourihan ''AS IS'' AND ANY EXPRESS
//  OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  ARE DISCLAIMED. IN NO EVENT SHALL Jim Hourihan BE LIABLE FOR
//  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
//  OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
//  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//  DAMAGE.
//
#include <Mu/NodeVisitor.h>
#include <Mu/Type.h>
#include <iosfwd>

namespace Mu {

class Context;

//
//  class NodePrinter
//
//  A NodeVisitor that prints out the nodes in a tree to the output
//  stream. 
//

class NodePrinter : public NodeVisitor
{
  public:

    enum Style
    {
	Tree,
	Lispy
    };

    NodePrinter(Node*,std::ostream&, Style=Tree);
    NodePrinter(Node*,std::ostream&, Type::ValueOutputState&, Style=Tree);
    ~NodePrinter();

  protected:
    virtual void preOrderVisit(Node*,int depth);
    virtual void postOrderVisit(Node*,int depth);
    virtual void childVisit(Node*,Node*,size_t);
    
    std::ostream&	out() { return *_ostream; }

  private:
    Style                   _style;
    Type::ValueOutputState* _state;
    std::ostream*           _ostream;
};


} // namespace Mu

#endif // __Mu__NodePrinter__h__
