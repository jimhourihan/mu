#ifndef __Mu__NodeVisitor__h__
#define __Mu__NodeVisitor__h__
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
#include <sys/types.h>

namespace Mu {

class Node;

//
//  class NodeVisitor
//
//  Visit each node in a node tree. There are multiple methods to
//  traverse the tree using a NodeVisitor. The tree can be edited from
//  this class.
//
//  Some typical uses of a NodeVisitor are for printing a Node tree,
//  collapsing constant expressions, sub-expression elimination.
//

class NodeVisitor
{
  public:
    explicit NodeVisitor(Node*);
    NodeVisitor();
    ~NodeVisitor();

    //
    //	Traversal methods
    //

    void	    traverse();
    Node*	    root() const { return _root; }

  protected:
    virtual void    preOrderVisit(Node*,int depth);
    virtual void    postOrderVisit(Node*,int depth);
    virtual void    childVisit(Node*, Node*, size_t);

    size_t          nodeIndex() const { return _index; }
    Node*           nodeParent() const { return _parent; }
    void            set(Node*);

  private:
    void	    traverseRecursive(Node*,int);
    
  private:
    Node*	    _root;
    Node*           _parent;
    size_t          _index;
};


} // namespace Mu

#endif // __Mu__NodeVisitor__h__
