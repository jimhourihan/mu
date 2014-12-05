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

#include "Environment.h"
#include "UTF8.h"

namespace Mu {
namespace Environment {
using namespace std;

struct EnvData
{
    MU_GC_NEW_DELETE
    String              _home;
    SearchPath          _modulePath;
    ProgramArguments    _programArgs;
};

static EnvData* env = 0;

static void 
init()
{
    if (env) return;
    env = new EnvData;

    const char *mp = getenv("MU_MODULE_PATH");
    const char *mh = getenv("MU_HOME");

#ifdef WIN32
    String modulePath = mp ? mp : ".";
    env->_home = mh ? mh : "";
    modulePath += ";" + env->_home;

    UTF8tokenize(env->_modulePath, modulePath, ";");
#else
    String modulePath = mp ? mp : ".";
    env->_home = mh ? mh : "";
    modulePath += ":" + env->_home;

    UTF8tokenize(env->_modulePath, modulePath, ":");
#endif
}

void 
pathComponents(const String& path, PathComponents& components)
{
    UTF8tokenize(components, path, "/");
}

void
setModulePath(const SearchPath& paths)
{
    if (!env) init();
    env->_modulePath = paths;
}

void 
setProgramArguments(const ProgramArguments& args)
{
    if (!env) init();
    env->_programArgs = args;
}

const String&
muHomeLocation()
{
    if (!env) init();
    return env->_home;
}

const SearchPath&
modulePath()
{
    if (!env) init();
    return env->_modulePath;
}

const ProgramArguments&
programArguments()
{
    if (!env) init();
    return env->_programArgs;
}

} // Environment
} // Mu
