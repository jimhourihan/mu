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

#include <Mu/ASTNode.h>
#include <Mu/NodePatch.h>
#include <Mu/Node.h>
#include <Mu/Function.h>
#include <Mu/ReferenceType.h>
#include <Mu/ParameterVariable.h>
#include <Mu/Context.h>
#include <Mu/Exception.h>
#include <Mu/MemberVariable.h>
#include <Mu/MemberFunction.h>
#include <Mu/MachineRep.h>
#include <Mu/Unresolved.h>
#include <algorithm>

namespace Mu {
using namespace std;

NodePatch::NodePatch(NodeAssembler *as, Function* f) 
    : NodeVisitor(f->body()),
      _as(as),
      _method(dynamic_cast<MemberFunction*>(f)),
      _function(f),
      _slot(0)
{
    if (_as->context()->verbose())
    {
        cout << ">>> Mu: patching " 
             << f->fullyQualifiedName() << endl;
    }
}

NodePatch::~NodePatch() {}

void
NodePatch::preOrderVisit(Node* node, int depth)
{
    const Symbol* s = node->symbol();

    if (dynamic_cast<const UnresolvedSymbol*>(s))
    {
        ASTNode* astnode = static_cast<ASTNode*>(node);
        _as->setScope(astnode->scope);
        astnode->preResolve(*this);
    }
}

void    
NodePatch::postOrderVisit(Node* node, int depth)
{
    const Symbol* s = node->symbol();

    if (dynamic_cast<const UnresolvedSymbol*>(s))
    {
        ASTNode* astnode = static_cast<ASTNode*>(node);
        _as->setScope(astnode->scope);

        if (Node* newNode = astnode->resolve(*this))
        {
            if (astnode != newNode)
            {
                if (root() == node)
                {
                    //
                    //  Its the root of the function so we need to check
                    //  that the types match and fix if not.
                    //

                    if (Node* cn = _as->cast(newNode, _function->returnType()))
                    {
                        newNode = cn;
                    }
                    else
                    {
                        _as->freportError(newNode,
                                          "Cannot cast from type \"%s\" to "
                                          "type \"%s\"",
                                          newNode->type()->fullyQualifiedName().c_str(),
                                          _function->returnType()->fullyQualifiedName().c_str());

                        throw BadCastException();
                    }

                    _function->setBody(newNode);
                }
                else
                {
                    node->releaseArgv();
                    node->deleteSelf();
                    nodeParent()->setArg(newNode, nodeIndex());
                }
            }
        }
        else
        {
            _as->freportError(node,
                              "Unresolvable expression in function \"%s\"",
                              _function->fullyQualifiedName().c_str());

            throw UnresolvedFunctionException();
        }
    }
}

void    
NodePatch::childVisit(Node* node, Node* child, size_t index)
{
    const Symbol* s = node->symbol();

    if (dynamic_cast<const UnresolvedSymbol*>(s))
    {
        ASTNode* astnode = static_cast<ASTNode*>(node);
        _as->setScope(astnode->scope);
        astnode->childVisit(*this, child, index);
    }
}

Node*
NodePatch::patch()
{
    _as->allowUnresolvedCalls(false);
    traverse();
    _as->allowUnresolvedCalls(true);
    return root();
}

} // namespace Mu
