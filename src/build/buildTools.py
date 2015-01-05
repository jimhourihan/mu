#
#  Copyright (c) 2001, Tweak Films
#  Copyright (c) 2008, Tweak Software
# 
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:
#
#     * Redistributions of source code must retain the above
#       copyright notice, this list of conditions and the following
#       disclaimer.
#
#     * Redistributions in binary form must reproduce the above
#       copyright notice, this list of conditions and the following
#       disclaimer in the documentation and/or other materials
#       provided with the distribution.
#
#     * Neither the name of the Tweak Software nor the names of its
#       contributors may be used to endorse or promote products
#       derived from this software without specific prior written
#       permission.
# 
#  THIS SOFTWARE IS PROVIDED BY Tweak Software ''AS IS'' AND ANY EXPRESS
#  OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
#  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
#  ARE DISCLAIMED. IN NO EVENT SHALL Tweak Software BE LIABLE FOR
#  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
#  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
#  OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
#  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
#  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
#  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
#  DAMAGE.
#
# This module is used to communicate with the Makefiles. It will set up a
# database for a given project automatically.
#

import os
import os.path
import string
import sys
import re
import pickle

verbose = 1

def info(message):
    if verbose == 1:
        print "INFO:", message
        sys.stdout.flush();

def error(message):
    print "ERROR:", message
    sys.stdout.flush();

def warning(message):
    if verbose == 1:
        print "WARNING:", message
        sys.stdout.flush();

rePROJECT      = re.compile("^include.*build/Makefile.master$")
rePACKAGE      = re.compile("^include.*build/Makefile.packages$")
rePACKAGETYPE  = re.compile("^PACKAGE.*=.*$")
reEXTRAINSTALL = re.compile("^extra_install:$")

def isProjectDirectory(path):
    f = file(path + "/Makefile", "r")
    for line in f:
        if rePACKAGE.match(line) or rePACKAGETYPE.match(line):
            return False
        elif rePROJECT.match(line):
            return True
    return False

def isPackageDirectory(path):
    f = file(path + "/Makefile", "r")
    for line in f:
        if rePACKAGE.match(line) or rePACKAGETYPE.match(line):
            return True
    return False

def hasExtraInstall(path):
    f = file(path + "/Makefile", "r")
    for line in f:
        if reEXTRAINSTALL.match(line):
            return True
    return False

class SourceTree:

    def __init__(self):
        self.nodeDictionary = {}
        self.bin = None

    def findAllProjects(self):

        if self.bin != None:
            return

        info("Searching source tree")

        self.src      = os.getenv("SRC_ROOT")
        self.binRE    = re.compile(self.src + "/+bin/[^/]+/[^/]+$")
        self.libRE    = re.compile(self.src + "/+lib/[^/]+/[^/]+$")
        self.pubRE    = re.compile(self.src + "/+pub/[^/]+$")
        self.plugRE   = re.compile(self.src + "/+plugins/[^/]+/[^/]+$")
        self.pyRE     = re.compile(self.src + "/+python/[^/]+/[^/]+$")
        self.scriptRE = re.compile(self.src + "/+scripts/[^/]+/[^/]+$")
        self.bin      = []
        self.lib      = []
        self.pub      = []
        self.python   = []
        self.scripts  = []
        self.plugins  = []

        for root, dirs, files in os.walk(self.src):
            if os.path.basename(root) != "CVS":
                if "Makefile" in files:
                    if "CVS" in dirs:
                        dirs.remove("CVS")

                    e = [root, dirs, files, None]

                    if self.binRE.match(root) != None:
                        self.bin.append(e)
                    elif self.libRE.match(root) != None:
                        self.lib.append(e)
                    elif self.pubRE.match(root) != None:
                        self.pub.append(e)
                    elif self.plugRE.match(root) != None:
                        self.plugins.append(e)
                    elif self.pyRE.match(root) != None:
                        self.python.append(e)
                    elif self.scriptRE.match(root) != None:
                        self.scripts.append(e)


    def loadAllProjects(self):
        "findAllProjects() should be called before this function."

        info("Loading all projects")
        all = []
        all.extend(self.bin)
        all.extend(self.lib)
        all.extend(self.pub)
        all.extend(self.plugins)
        all.extend(self.python)
        all.extend(self.scripts)
        self.loadProjects(all)

    def locateProjectsByRegexAndLoad(self, projects):

        rval = []
        all = []
        all.extend(self.bin)
        all.extend(self.lib)
        all.extend(self.pub)
        all.extend(self.plugins)

        res = []
        for i in projects:
            if len(i) > 0: 
                if i[-1] != '$':
                    i += '$'
                if i[0] != '/':
                    i = "/%s" % i
                res.append(re.compile(i))

        for r in res:
            for t in all:
                if r.search(t[0]) != None:
                    rval.append(t)

        if len(rval) != 0:
            self.loadProjects(rval)

        return rval

    def loadProjects(self, projects):
        """Load a list of project directories as Projects. The fourth
        list element is filled in"""

        for p in projects:
            if isProjectDirectory(p[0]) == True:
                p[3] = Project()
                p[3].loadProjectInfo(p[0])
                p[3].loadProjectDAG()
            else:
                warning("%s is not a project directory" % p[0])


