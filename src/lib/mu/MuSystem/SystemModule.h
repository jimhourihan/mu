#ifndef __runtime__SystemModule__h__
#define __runtime__SystemModule__h__
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
#include <Mu/Module.h>
#include <Mu/Node.h>

namespace Mu {

class SystemModule : public Module
{
  public:
    SystemModule(Context* c, const char *name);
    virtual ~SystemModule();

    virtual void load();

    static Module* init(const char* name, Context*);

    static NODE_DECLARATION(getenv, Pointer);
    static NODE_DECLARATION(getenv2, Pointer);
    static NODE_DECLARATION(getenv3, Pointer);
    static NODE_DECLARATION(unsetenv, void);
    static NODE_DECLARATION(putenv, void);
    static NODE_DECLARATION(setenv, void);
    static NODE_DECLARATION(getcwd, Pointer);
    static NODE_DECLARATION(ctermid, Pointer);
    static NODE_DECLARATION(chdir, void);

    static NODE_DECLARATION(getuid, int);
    static NODE_DECLARATION(geteuid, int);
    static NODE_DECLARATION(getgid, int);
    static NODE_DECLARATION(getegid, int);
    static NODE_DECLARATION(getpid, int);
    static NODE_DECLARATION(getppid, int);
    static NODE_DECLARATION(getpgid, int);
    static NODE_DECLARATION(getpgrp, int);

    static NODE_DECLARATION(setuid, void);
    static NODE_DECLARATION(seteuid, void);
    static NODE_DECLARATION(setgid, void);
    static NODE_DECLARATION(setegid, void);
    static NODE_DECLARATION(setsid, int);
    static NODE_DECLARATION(setpgid, void);
    //static NODE_DECLARATION(setpgrp, void);
    static NODE_DECLARATION(setreuid, void);
    static NODE_DECLARATION(setregid, void);
    //static NODE_DECLARATION(issetugid, bool);

    static NODE_DECLARATION(umask, int);
    static NODE_DECLARATION(chmod, void);
    static NODE_DECLARATION(mkdir, void);
    static NODE_DECLARATION(mkfifo, void);
    static NODE_DECLARATION(mknod, void);
    static NODE_DECLARATION(readlink, Pointer);

    static NODE_DECLARATION(fork, int);
    static NODE_DECLARATION(exec, void);
    static NODE_DECLARATION(system, int);
    static NODE_DECLARATION(wait, Pointer);
    static NODE_DECLARATION(waitpid, Pointer);

    static NODE_DECLARATION(defaultWindowsOpen, int);

    static NODE_DECLARATION(wifexited, bool);
    static NODE_DECLARATION(wifsignaled, bool);
    static NODE_DECLARATION(wifstopped, bool);
    static NODE_DECLARATION(wcoredump, bool);
    static NODE_DECLARATION(wexitstatus, int);
    static NODE_DECLARATION(wtermsig, int);
    static NODE_DECLARATION(wstopsig, int);

    static NODE_DECLARATION(_exit, void);
    static NODE_DECLARATION(exit, void);
    static NODE_DECLARATION(kill, void);

    static NODE_DECLARATION(getdtablesize, int);
    static NODE_DECLARATION(fcntl, int);
    static NODE_DECLARATION(flock, int);
    static NODE_DECLARATION(pipe, Pointer);
    static NODE_DECLARATION(open, int);
    static NODE_DECLARATION(close, void);
    static NODE_DECLARATION(system2, Pointer);
    static NODE_DECLARATION(dup, int);
    static NODE_DECLARATION(dup2, int);
    static NODE_DECLARATION(read, int);
    static NODE_DECLARATION(write, int);
    static NODE_DECLARATION(lseek, int);
    static NODE_DECLARATION(link, void);
    static NODE_DECLARATION(unlink, void);
    static NODE_DECLARATION(ioctl, void);
    static NODE_DECLARATION(stat, Pointer);
    static NODE_DECLARATION(s_isblk, bool);
    static NODE_DECLARATION(s_ischr, bool);
    static NODE_DECLARATION(s_isdir, bool);
    static NODE_DECLARATION(s_isfifo, bool);
    static NODE_DECLARATION(s_isreg, bool);
    static NODE_DECLARATION(s_islnk, bool);
    static NODE_DECLARATION(s_issock, bool);

    static NODE_DECLARATION(socket, int);

    static NODE_DECLARATION(fopen, Pointer);
    static NODE_DECLARATION(fdopen, Pointer);
    static NODE_DECLARATION(freopen, Pointer);
    static NODE_DECLARATION(fclose, void);
    static NODE_DECLARATION(clearerr, void);
    static NODE_DECLARATION(feof, bool);
    static NODE_DECLARATION(ferror, bool);
    static NODE_DECLARATION(fileno, int);

    static NODE_DECLARATION(time, int64);
    static NODE_DECLARATION(gettimeofday, Pointer);
};

} // namespace Mu

#endif // __runtime__SystemModule__h__
