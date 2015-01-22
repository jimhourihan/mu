//
//  Copyright (c) 2010 Tweak Software. 
//  All rights reserved.
//
#include "AST.h"
#include "Grammar.h"
#include <Mu/Value.h>
#include <Mu/ParameterVariable.h>
#include <MuLang/StringType.h>
#include <sstream>

namespace Mu {
namespace AST {
using namespace std;

typedef NodeAssembler::NodeList NodeList;
typedef NodeAssembler::SymbolList SymbolList;

ASTNode::ASTNode(const Location& loc)
  : next(0), 
    isTuple(false),
    isSequence(false) 
{
    location = loc; 
}

ASTNode::~ASTNode() {}

ASTNode*
ASTNode::append(ASTNode* n)
{
    ASTNode* node = this;
    for (; node->next; node = node->next);
    node->next = n;
    return this;
}

void ASTNode::print(ostream& o) const {}
void ASTNode::printAnnotated(ostream& o) const {}

Node*
ASTNode::resolve(NodeAssembler& as) const
{
    as.setLineNum(location.last_line);
    as.setCharNum(location.last_column);
    Node* n = resolveInternal(as);
    return n;
}

Node*
ASTNode::resolveInternal(NodeAssembler& as) const
{
    return 0;
}

Node*
ASTNode::errorReturn(NodeAssembler& as, const string& msg) const
{
    as.setLineNum(location.last_line);
    as.setCharNum(location.last_column);
    as.freportError(msg.c_str());
    return 0;
}

void 
ASTNode::printList(ostream& o, char sep) const
{
    for (const ASTNode* n = this; n; n = n->next)
    {
        if (n != this) o << sep << " ";
        n->print(o);
    }
}

void 
ASTNode::printListAnnotated(ostream& o, char sep) const
{
    for (const ASTNode* n = this; n; n = n->next)
    {
        if (n != this) o << sep << " ";
        n->printAnnotated(o);
    }
}

void 
ASTNode::error(NodeAssembler& as, const ASTNode* astnode, const char* msg, ...)
{
    char temp[256];

    va_list ap;
    va_start(ap,msg);
    vsprintf(temp,msg,ap);
    va_end(ap);

    as.setLineNum(astnode->location.last_line);
    as.setCharNum(astnode->location.last_column);
    as.reportError(temp);
}

Node* 
ASTNode::resolveSymbolConstant(NodeAssembler& as, Node* node) const
{
    if (as.isConstant(node))
    {
        GLRContext* c = static_cast<GLRContext*>(as.context());
        const Type* t = node->type();
        DataNode* dn = static_cast<DataNode*>(node);

        if (t == c->functionSymbolType())
        {
            const Function* F = reinterpret_cast<const Function*>(dn->_data._Pointer);
            return as.functionConstant(F);
        }
        else if (t == c->typeSymbolType())
        {
        }
        else if (t == c->moduleSymbolType())
        {
        }

        return node;
    }
    else
    {
        return node;
    }
}

//----------------------------------------------------------------------

NodeAssembler::Pattern* 
Pattern::resolvePattern(NodeAssembler& as) const
{
    return 0;
}

//----------------------------------------------------------------------

Node* 
MergeNode::resolveInternal(NodeAssembler& as) const
{
    //
    //  This is hugely flawed if it every actually has to be
    //  resolved. The context would have to be split here to
    //  successfully find out one of the branches is not going to
    //  work. Otherwise it will be corrupted with a bunch of garbage
    //  from the failed branch.
    //

    Node* n0 = node0->resolve(as);
    Node* n1 = node1->resolve(as);

    if (n0 && n1)
    {
        return errorReturn(as, "Ambiguous expression: both branches are valid");
    }

    return n0 ? n0 : n1;
}

void 
MergeNode::print(std::ostream& o) const
{
    cout << "<merge>(";
    node0->print(o);
    cout << " <> ";
    node1->print(o);
    cout << ")";
}

void
MergeNode::printAnnotated(ostream& o) const
{
    cout << "MergeNode(";
    node0->printAnnotated(o);
    cout << " --or-- ";
    node1->printAnnotated(o);
    cout << ")";
}

//----------------------------------------------------------------------

Node* 
ScopeOperator::resolveInternal(NodeAssembler& as) const
{
    MuLangContext* c = static_cast<MuLangContext*>(as.context());

    if (Node* lnode = left->resolve(as))
    {
        if (as.isConstant(lnode))
        {
            DataNode* dnode = static_cast<DataNode*>(lnode);
            const Type* type = lnode->type();

            if (type == c->moduleSymbolType() || type == c->typeSymbolType())
            {
                as.prefixScope((const Symbol*)(dnode->_data._Pointer));
            }
            else
            {
                // some literal constant -- look in its type
                as.prefixScope(lnode->type());
            }

            Node* rnode = right->resolve(as);
            as.prefixScope(0);
            return rnode;
        }
    }

    return errorReturn(as, "in scope operator");
}

void
ScopeOperator::print(ostream& o) const
{
    left->print(o); o << "."; right->print(o);
}

void
ScopeOperator::printAnnotated(ostream& o) const
{
    cout << "ScopeOperator(";
    left->printAnnotated(o); 
    o << ","; 
    right->printAnnotated(o);
    o << ")";
}

//----------------------------------------------------------------------

void
RefIdentifier::print(ostream& o) const
{
    o << name;
}

void
RefIdentifier::printAnnotated(ostream& o) const
{
    o << "\"" << name << "\"";
}

Node* 
RefIdentifier::resolveInternal(NodeAssembler& as) const
{
    if (const Symbol* s = as.findSymbolInScope(name))
    {
        if (const Function* F = dynamic_cast<const Function*>(s))
        {
            return as.functionSymbolConstant(F);
        }
        else if (const Variable* v = dynamic_cast<const Variable*>(s))
        {
            return as.referenceVariable(v);
        }
        else if (const Module* m = dynamic_cast<const Module*>(s))
        {
            return as.moduleSymbolConstant(m);
        }
        else if (const Type* t = dynamic_cast<const Type*>(t))
        {
            return as.typeSymbolConstant(t);
        }
    }

    ostringstream str;
    str << "Unresolved symbol \"" << name << "\"";
    return errorReturn(as, str.str());
}

//----------------------------------------------------------------------

void
Constant::print(ostream& o) const
{
    switch (type)
    {
      case MU_FLOATCONST: o << value.as<double>(); break;
      case MU_INTCONST: o << value.as<int64>(); break;
      case MU_BOOLCONST: o << (value.as<bool>() ? "true" : "false"); break;
      case MU_CHARCONST: o << "'" << char(value.as<int>()) << "'"; break;
      case MU_STRINGCONST:
          StringType::String* s = reinterpret_cast<StringType::String*>(value.as<Pointer>());
          StringType::outputQuotedString(o, s->utf8());
          break;
    }
}

void
Constant::printAnnotated(ostream& o) const
{
    print(o);
}

Node* 
Constant::resolveInternal(NodeAssembler& as) const
{
    const Type* type = 0;
    GLRContext* context = static_cast<GLRContext*>(as.context());
    Object* obj = 0;

    switch (this->type)
    {
      case MU_FLOATCONST: type = context->doubleType(); break;
      case MU_INTCONST: type = context->intType(); break;
      case MU_BOOLCONST: type = context->boolType(); break;
      case MU_CHARCONST: type = context->charType(); break;
      case MU_STRINGCONST: type = context->stringType(); break;
      case MU_NIL: type = context->nilType(); break;
    }

    DataNode* n = as.constant(type, obj);
    n->_data = value;
    return n;
}

//----------------------------------------------------------------------

void
Apply::print(ostream& o) const
{
    o << name;
    o << "("; args->printList(o); o << ")";
}

void
Apply::printAnnotated(ostream& o) const
{
    o << "Apply(\"" << name << "\", ";
    args->printListAnnotated(o); 
    o << ")";
}

Node* 
Apply::resolveInternal(NodeAssembler& as) const
{
    NodeList nl = as.emptyNodeList();

    for (ASTNode* n = args; n; n = n->next)
        nl.push_back(resolveSymbolConstant(as, n->resolve(as)));

    Node* rnode = 0;

    if (const Symbol* s = as.findSymbolInScope(name))
    {
        if (const Function* F = dynamic_cast<const Function*>(s))
        {
            rnode = as.callBestOverloadedFunction(F, nl);
        }
        else if (const Variable* v = dynamic_cast<const Variable*>(s))
        {
            rnode = as.call(v, nl);
        }
        else if (const Module* m = dynamic_cast<const Module*>(s))
        {
            //
        }
        else if (const Type* t = dynamic_cast<const Type*>(t))
        {
            //
        }
    }

    as.removeNodeList(nl);
    return rnode;
}

//----------------------------------------------------------------------

void
ExprApply::print(ostream& o) const
{
    expression->print(o);
    o << "("; args->printList(o); o << ")";
}

void
ExprApply::printAnnotated(ostream& o) const
{
    o << "ExprApply(";
    expression->printAnnotated(o);
    o << ", "; args->printListAnnotated(o); o << ")";
}

Node* 
ExprApply::resolveInternal(NodeAssembler& as) const
{
    GLRContext* c = static_cast<GLRContext*>(as.context());

    NodeList nl = as.emptyNodeList();

    for (ASTNode* n = args; n; n = n->next)
    {
        nl.push_back(resolveSymbolConstant(as, n->resolve(as)));

        if (!nl.back())
        {
            as.removeNodeList(nl);
            return errorReturn(as, "Bad argument");
        }
    }
 
    if (Node* enode = expression->resolve(as))
    {
        if (as.isSymbolExpression(enode))
        {
            const Type* t = enode->type();

            if (t == c->typeSymbolType())
            {
                Node* n = as.call(as.evalSymbolicExpression<Type>(enode), nl);
                as.removeNodeList(nl);
                return n;
            }
            else if (t == c->functionSymbolType())
            {
                const Function* F = as.evalSymbolicExpression<Function>(enode);
                Node* n = as.callBestOverloadedFunction(F, nl);
                as.removeNodeList(nl);
                return n;
            }
        }
        else if (as.isConstant(enode))
        {
            const Type* t = enode->type();
            DataNode* dn = static_cast<DataNode*>(enode);

            if (t == c->functionSymbolType())
            {
                const Function* F = reinterpret_cast<const Function*>(dn->_data._Pointer);
                Node* n = as.callBestOverloadedFunction(F, nl);
                as.removeNodeList(nl);
                return n;
            }
        }
        else
        {
            Node* n = as.call(enode, nl, false); // TODO: what should 3rd arg be?
            as.removeNodeList(nl);
            return n;
        }
    }

    return errorReturn(as, "Unresolved expression");
}

//----------------------------------------------------------------------

void
IndexedExpr::print(ostream& o) const
{
    expression->print(o);
    o << "["; args->printList(o); o << "]";
}

void
IndexedExpr::printAnnotated(ostream& o) const
{
    o << "IndexedExpr(";
    expression->printAnnotated(o);
    o << ", "; args->printListAnnotated(o); o << ")";
}

Node*
IndexedExpr::resolveInternal(NodeAssembler& as) const
{
    NodeList nl = as.emptyNodeList();

    for (ASTNode* n = args; n; n = n->next) 
    {
        if (Node* node = resolveSymbolConstant(as, n->resolve(as)))
        {
            nl.push_back(node);
        }
        else
        {
            as.removeNodeList(nl);
            return errorReturn(as, "Bad argument");
        }
    }

    Node* node = as.memberOperator("[]", 
                                   resolveSymbolConstant(as, expression->resolve(as)), 
                                   nl);

    as.removeNodeList(nl);
    return node;
}

//----------------------------------------------------------------------

void
ConditionalExpr::print(ostream& o) const
{
    o << "if ";
    condition->print(o);
    o << " then ";
    thenexpr->print(o);
    o << " else ";
    elseexpr->print(o);
}

void
ConditionalExpr::printAnnotated(ostream& o) const
{
    o << "ConditionalExpr(";
    condition->printAnnotated(o);
    o << ", ";
    thenexpr->printAnnotated(o);
    o << ", ";
    elseexpr->printAnnotated(o);
    o << ")";
}

Node* 
ConditionalExpr::resolveInternal(NodeAssembler& as) const
{
    Node* c = resolveSymbolConstant(as, condition->resolve(as)); 
    if (!c) return errorReturn(as, "Bad conditional expression");
    Node* e1 = resolveSymbolConstant(as, thenexpr->resolve(as));
    if (!e1) return errorReturn(as, "Bad then expression");
    Node* e2 = resolveSymbolConstant(as, elseexpr->resolve(as));
    if (!e2) return errorReturn(as, "Bad else expression");

    return as.conditionalExpression(c, e1, e2);
}

//----------------------------------------------------------------------

void
ListExpr::print(ostream& o) const
{
    o << "["; args->printList(o); o << "]";
}

void
ListExpr::printAnnotated(ostream& o) const
{
    o << "ListExpr(";
    args->printListAnnotated(o); 
    o << ")";
}

Node* 
ListExpr::resolveInternal(NodeAssembler& as) const
{
    NodeList nl = as.emptyNodeList();

    for (ASTNode* n = args; n; n = n->next) 
    {
        if (Node* node = resolveSymbolConstant(as, n->resolve(as)))
        {
            nl.push_back(node);
        }
        else
        {
            as.removeNodeList(nl);
            return errorReturn(as, "Bad argument");
        }
    }

    Node* node = as.listNode(nl);
    as.removeNodeList(nl);
    return node;
}

//----------------------------------------------------------------------

void
TupleExpr::print(ostream& o) const
{
    o << "("; args->printList(o); o << ")";
}

void
TupleExpr::printAnnotated(ostream& o) const
{
    o << "TupleExpr(";
    args->printListAnnotated(o); o << ")";
}

Node* 
TupleExpr::resolveInternal(NodeAssembler& as) const
{
    NodeList nl = as.emptyNodeList();

    for (ASTNode* n = args; n; n = n->next) 
    {
        if (Node* node = resolveSymbolConstant(as, n->resolve(as)))
        {
            nl.push_back(node);
        }
        else
        {
            as.removeNodeList(nl);
            return errorReturn(as, "Bad argument");
        }
    }

    Node* node = as.tupleNode(nl);
    as.removeNodeList(nl);
    return node;
}

//----------------------------------------------------------------------

void
SequenceExpr::print(ostream& o) const
{
    o << "{"; args->printList(o, ';'); o << "}";
}

void
SequenceExpr::printAnnotated(ostream& o) const
{
    o << "SequenceExpr(";
    args->printListAnnotated(o, ','); o << ")";
}

Node* 
SequenceExpr::resolveInternal(NodeAssembler& as) const
{
    as.pushAnonymousScope("__");
    NodeList nl = as.emptyNodeList();

    for (ASTNode* n = args; n; n = n->next) 
    {
        if (Node* node = resolveSymbolConstant(as, n->resolve(as)))
        {
            nl.push_back(node);
        }
        else
        {
            as.removeNodeList(nl);
            as.popScope();
            return errorReturn(as, "Bad argument");
        }
    }
    
    Node* node = 0;

    if (nl.size() > 1)
    {
        node = as.callBestOverloadedFunction(as.context()->simpleBlock(), nl);
    }
    else if (nl.size() == 1)
    {
        node = nl.front();
    }
    else
    {
        node = as.callBestOverloadedFunction(as.context()->noop(), as.emptyNodeList());
    }

    as.removeNodeList(nl);
    as.popScope();

    return node;
}

//----------------------------------------------------------------------


NodeAssembler::Pattern* 
NamePattern::resolvePattern(NodeAssembler& as) const
{
    if (RefIdentifier* id = dynamic_cast<RefIdentifier*>(name))
    {
        return as.newPattern(id->name);
    }
    else
    {
        return 0;
    }
}

void 
NamePattern::print(std::ostream& o) const
{
    name->print(o);
}

void 
NamePattern::printAnnotated(std::ostream& o) const
{
    o << "NamePattern(";
    name->printAnnotated(o);
    o << ")";
}

//----------------------------------------------------------------------

NodeAssembler::Pattern* 
ConstructorPattern::resolvePattern(NodeAssembler& as) const
{
    return 0;
}

NodeAssembler::Pattern* 
ConstantPattern::resolvePattern(NodeAssembler& as) const
{
    if (unary_minus)
    {
        Node* n = as.unaryOperator("-",expression->resolve(as));
        
        if (!n)
        {
            errorReturn(as, "negation does not apply here");
            return 0;
        }

        return as.newPattern(n);
    }
    else
    {
        return as.newPattern(expression->resolve(as));
    }
}

void 
ConstantPattern::print(std::ostream& o) const
{
    if (unary_minus) o << "-";
    expression->print(o);
}

void 
ConstantPattern::printAnnotated(std::ostream& o) const
{
    if (unary_minus) o << "-";
    expression->printAnnotated(o);
}

//----------------------------------------------------------------------

NodeAssembler::Pattern* 
MatchAnyPattern::resolvePattern(NodeAssembler& as) const
{
    return as.newPattern(as.context()->internName("_").nameRef());
}

void 
MatchAnyPattern::print(std::ostream& o) const
{
    o << "_";
}

//----------------------------------------------------------------------

NodeAssembler::Pattern* 
CompoundPattern::resolvePattern(NodeAssembler& as) const
{
    NodeAssembler::Pattern* p = 0;

    for (Pattern* pnode = patterns; pnode; pnode = (Pattern*)pnode->next)
    {
        NodeAssembler::Pattern* rpat = pnode->resolvePattern(as);
        if (!p) p = rpat;
        else as.appendPattern(p, rpat);
    }

    const char* t = "?tuple";

    if (type == Struct) 
    {
        t = "?class_not_tuple";
    }
    else if (type == List) 
    {
        t = "?list";
        as.unflattenPattern(p, "?list");
    }

    return as.newPattern(p, t);
}

void 
CompoundPattern::print(std::ostream& o) const
{
    const char* t = "()";
    if (type == Struct) t = "{}";
    else if (type == List) t = "[]";

    o << t[0];

    for (Pattern* p = patterns; p; p = (Pattern*)p->next)
    {
        if (p != patterns) o << ", ";
        p->print(o);
    }

    o << t[1];
}

//----------------------------------------------------------------------

NodeAssembler::Pattern* 
ConsPattern::resolvePattern(NodeAssembler& as) const
{
    return 0;
}

//----------------------------------------------------------------------

Node* 
PatternEquality::resolveInternal(NodeAssembler& as) const
{
    if (expression)
    {
        return as.resolvePatterns(pattern->resolvePattern(as),
                                  as.dereferenceLValue(resolveSymbolConstant(as, expression->resolve(as))));
    }
    else
    {
        return 0;
    }
}

void
PatternEquality::print(ostream& o) const
{
    pattern->print(o);
    o << " = ";
    expression->print(o);
}

void 
PatternEquality::printAnnotated(std::ostream& o) const
{
    o << "PatternEquality(";
    pattern->printAnnotated(o);
    o << " = ";
    expression->printAnnotated(o);
    o << ")";
}

//----------------------------------------------------------------------

Node* 
CasePattern::resolveInternal(NodeAssembler& as) const
{
    NodeList nl = as.newNodeList(expression->resolve(as));
    Node* cp = as.casePattern(pattern->resolvePattern(as));
    if (!cp)
    {
        as.removeNodeList(nl);
        return errorReturn(as, "Invalid case pattern");
    }
    Node* n = as.casePatternStatement(cp, nl);
    as.removeNodeList(nl);
    return n;
}

void
CasePattern::print(ostream& o) const
{
    pattern->print(o);
    o << " -> ";
    expression->print(o);
}

void 
CasePattern::printAnnotated(std::ostream& o) const
{
    o << "CasePattern(";
    pattern->printAnnotated(o);
    o << " -> ";
    expression->printAnnotated(o);
    o << ")";
}

//----------------------------------------------------------------------

Node*
LetExpr::resolveInternal(NodeAssembler& as) const
{
    as.declarationType(0);

    if (expression)
    {
        as.pushAnonymousScope("__");
    }

    NodeList nl = as.emptyNodeList();

    for (ASTNode* n = assignments; n; n = n->next) 
    {
        if (Node* node = n->resolve(as))
        {
            nl.push_back(node);
        }
        else
        {
            as.removeNodeList(nl);
            return errorReturn(as, "Unresolved pattern");
        }
    }

    Node* p = as.callBestOverloadedFunction(as.context()->patternBlock(), nl);
    as.removeNodeList(nl);

    Node* bnode = 0;

    if (expression)
    {
        if (Node* n = resolveSymbolConstant(as, expression->resolve(as)))
        {
            nl = as.newNodeList(p);
            nl.push_back(n);
            
            bnode = as.callBestOverloadedFunction(as.context()->simpleBlock(), nl);
            as.removeNodeList(nl);
        }

        as.popScope();
    }
    else
    {
        nl = as.newNodeList(p);
        bnode = as.callBestOverloadedFunction(as.context()->simpleBlock(), nl);
        as.removeNodeList(nl);
    }

    return bnode;
}

void
LetExpr::print(ostream& o) const
{
    o << "let ";
    assignments->printList(o);

    if (expression)
    {
        o << " in ";
        expression->print(o);
    }
}

void
LetExpr::printAnnotated(ostream& o) const
{
    o << "Let(";
    assignments->printListAnnotated(o);
    if (expression)
    {
        o << ", ";
        expression->printAnnotated(o);
    }
    o << ")";
}

//----------------------------------------------------------------------

Node*
RequireExpr::resolveInternal(NodeAssembler& as) const
{
    Module* m = 0;

    //
    //  Need to test for type, existing module, or try to load module
    //  right now its only trying to load
    //

    if (expression)
    {
        as.pushAnonymousScope("__");
    }

    for (ASTNode* n = identifiers; n; n = n->next)
    {
        RefIdentifier* id = static_cast<RefIdentifier*>(n);

        if (!(m = Module::load(id->name, as.process(), as.context())))
        {
            const Environment::SearchPath& paths = Mu::Environment::modulePath();

            for (int i=0; i < paths.size(); i++)
            {
                const Mu::String& p = paths[i];

                error(as, this, 
                      "No module named \"%s\" found in %s", 
                      id->name.c_str(), 
                      p.c_str());
            }
        }
        else if (use)
        {
            as.pushScope(m, false);
        }
    }

    if (expression)
    {
        Node* enode = resolveSymbolConstant(as, expression->resolve(as));
        as.popScope();
        return enode;
    }
    else
    {
        return as.callBestOverloadedFunction(as.context()->noop(), as.emptyNodeList());
    }
}

void
RequireExpr::print(ostream& o) const
{
    o << (use ? "use " : "require ");
    identifiers->printList(o);

    if (expression)
    {
        o << " in ";
        expression->print(o);
    }
}

void
RequireExpr::printAnnotated(ostream& o) const
{
    o << "RequireExpr(" << (use ? "use" : "require") << " [";
    identifiers->printListAnnotated(o);
    o << "]";

    if (expression)
    {
        o << ", ";
        expression->printAnnotated(o);
    }

    o << ")";
}

//----------------------------------------------------------------------

Node*
CaseExpr::resolveInternal(NodeAssembler& as) const
{
    Node* n = as.beginCase(expression->resolve(as));

    NodeList nl = as.emptyNodeList();

    for (ASTNode* a = patterns; a; a = a->next)
    {
        nl.push_back(a->resolve(as));
    }

    return as.finishCase(n, nl);
}

void
CaseExpr::print(ostream& o) const
{
    o << "case ";
    expression->print(o);
    o << " of { ";
    patterns->printList(o);
    o << " }";
}

void
CaseExpr::printAnnotated(ostream& o) const
{
    o << "CaseExpr(";
    expression->printAnnotated(o);
    o << ", ";
    patterns->printListAnnotated(o);
    o << ")";
}
//----------------------------------------------------------------------

Node*
VariableInitializer::resolveInternal(NodeAssembler& as) const
{
    return 0;
}

void
VariableInitializer::print(ostream& o) const
{
    identifier->print(o);
    o << " = ";
    expression->print(o);
}

void
VariableInitializer::printAnnotated(ostream& o) const
{
    o << "VariableInitializer(";
    identifier->printAnnotated(o);
    o << " = ";
    expression->printAnnotated(o);
    o << ")";
}
//----------------------------------------------------------------------

Node*
VariableDeclaration::resolveInternal(NodeAssembler& as) const
{
    if (Node* tnode = type->resolve(as))
    {
        if (const Type* t = as.evalSymbolicExpression<Type>(tnode))
        {
            as.declarationType(t);

            NodeList nl = as.emptyNodeList();

            for (ASTNode* e = initializers; e; e = e->next)
            {
                VariableInitializer* init = static_cast<VariableInitializer*>(e);
                RefIdentifier* i = static_cast<RefIdentifier*>(init->identifier);

                if (Node* enode = resolveSymbolConstant(as, init->expression->resolve(as)))
                {
                    Node* inode = as.declareInitializer(i->name, enode);
                    nl.push_back(inode);
                }
            }

            Node* vnode = as.callBestOverloadedFunction(as.context()->simpleBlock(), nl);
            as.removeNodeList(nl);
            return vnode;
        }
    }

    return errorReturn(as, "Unresolved variable declaration");
}

void
VariableDeclaration::print(ostream& o) const
{
    //o << "var ";
    type->print(o);
    o << " ";
    initializers->printList(o);
}

void
VariableDeclaration::printAnnotated(ostream& o) const
{
    o << "VariableDeclaration(";
    type->printAnnotated(o);
    o << ", ";
    initializers->printListAnnotated(o);
    o << ")"; 
}

//----------------------------------------------------------------------

Node*
AggregateValueExpr::resolveInternal(NodeAssembler& as) const
{
    if (type)
    {
        if (Node* tnode = type->resolve(as))
        {
            if (const Type* t = as.evalSymbolicExpression<Type>(tnode))
            {
                as.pushType(t);
            }
            else
            {
                return errorReturn(as, "Bad type expression");
            }
        }
        else
        {
            return errorReturn(as, "Bad type expression");
        }
    }
    else
    {
        if (!as.topType()) return errorReturn(as, "Internal error");
    }

    size_t field = 0;
    NodeList nl = as.emptyNodeList();

    for (ASTNode* n = list; n; n = n->next, field++)
    {
        as.pushType(as.topType()->fieldType(field));
        
        if (Node* node = n->resolve(as))
        {
            nl.push_back(node);
        }
        else
        {
            as.popType();
            return errorReturn(as, "Bad list item");
        }

        as.popType();
    }

    const Type* t = as.topType();
    Node* rnode = as.call(t, nl);
    as.removeNodeList(nl);
    if (type) as.popType();

    return rnode;
}

void
AggregateValueExpr::print(ostream& o) const
{
    if (type) 
    {
        type->print(o);
        o << " ";
    }

    o << "{";
    list->printList(o);
    o << "}";
}

void
AggregateValueExpr::printAnnotated(ostream& o) const
{
    o << "AggregateValueExpr(";
    if (type) 
    {
        type->printAnnotated(o);
        o << ", ";
    }
    else 
    {
        list->printAnnotated(o);
    }

    o << ")";
}

//----------------------------------------------------------------------

Node* 
ParamDecl::resolveInternal(NodeAssembler& as) const
{
    const Type* t = 0;

    if (type)
    {
        if (Node* tnode = type->resolve(as))
        {
            if (!(t = as.evalSymbolicExpression<Type>(tnode)))
            {
                return errorReturn(as, "Bad type expression");
            }
        }
        else
        {
            return errorReturn(as, "Bad type expression");
        }
    }

    string pname = "__";

    if (RefIdentifier* idnode = dynamic_cast<RefIdentifier*>(name))
    {
        pname = idnode->name.c_str();
    }

    return as.paramSymbolConstant(new ParameterVariable(as.context(), pname.c_str(), t));
}

void 
ParamDecl::print(ostream& o) const
{
    type->print(o);
    o << " ";
    name->print(o);

    if (value) 
    {
        o << " ";
        value->print(o);
    }
}

void 
ParamDecl::printAnnotated(ostream& o) const
{
    o << "ParamDecl(";
    type->printAnnotated(o);
    o << ", ";
    name->printAnnotated(o);

    if (value) 
    {
        o << ", ";
        value->printAnnotated(o);
    }

    o << ")";
}

Node* 
FunctionDecl::resolveInternal(NodeAssembler& as) const
{
    SymbolList sl = as.emptySymbolList();

    for (ASTNode* p = parameters; p; p = p->next)
    {
        if (const ParameterVariable* v =
            as.evalSymbolicExpression<ParameterVariable>(p->resolve(as)))
        {
            sl.push_back((Symbol*)v);
        }
        else
        {
            as.removeSymbolList(sl);
            return errorReturn(as, "Bad parameter declaration");
        }
    }

    string fname = "__lambda";

    if (RefIdentifier* idnode = dynamic_cast<RefIdentifier*>(name))
    {
        fname = idnode->name.c_str();
    }

    const Type* rtype = 0;

    if (!(rtype = as.evalSymbolicExpression<Type>(returnType->resolve(as))))
    {
        as.removeSymbolList(sl);
        return errorReturn(as, "Bad type expression");
    }

    Function* F = as.declareFunction(fname.c_str(), 
                                     rtype, 
                                     sl, 
                                     Mu::Function::ContextDependent);
    as.removeSymbolList(sl);
    as.declareFunctionBody(F, resolveSymbolConstant(as, body->resolve(as)));
    return as.functionConstant(F);
}

void
FunctionDecl::print(ostream& o) const
{
    o << "function: ";
    name->print(o);
    o << " (";
    returnType->print(o);
    o << "; ";
    parameters->printList(o);
    o << ") ";
    body->print(o);
}

void 
FunctionDecl::printAnnotated(ostream& o) const
{
    o << "FunctionDecl(";
    if (name) name->printAnnotated(o);
    else o << "lambda";
    o << ", ";
    returnType->printAnnotated(o);
    o << ", ";
    parameters->printListAnnotated(o);
    o << ", ";
    body->printAnnotated(o);
    o << ")";
}


//----------------------------------------------------------------------

Node* 
ModuleDecl::resolveInternal(NodeAssembler& as) const
{
    Name n;

    if (RefIdentifier* namenode = dynamic_cast<RefIdentifier*>(name))
    {
        n = namenode->name;
    }

    const Module* module = 0;

    if (const Symbol* s = as.findSymbolInScope(n))
    {
        module = dynamic_cast<const Module*>(s);
    }

    if (module) 
    {
        as.pushScope((Symbol*)module);
    }
    else 
    {
        as.pushModuleScope(n);
    }

    as.newStackFrame();

    Node* node = body ? body->resolve(as) : 0;

    as.endStackFrame();
    as.popScope();
    return node;
}

void 
ModuleDecl::print(ostream& o) const
{
    o << "module: ";
    name->print(o);
    o << " {";
    if (body) body->print(o);
    o << " }";
}

void 
ModuleDecl::printAnnotated(ostream& o) const
{
    o << "ModuleDecl(";
    name->printAnnotated(o);

    if (body) 
    {
        o << ", ";
        body->printAnnotated(o);
    }

    o << ")";
}

//----------------------------------------------------------------------

void
TypeIdentifier::print(ostream& o) const
{
    o << name;
}

void
TypeIdentifier::printAnnotated(ostream& o) const
{
    o << "*\"" << name << "\"";
}

Node* 
TypeIdentifier::resolveInternal(NodeAssembler& as) const
{
    if (const Symbol* s = as.findSymbolInScope(name))
    {
        for (s = s->firstOverload(); s; s = s->nextOverload())
        {
            if (const Type* t = dynamic_cast<const Type*>(s))
            {
                return as.typeSymbolConstant(t);
            }
        }
    }

    return errorReturn(as, "Unknown type identifier");
}

//----------------------------------------------------------------------

void
TupleType::print(ostream& o) const
{
    o << "(";
    components->printList(o);
    o << ")";
}

void
TupleType::printAnnotated(ostream& o) const
{
    o << "TupleType(";
    components->printListAnnotated(o);
    o << ")";
}

Node* 
TupleType::resolveInternal(NodeAssembler& as) const
{
    MuLangContext* c = static_cast<MuLangContext*>(as.context());
    NodeList nl = as.emptyNodeList();

    for (ASTNode* a = components; a; a = a->next)
    {
        if (Node* texpr = a->resolve(as))
        {
            nl.push_back(texpr);
        }
        else
        {
            as.removeNodeList(nl);
            return errorReturn(as, "Bad tuple component");
        }
    }

    Node* lnode = as.listNode(nl);
    as.removeNodeList(nl);

    nl = as.newNodeList(lnode);
    Name n = c->internName("make_tuple_type");
    Node* node = as.callFunction(static_cast<const Function*>(c->runtimeModule()->findSymbol(n)), nl);
    as.removeNodeList(nl);

    return node;
}

//----------------------------------------------------------------------

void
ListType::print(ostream& o) const
{
    o << "[";
    elementType->print(o);
    o << "]";
}

void
ListType::printAnnotated(ostream& o) const
{
    o << "ListType(";
    elementType->printAnnotated(o);
    o << ")";
}

Node* 
ListType::resolveInternal(NodeAssembler& as) const
{
    MuLangContext* c = static_cast<MuLangContext*>(as.context());
    NodeList nl = as.emptyNodeList();

    if (Node* texpr = elementType->resolve(as))
    {
        nl.push_back(texpr);
    }
    else
    {
        as.removeNodeList(nl);
        return errorReturn(as, "Bad list component");
    }

    Name n = c->internName("make_list_type");
    Node* node = as.callFunction(static_cast<const Function*>(c->runtimeModule()->findSymbol(n)), nl);
    as.removeNodeList(nl);

    return node;
}

//----------------------------------------------------------------------

void
FuncType::print(ostream& o) const
{
    o << "(";
    returnType->print(o);
    o << ";";
    argTypes->printList(o);
    o << ")";
}

void
FuncType::printAnnotated(ostream& o) const
{
    o << "FuncType(";
    returnType->printAnnotated(o);
    o << "; ";
    argTypes->printListAnnotated(o);
    o << ")";
}

Node* 
FuncType::resolveInternal(NodeAssembler& as) const
{
    MuLangContext* c = static_cast<MuLangContext*>(as.context());
    NodeList nl = as.emptyNodeList();

    if (Node* texpr = returnType->resolve(as))
    {
        nl.push_back(texpr);
    }
    else
    {
        as.removeNodeList(nl);
        return errorReturn(as, "Bad return type expression");
    }

    NodeList anl = as.emptyNodeList();

    for (ASTNode* a = argTypes; a; a = a->next)
    {
        if (Node* texpr = a->resolve(as))
        {
            anl.push_back(texpr);
        }
        else
        {
            as.removeNodeList(anl);
            return errorReturn(as, "Bad argument");
        }
    }

    Node* lnode = as.listNode(anl);
    as.removeNodeList(anl);
    nl.push_back(lnode);

    Name n = c->internName("make_function_type");
    Node* node = as.callFunction(static_cast<const Function*>(c->runtimeModule()->findSymbol(n)), nl);
    as.removeNodeList(nl);

    return node;
}

//----------------------------------------------------------------------

Node*
FixedArrayType::resolveInternal(NodeAssembler& as) const
{
    MuLangContext* c = static_cast<MuLangContext*>(as.context());
    NodeList nl = as.emptyNodeList();

    if (Node* texpr = elementType->resolve(as))
    {
        nl.push_back(texpr);
    }

    MuLangContext::SizeVector sizes;
    NodeList anl = as.emptyNodeList();

    for (ASTNode* d = dimensions; d; d = d->next)
    {
        anl.push_back(d->resolve(as));
    }

    Node* lnode = as.listNode(anl);
    as.removeNodeList(anl);
    nl.push_back(lnode);

    Name n = c->internName("make_fixed_array_type");
    Node* node = as.callFunction(static_cast<const Function*>(c->runtimeModule()->findSymbol(n)), nl);
    as.removeNodeList(nl);

    return node;
}

void
FixedArrayType::print(ostream& o) const
{
    elementType->print(o);
    o << "[";
    
    for (ASTNode* d = dimensions; d; d = d->next)
    {
        if (d != dimensions) o << ", ";
        d->print(o);
    }

    o << "]";
}

void
FixedArrayType::printAnnotated(ostream& o) const
{
    o << "FixedArrayType(";
    elementType->printAnnotated(o);
    o << ", ";
    
    for (ASTNode* d = dimensions; d; d = d->next)
    {
        if (d != dimensions) o << ", ";
        d->print(o);
    }

    o << ")";
}

//----------------------------------------------------------------------

Node*
DynamicArrayType::resolveInternal(NodeAssembler& as) const
{
    MuLangContext* c = static_cast<MuLangContext*>(as.context());
    NodeList nl = as.emptyNodeList();

    if (Node* texpr = elementType->resolve(as))
    {
        nl.push_back(texpr);
    }

    Name n = c->internName("make_dynamic_array_type");
    Node* node = as.callFunction(static_cast<const Function*>(c->runtimeModule()->findSymbol(n)), nl);
    as.removeNodeList(nl);

    return node;
}

void
DynamicArrayType::print(ostream& o) const
{
    elementType->print(o);
    o << "[";
    
    //for (ASTNode* d = dimensions; d; d = d->next)
    //{
        //if (d != dimensions) o << ", ";
        //d->print(o);
    //}

    o << "]";
}

void
DynamicArrayType::printAnnotated(ostream& o) const
{
    o << "DynamicArrayType(";
    elementType->printAnnotated(o);
    //o << ", ";
    
    //for (ASTNode* d = dimensions; d; d = d->next)
    //{
        //if (d != dimensions) o << ", ";
        //d->print(o);
    //}

    o << ")";
}

//----------------------------------------------------------------------


void 
FieldDecl::print(std::ostream& o) const
{
}

void 
FieldDecl::printAnnotated(std::ostream& o) const
{
}

Node* 
FieldDecl::resolveInternal(NodeAssembler& as) const
{
    return as.callBestOverloadedFunction(as.context()->noop(), as.emptyNodeList());
}

void 
RecordTypeDecl::print(std::ostream& o) const
{
}

void 
RecordTypeDecl::printAnnotated(std::ostream& o) const
{
}

Node* 
RecordTypeDecl::resolveInternal(NodeAssembler& as) const
{
    return as.callBestOverloadedFunction(as.context()->noop(), as.emptyNodeList());
}

void 
ClassTypeDecl::print(std::ostream& o) const
{
}

void 
ClassTypeDecl::printAnnotated(std::ostream& o) const
{
}

Node* 
ClassTypeDecl::resolveInternal(NodeAssembler& as) const
{
    return as.callBestOverloadedFunction(as.context()->noop(), as.emptyNodeList());
}


} // AST
} // Mu