sourceTree = SourceTree()

class Package:

    def __init__(self, pathToMakefile):

        sourceTree.findAllProjects()

        #
        # Open a pipe to make and get the configuration information from
        # the Makefiles
        #

        p = os.popen("make --no-print-directory -C " + pathToMakefile + " package_info")

        #
        # Parse the information and set instance variables to the results.
        #

        line                    = p.readline()
        self.other              = {}
        self.path               = pathToMakefile
        self.binaries           = []
        self.extra_applications = []
        self.libraries          = []
        self.plugins            = []
        self.scripts            = []
        self.package            = ""
        self.type               = ""
        self.version            = ""

        while line:
            words = string.split(line)
            name  = words[0]
            del words[0]
            if len(words) == 0:
                words = [""]
            if name == "BINARIES":
                self.binaries = words
            if name == "APPLICATION":
                self.application = words
            if name == "EXTRA_APPLICATIONS":
                self.extra_applications = words
            if name == "LIBRARIES":
                self.libraries = words
            if name == "PLUGINS":
                self.plugins = words
            if name == "SCRIPTS":
                self.scripts = words
            if name == "PACKAGE":
                self.package, self.type, self.version = words
            else:
                self.other[name] = words
            line = p.readline()

        p.close()
        all = self.allProjects()
        self.targets = sourceTree.locateProjectsByRegexAndLoad(all)

    def allProjects(self):

        all = []
        all.extend(self.binaries)
        all.extend(self.application)
        all.extend(self.extra_applications)
        all.extend(self.libraries)
        all.extend(self.plugins)
        all.extend(self.scripts)
        return all

    def projectsInBuildOrder(self, includeSystemLibs=0):

        targets = []

        for i in self.targets:
            path    = i[0]
            project = i[3]
            deps    = project.projectsInBuildOrder()

            for d in deps:
                if not d in targets:
                    targets.append(d)

        return targets

    def rootProjects(self):

        targets = []

        for i in self.targets:
            project = i[3]
            if project != None:
                targets.append(project)

        return targets

class Project:

    def __init__(self):
        pass

    def loadProjectInfo(self, pathToMakefile):
        #
        # Open a pipe to make and get the configuration information from
        # the Makefiles
        #

        p = os.popen("make --no-print-directory -C " + pathToMakefile + " configure_info")

        #
        # Parse the information and set instance variables to the results.
        #

        line          = p.readline()
        self.other    = {}
        self.debugger = "gdb"
        self.modules  = []
        self.path     = pathToMakefile

        while line:
            words = string.split(line)
            name  = words[0]
            del words[0]
            if len(words) == 0:
                words = [""]
            if name == "COMPILER":
                self.compiler = words[0]
            if name == "DEBUGGER":
                self.debugger = words[0]
            elif name == "PLATFORM":
                self.platform = words[0]
            elif name == "ARCH":
                self.arch = words[0]
            elif name == "SRC_ROOT":
                self.src_root = words[0]
            elif name == "BUILD_ROOT":
                self.build_root = words[0]
            elif name == "MAKE_ROOT":
                self.make_root = words[0]
            elif name == "CVSROOT":
                self.cvsroot = words[0]
            elif name == "CVSREAD":
                self.cvsroot = words[0]
            else:
                self.other[name] = words
            line = p.readline()

        p.close()
        self.root = ProjectNode()
        self.name = "ROOT PROJECT"
        self.root.loadProject(self, self.path)
        self.root.loadModules(self)

    def loadProjectDAG(self):
        self.root.loadLibs()
        for p in self.modules:
            p.loadLibs()

    def makeCurrentProjectLast(self, projects, currentProjectPath='.'):
        "Return projects in build order with current project last"
        finalProjectList = []
        buildCurrentProjectLast = False
        currentProject = Project()
        for p in projects:
                if p.path == currentProjectPath:
                    buildCurrentProjectLast = True
                    currentProject = p
                else:
                    finalProjectList.append(p)

        if buildCurrentProjectLast:
            finalProjectList.append(currentProject)

        return finalProjectList

    def projectsInBuildOrder(self, includeSystemLibs=0):
        "Return projects in build order"
        projects = []
        self.root.depthFirstSortProjects(projects, includeSystemLibs)
        for p in self.modules:
            p.depthFirstSortProjects(projects, includeSystemLibs)
        return self.makeCurrentProjectLast(projects)

    def loadProjectFlags(self):
        "Load the combined CXXFLAGS, CFLAGS, MCCFLAGS, etc"
        p = os.popen("make --no-print-directory -C " + self.path + " flag_info")
        self.flags = {}
        line = p.readline()

        while line:
            words = string.split(line)
            name  = words[0]
            del words[0]
            if len(words) == 0:
                words = [""]
            else:
                self.flags[name] = words
            line = p.readline()
        p.close()

