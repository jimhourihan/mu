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

#include <Mu/NodeSimplifier.h>
#include <Mu/NodeAssembler.h>
#include <Mu/Function.h>
#include <Mu/Context.h>

namespace Mu {
using namespace std;

NodeSimplifier::NodeSimplifier(NodeAssembler* as) 
    : NodeVisitor(),
      _as(as),
      _context(as->context())
{
}

Node*
NodeSimplifier::operator() (Node* n)
{
    set(n);
    traverse();
    return root();
}

void
NodeSimplifier::preOrderVisit(Node* n, int depth)
{
    //
    //  This is all very hacked to get things started. What's really
    //  needed here is basically an LR() parser framework to identify
    //  sub-trees and exectute actions on the non-terminals
    //

    const Symbol* s = n->symbol();

    if (s == _context->fixedFrameBlock())
    {
        //
        //  If its a fixed frame block and the frame size is 0 convert
        //  it into a simple block in place.
        //

        DataNode* dn = static_cast<DataNode*>(n);
        int size = dn->_data._int;

        if (size == 0)
        {
            const Function* f = _context->simpleBlock();
            n->_symbol = f;
            n->_func   = f->func(n);
        }
    }

    if (s == _context->simpleBlock())
    {
        //
        //  If its a simple frame block and it has only a single
        //  argument just return the argument.
        //

        if (n->numArgs() == 1)
        {
            Node* nn = n->_argv[0];
            n->_argv[0] = 0;

            if (nodeParent() && nodeParent() != n)
            {
                nodeParent()->_argv[nodeIndex()] = nn;
            }
            else
            {
                set(nn);
            }

            n->deleteSelf();
        }
    }
}



} // namespace Mu
