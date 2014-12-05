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
#include <Mu/Node.h>

namespace Mu {
using namespace std;

NodeVisitor::NodeVisitor(Node *node) : _root(node), _parent(0), _index(0) {}
NodeVisitor::NodeVisitor() : _root(0), _parent(0), _index(0) {}
NodeVisitor::~NodeVisitor() {}

void
NodeVisitor::set(Node* node)
{
    _root = node;
}

void
NodeVisitor::postOrderVisit(Node*,int)
{
    // default is to do nothing
}

void
NodeVisitor::preOrderVisit(Node*,int)
{
    // default is to do nothing
}

void
NodeVisitor::childVisit(Node*, Node*, size_t)
{
    // default is to do nothing
}

//---

void
NodeVisitor::traverse()
{
    if (_root) traverseRecursive(_root,0);
}

void	    
NodeVisitor::traverseRecursive(Node *node, int depth)
{
    Node* saved_parent = _parent;
    preOrderVisit(node, depth);

    if (node)
    {
        _parent = node;
        size_t saved_index = _index;

        for (int i=0,s=node->numArgs(); i<s; i++)
        {
            _index = i;
            childVisit(node, node->argNode(i), i);
            traverseRecursive(node->argNode(i), depth+1);
        }

        _index = saved_index;
        _parent = saved_parent;
    }

    postOrderVisit(node,depth);
}


} // namespace Mu