class ProjectNode:

    def __init__(self):
        self.usedByProjects    = []
        self.builtFromProjects = []
        self.name              = "UNNAMED PROJECT"
        self.type              = "UNTYPED PROJECT"
        self.projectPaths      = []
        self.libs              = []

    def makeSystemProject(self, project, name):
        "Force this project to be representative of a system component"
        self.systemLib    = 1
        self.name         = name
        self.project      = project
        self.path         = ""
        self.type         = "SYSTEM"
        self.projectPaths = ['']

    def loadProject(self, project, pathToMakefile):
        "Load information about this project from Makefile"
        #if pathToMakefile[len(pathToMakefile)-1] != '/':
        #    pathToMakefile += '/'

        #
        # Open a pipe to make and get the project info
        #

        p = os.popen("make --no-print-directory -C " + pathToMakefile + " project_info")

        #
        # Parse and set instance variables
        #

        line             = p.readline()
        self.project     = project
        self.other       = {}
        self.path        = pathToMakefile
        self.systemLib   = 0
        self.modules     = []
        self.modulePaths = []
        self.libs        = []
        self.type        = ""
        self.target      = None
        self.projectPaths= []
        self.mocgenfiles = []
        self.qrcgenfiles = []
        self.qtresources = []
        self.genfiles    = []
        self.frameworks  = []

        while line:
            words = string.split(line)
            name  = words[0]
            del words[0]
            if len(words) == 0:
                words = [""]
            if name == "PROJECT":
                self.name = words[0]
            elif name == "TYPE":
                self.type = words[0]
            elif name == "TARGET":
                self.target = words[0]
            elif name == "TARGETBIN":
                self.target_bin = words[0]
            elif name == "OBJDIR":
                self.objdir = words[0]
            elif name == "PROJECTPATHS":
                self.projectPaths = words
            elif name == "LIBS":
                self.libs = words
            elif name == "MODULES":
                self.modules = words
            elif name == "MODULEPATHS":
                self.modulePaths = words
            elif name == "FRAMEWORKS":
                self.frameworks = words
            elif name == "IPATH":
                self.ipath = words
            elif name == "LPATH":
                self.lpath = words
            elif name == "SRCS":
                self.srcs = words
            elif name == "EXPORTED":
                self.exported = words
            elif name == "GENFILES":
                self.genfiles = words
            elif name == "MOCGENFILES":
                self.mocgenfiles = words
            elif name == "QRCGENFILES":
                self.qrcgenfiles = words
            elif name == "QTRESOURCES":
                self.qtresources = words
            elif name == "DEPFILES":
                self.depfiles = words
            elif name == "EXISTINGLIBS":
                self.existinglibs = words
            elif name == "LINK_TYPE":
                self.linktype = words
            elif name == "QT_TYPE":
                self.qttype = words
            else:
                self.other[name] = words
            line = p.readline()
        p.close()

        if self.name == "UNNAMED PROJECT":
            error("*** Check Makefile at %s" % pathToMakefile)
        info("Loaded " + self.name + " " + self.type + " project")
        sourceTree.nodeDictionary[self.name] = self;

    def loadModules(self, project):
        "Load projects for all modules"
        paths = self.modulePaths

        if (paths == ['']):
            return
        
        for mp in paths:
            p = ProjectNode() 
            p.loadProject(self.project, mp)
            project.modules.append(p)

    def loadLibs(self):
        "Recursively load all projects on which this depends"
        paths = self.projectPaths + self.modulePaths

        if paths == ['']:
            return

        libs      = self.libs + self.modules + self.frameworks
        srclibs   = []
        basepaths = []

        #
        # List of libs in the source tree is created by examining the
        # paths that the Makefile is using.
        #
        
        for path in paths:
            basepaths.append(os.path.basename(path))

        #
        # Catagorize the libs into system, source, or prebuilt
        #

        for lib in libs:
            if sourceTree.nodeDictionary.has_key(lib):
                #
                # Already cached this project. Hook us up.
                #
                p = sourceTree.nodeDictionary[lib]
                p.usedByProjects.append(self)
                self.builtFromProjects.append(p)
            elif lib != "":
                if lib in basepaths:
                    #
                    #  This lib is the source tree
                    #
                    p = ProjectNode() 
                    p.systemLib = 0
                    pathToLib = 0
                    for path in paths:
                        if os.path.basename(path) == lib:
                            pathToLib = path
                    p.loadProject(self.project,pathToLib)
                    p.loadLibs()
                    p.usedByProjects.append(self)
                    self.builtFromProjects.append(p)
                else:
                    #
                    # This lib is not in the source tree
                    #
                    p = ProjectNode() 
                    p.makeSystemProject(self.project,lib)
                    p.usedByProjects.append(self)
                    self.builtFromProjects.append(p)
                    info("Loaded " + lib + " SYSTEM component")

    def depthFirstSortProjects(self, projects, includeSystemLibs=0):
        for p in self.builtFromProjects:
            if p != self:
                p.depthFirstSortProjects(projects, includeSystemLibs)

        # is there a better way to find an element?
        if not self in projects:
            if includeSystemLibs == 0 and self.systemLib == 1:
                pass
            else:
                projects.append(self)


