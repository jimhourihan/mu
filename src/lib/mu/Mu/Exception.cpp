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

#include <Mu/Exception.h>
#include <Mu/Thread.h>
#include <Mu/ParameterVariable.h>
#include <sstream>

namespace Mu {
using namespace std;

Exception::Exception(const char* m, Object* o) throw() 
    : std::exception(), 
      _message(m), 
      _object(o) 
{
}

Exception::Exception(Thread& thread, const char* m, Object* o) throw() 
    : std::exception(),
      _message(m),
      _object(o) 
{
    thread.backtrace(_backtrace);
}

Exception::~Exception() throw() {}

const char *
Exception::what() const throw() 
{ 
    return _message.c_str(); 
}

String
Exception::backtraceAsString() const
{
    return backtraceAsString(_backtrace);
}

String
Exception::backtraceAsString(const BackTrace& bt)
{
    ostringstream cstr;

    int stackcount = 0;

    if (bt.empty())
    {
        cstr << "no backtrace available";
    }

    for (int i=0; i < bt.size() ; i++)
    {
        const Node* n = bt[i].node;
        const Symbol* s = bt[i].symbol;
        const Function* f = dynamic_cast<const Function*>(s);

        if (bt[i].filename && *bt[i].filename && bt[i].linenum)
        {
            cstr << bt[i].filename 
                 << ", line " << bt[i].linenum 
                 << ", char " << bt[i].charnum
                 << ":"
                 << endl;
        }

        if (i < 100) cstr << " ";
        if (i < 10) cstr << " ";
        cstr << i << ": ";

        s->outputNode(cstr, n);

        cstr << endl;

        string sname = s->name();
        if (sname.size() > 2 && sname[0] == '_' && sname[1] == '_') continue;

        if (f && f->returnType()->isTypePattern())
        {
            cstr << "    returns: " << n->type()->fullyQualifiedName() << endl;
        }

        for (int q=0, s=n->numArgs(); q < s; q++)
        {
            const Node* p = n->argNode(q);
            cstr << "     ";
            if (q < 10) cstr << " ";
            cstr << q << ": ";

            cstr << p->type()->fullyQualifiedName() << " ";

            if (f && f->hasParameters())
            {
                cstr << f->parameter(q)->name() << " ";
            }
            
            if (const Type* t = dynamic_cast<const Type*>(p->symbol()))
            {
                DataNode* dn = (DataNode*)p;
                cstr << "=> constant ";
                t->outputValue(cstr, dn->_data);
            }

            cstr << endl;
        }
    }

    string temp = cstr.str();
    return String(temp.c_str());
}

} // namespace Mu