cachingEnabled = os.getenv("BUILD_CACHING", "FALSE") == "TRUE"
build_root     = os.getenv("BUILD_ROOT", "")

def loadCachedProjectInfo(force = False):

    global cachingEnabled
    global build_root

    if not cachingEnabled:
        p = Project()
        p.loadProjectInfo(".")
        return p

    pfilename = ".cached_project_info.p"
    pexists = os.path.exists(pfilename)
    mtime = os.path.getmtime("Makefile")
    ptime = 0

    if pexists:
        ptime = os.path.getmtime(pfilename)
    else:
        ptime = mtime - 1

    if ptime > mtime and not force:
        pfile = open(pfilename, "rb")
        p = pickle.load(pfile)
        pfile.close()

        if build_root != p.build_root:
            info("cached project info needs to be updated")
            return loadCachedProjectInfo(True)

        return p
    else:
        p = Project()
        p.loadProjectInfo(".")
        pfile = open(pfilename, "wb")
        pickle.dump(p, pfile)
        pfile.close()
        return p


def loadCachedProjectDAG(force = False):

    global build_root
    global cachingEnabled

    if not cachingEnabled:
        p = Project()
        p.loadProjectInfo(".")
        p.loadProjectDAG()
        return p

    pfilename = ".cached_project_dag.p"
    pexists = os.path.exists(pfilename)
    mtime = os.path.getmtime("Makefile")
    ptime = 0

    if pexists:
        ptime = os.path.getmtime(pfilename)
    else:
        ptime = mtime - 1

    if ptime > mtime and not force:
        pfile = open(pfilename, "rb")
        p = pickle.load(pfile)
        pfile.close()
        info("loaded DAG from cache")

        if build_root != p.build_root:
            info("cached DAG needs to be updated")
            return loadCachedProjectDAG(True)

        for n in p.projectsInBuildOrder():
            makefile = os.path.join(n.path, "Makefile")
            if os.path.getmtime(makefile) > ptime:
                info("cached DAG data needs to be updated")
                return loadCachedProjectDAG(True)

        return p
    else:
        info("DAG cache is out of date")
        p = loadCachedProjectInfo()
        p.loadProjectDAG()
        pfile = open(pfilename, "wb")
        pickle.dump(p, pfile)
        pfile.close()
        return p
