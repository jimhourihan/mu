#!/usr/bin/env python
from sgmllib import SGMLParser
import urllib
import sys
import traceback
import pprint
import string
import re
import pickle
import os
from sets import Set

#
#   We need to at least use objectHTML and qtHTML as the roots for
#   recursiveParse() below. Other base classes may be generated as
#   well.
#

showit = False

pp = pprint.PrettyPrinter()

htmlDir                  = "/Volumes/corn_10dot5/Developer/Documentation/Qt/html/"
objectHTML               = "%s/qobject.html" % htmlDir
qtHTML                   = "%s/qt.html" % htmlDir
qtapifile                = "qt45api.p"
templateObjectH          = "templates/TemplateObjectType.h"
templateObjectCPP        = "templates/TemplateObjectType.cpp"
templateTypeH            = "templates/TemplateType.h"
templateTypeCPP          = "templates/TemplateType.cpp"
templatePointerTypeH     = "templates/TemplatePointerType.h"
templatePointerTypeCPP   = "templates/TemplatePointerType.cpp"
templateInterfaceTypeH   = "templates/TemplateInterfaceType.h"
templateInterfaceTypeCPP = "templates/TemplateInterfaceType.cpp"

#
#   Setting this to true causes the library to be generated with
#   unique subclasses for every Qt class. This allows inheritance from
#   Mu.
#

allowInheritance = False

#
# base class html files: these are recursively scanned
#

baseHTML    = ["qt", "qobject" , "qfont", "qsize", "qpoint", "qrect", "qicon",
               "qvariant", "qstandarditem", "qmodelindex", "qpixmap",
               "qregion", "qcolor", "qlistwidgetitem", "qtreewidgetitem", 
               "qtablewidgetitem", "qurl", "qbytearray", "qlayoutitem",
               "qpaintdevice", "qhostaddress", "qhostinfo", "qtimer", 
               "qdesktopservices", "qdir", "qfileinfo", "qdatastream",
               "qitemselectionrange", "qitemselection", "qgradient",
               "qbrush", "qmatrix", "qtransform", "qpointf", "qpalette"]

#
#   These classes use the standard Mu ClassInstance to hold their data
#   and have the indicated data members. The primitiveTypes actually
#   embed the data type in the Instance object. The pointerTypes use a
#   named field to hold the native object.
#

primitiveTypes  = Set(["QSize", "QRect", "QPoint", "QPointF", "QIcon", "QPixmap", 
                       "QBitmap", "QColor", "QVariant", "QRegion", "QImage",
                       "QModelIndex", "QFont", "QUrl", "QByteArray", "QDataStream",
                       "QHostAddress", "QHostInfo", "QDir", "QFileInfo",
                       "QItemSelectionRange", "QItemSelection", "QBrush", "QGradient",
                       "QMatrix", "QTransform", "QConicalGradient", "QLinearGradient", 
                       "QRadialGradient", "QPalette"])

interfaceTypes = Set(["QLayoutItem", "QPaintDevice"])

pointerTypes = Set(["QStandardItem", "QListWidgetItem", "QTreeWidgetItem", 
                    "QTableWidgetItem", "QLayoutItem", "QPaintDevice"])

def isAPrimitiveType(name):
    return name in primitiveTypes

def isAPointerType(name):
    return name in pointerTypes

#
#   C++ things which modify the meat of class name
#

typeElaborations = ["const", "virtual", "*", "&"]

#
#   Map from C++ types to Mu types. Additional elements are added
#   during parsing. 
#

translationMap = {
    "void"                      : "void",
    "int"                       : "int",
    "uint"                      : "int",
    "bool"                      : "bool",
    "double"                    : "double",
    "qreal"                     : "double",
    "qint64"                    : "int64",
    "QString"                   : "string",
    "QStringList"               : "string[]",
    "QModelIndexList"           : "qt.QModelIndex[]",
    "QRgb"                      : "int",
    "QKeySequence"              : "string",
    "QList<QTreeWidgetItem *>"  : "qt.QTreeWidgetItem[]",
    "QList<QListWidgetItem *>"  : "qt.QListWidgetItem[]",
    "QList<QTableWidgetItem *>" : "qt.QTableWidgetItem[]",
    "QList<QStandardItem *>"    : "qt.QStandardItem[]",
    #"const QSizeF &"            : "qt.QSizeF",
    #"const QPointF &"           : "qt.QPointF",
    #"const QLineF &"            : "qt.QLineF",
    #"const QRectF &"            : "qt.QRectF",
    #"const QRegExp &"           : "qt.QRegExp",
    #"const QLine &"             : "qt.QLine",
    #"const QDate &"             : "qt.QDate",
    #"const QTime &"             : "qt.QTime",
}

#
#   Map from Mu type (in regex form) to Mu machine representation. The
#   tuple value contains (rep * more specific type) in case it matters.
#
#   NOTE: the order here matters! They are test in order
#

repMap = [
    (re.compile("bool"), ("bool", "bool")),
    (re.compile("void"), ("void", "void")),
    (re.compile("int64"), ("int64", "int64")),
    (re.compile("int"), ("int", "int")),
    (re.compile("float"), ("float", "float")),
    (re.compile("double"), ("double", "double")),
    (re.compile("short"), ("short", "short")),
    (re.compile("byte"), ("byte", "byte")),
    (re.compile("char"), ("char", "char")),
    (re.compile("flags .*"), ("int", "int")),
    (re.compile("string"), ("Pointer", "StringType::String")),
    (re.compile("string\\[\\]"), ("Pointer", "DynamicArray")),
    (re.compile("qt.QTreeWidgetItem\\[\\]"), ("Pointer", "DynamicArray")),
    (re.compile("qt.QListWidgetItem\\[\\]"), ("Pointer", "DynamicArray")),
    (re.compile("qt.QTableWidgetItem\\[\\]"), ("Pointer", "DynamicArray")),
    (re.compile("qt.QStandardItem\\[\\]"), ("Pointer", "DynamicArray")),
    (re.compile(".*"), ("Pointer", "ClassInstance"))
]

def repMapFind(x):
    for (rexp, val) in repMap:
        if rexp.match(x):
            return val
    return None

convertFromMap = {
    "string"     : ("qstring($E)", "QString"),
    "string[]"   : ("qstringlist($E)", "QStringList"),
    "qt.QModelIndex[]"   : ("qmodelindexlist($E)", "QModelIndexList"),
    #"string"     : ("$E->c_str()", "const char *"),
    "qt.QObject" : ("object<$T>($E)", "$T*"),
    #"qt.QTreeWidgetItem[]" : ("qpointerlist<$T>($E)", "$T*"),
}

convertToMap = {
    "QString" : ("makestring(c,$E)", "string"),
    "QStringList" : ("makestringlist(c,$E)", "string[]"),
    "QModelIndexList" : ("makeqmodelindexlist(c,$E)", "qt.QModelIndex[]"),
    #"const char *" : ("$E->c_str()", "string"),
}

setMap = {
    #"const char *" : "$O->string() = $E",
}

includeClasses = Set([
    "QAbstractButton",        "QComboBox",        "QMenu",               "QToolBar",
    "QAbstractItemModel",     "QCompleter",       "QObject",             "QToolButton",
    "QAbstractListModel",     "QDial",            "QPixmap",             "QWebFrame",
    "QAbstractSlider",        "QDialog",          "QPushButton",         "QWebPage",
    "QAbstractTableModel",    "QDockWidget",      "QRadioButton",        "QWebView",
    "QActionGroup",           "QFrame",           "QWidget",             "QFileDialog",
    "QAction",                "QIcon",            "QSlider",             "QStandardItem",
    "QCheckBox",              "QLineEdit",        "QStandardItemModel",  "QBitmap",
    "QColorDialog",           "QMainWindow",      "QSvgWidget",          "QModelIndex",
    "QCoreApplication",       "QApplication",     "QUrl",                "QByteArray",
    "QMenuBar",               "QLabel",           "QPlainTextEdit",      "QProgressBar",
    "QScrollArea",            "QSpinBox",         "QSplitter",           "QStackedWidget",
    "QStatusBar",             "QTabBar",          "QTabWidget",          "QTextDocument",
    "QTextEdit",              "QToolBox",         "QWidgetAction",       "QAbstractSpinBox",
    "QAbstractScrollArea",    "QButtonGroup",     "QRect",               "QRegion",
    "QSize",                  "QPoint",           "QFont",               "QVariant",
    "QStandardItem",          "QColor",           "QTreeWidgetItem",     "QListWidgetItem",
    "QTableWidgetItem",       "QListWidget",      "QTableWidget",        "QTreeWidget",
    "QTableView",             "QListView",        "QTreeView",           "QAbstractItemView",
    "QColumnView",            "QHeaderView",      "QLayout",             "QBoxLayout",
    "QHBoxLayout",            "QVBoxLayout",      "QFormLayout",         "QGridLayout",
    "QLayoutItem",            "QPaintDevice",     "QImage",              "QInputDialog",
    "QNetworkAccessManager",  "QEventLoop",       "QGroupBox",           "QIODevice",
    "QProcess",               "QFile",            "QAbstractSocket",     "QDir",
    "QTcpSocket",             "QUdpSocket",       "QTcpServer",          "QHostAddress",
    "QHostInfo",              "QLocalSocket",     "QTimer",              "QDesktopWidget",
    "QFileInfo",              "QItemSelection",   "QItemSelectionRange", "QItemSelectionModel",
    "QGradient",              "QBrush",           "QMatrix",             "QTransform",
    "QConicalGradient",       "QLinearGradient",  "QRadialGradient",
    "QPointF",                "QPalette",

    #"QDesktopServices",
    #"QDataStream",

    "QString", # has to be here
    "QStringList",
    "QModelIndexList",
    "QList<QTreeWidgetItem *>",
    "QList<QListWidgetItem *>",
    "QList<QTableWidgetItem *>",
    "QList<QStandardItem *>",
    ])

abstractClasses = [
        re.compile("QAbstract.*"), 
        re.compile("QLayout"),
        re.compile("QIODevice"),
]

def isAbstract(name):
    for reg in abstractClasses:
        if reg.match(name):
            return True
    return False

#
#   Most enums should be handled by the metaObject system, however
#   there are some that are not declared like that. They should be
#   listed here.
#

forceEnumOutput = { 
    "QIODevice" : ["OpenModeFlag"],
    "QProcess" : ["ExitStatus", "ProcessChannel", "ProcessChannelMode", 
                  "ProcessError", "ProcessState"],
    "QAbstractSocket" : ["NetworkLayerProtocol", "SocketError", "SocketState",
                         "SocketType"],
    "QFile" : ["FileError", "MemoryMapFlags", "Permission"],
    "QLocalSocket" : ["LocalSocketError", "LocalSocketState"],
}

#
# These are mis labeled in Qt's header files. QDOC_PROPERTY is used in
# insteadof Q_PROPERTY. For these classes, translate the props as
# functions.
#
doProps = ["QInputDialog"]

noHFileOutput = [] #["QObject"]


exclusionMap = {
    "QWidget::hasEditFocus" : None,
    "QWidget::setEditFocus" : None,
    "QWidget::macQDHandle" : None,
    "QWidget::macCGHandle" : None,
    "QWidget::x11Info" : None,
    "QWidget::x11PictureHandle" : None,
    "QWidget::getContentsMargins" : None,
    "QWidget::setContentsMargins" : None,
    
    "QMenuBar::defaultAction" : None,
    "QMenuBar::setDefaultAction" : None,
    "QPlainTextEdit::extraSelections" : None,
    "QPlainTextEdit::setExtraSelections" : None,
    "QPixmap::handle" : None,
    "QPixmap::x11PictureHandle" : None,
    "QPixmap::HBitmapFormat" : None,
    "QPixmap::ShareMode" : None,
    "QRegion::setRects" : None,
    "QVariant::canConvert" : None,
    "QVariant::PointArray" : None,

    # these two are "shadowing" the constructor that takes an int 
    "QVariant::QVariant" : [('QVariant', '', [('color', 'Qt::GlobalColor', None)], '', False),
                            ('QVariant', '', [('type', 'QVariant::Type', None)], '', False) ],

    "QBrush::gradient" : None,

}

def isFunctionExcluded(qtnamespace, qtfunc):
    cppname = (qtnamespace.name + "::" + qtfunc[0])
    if cppname in exclusionMap:
        e = exclusionMap[cppname]
        if e == None:
            return True
        inname = str(qtfunc)
        for f in e:
            if inname == str(f):
                return True
        return False

#
#   For name mangling. This is taken directly from the Context.cpp
#   file in Mu. The names generated by this map/func are used by the
#   muc front end when compiling to C++
#

mangleMap = {
' ': "_", '.': "__", '~': "Tilde_", '`': "Tick_", '+': "Plus_", '-': "Minus_",
'!': "Bang_", '%': "PCent_", '@': "At_", '#': "Pound_", '$': "Dollar_", '^': "Caret_",
'&': "Amp_", '*': "Star_", '(': "BParen_", ')': "EParen_", '=': "EQ_", '{': "BCB_",
'}': "ECB_", '[': "BSB_", ']': "ESB_", '|': "Pipe_", '\\': "BSlash_", ':': "Colon_",
';': "SColon_", '"': "Quote_", '\'': "SQuote_", '<': "LT_", '>': "GT_", ',': "Comma_",
'?': "QMark_", '/': "Slash_"
}

def mangleName(name):
    out = ""
    for c in name:
        k = str(c)
        if mangleMap.has_key(k):
            out += mangleMap[k]
        else:
            out += k
    return out


def convertFrom(expr, ktype, atype):
    if convertFromMap.has_key(ktype):
        (s, o) = convertFromMap[ktype]
        return (string.replace(string.replace(s, "$E", expr), "$T", atype),
                string.replace(o, "$T", atype))
    elif ktype.startswith("flags "):
        ntype = atype.split()[-1]
        return ("(%s)(%s)" % (ntype, expr), ntype)
    elif ktype.split(".")[-1] in primitiveTypes:
        ptype = ktype.split(".")[-1]
        ntype = atype.split()[-1]
        return ("getqtype<%sType>(%s)" % (ptype, expr), ntype)
    elif ktype.split(".")[-1] in pointerTypes:
        ptype = ktype.split(".")[-1]
        ntype = atype
        return ("getqpointer<%sType>(%s)" % (ptype, expr), ntype)
    elif "[]" in ktype:
        # QList
        ptype = ktype.split(".")[-1][0:-2]
        ntype = atype
        return ("qpointerlist<%sType>(%s)" % (ptype, expr), ntype)
    else:
        return ("(%s)(%s)" % (atype, expr), atype)

def convertTo(expr, ktype):
    ktype = sstrip(string.replace(ktype, "virtual", ""))
    if convertToMap.has_key(ktype):
        (s, o) = convertToMap[ktype]
        return string.replace(string.replace(s, "$E", expr), "$T", ktype)
    elif ktype in primitiveTypes:
        return "makeqtype<%sType>(c,%s,\"qt.%s\")" % (ktype, expr, ktype)
    elif ktype in pointerTypes:
        return "makeqpointer<%sType>(c,%s,\"qt.%s\")" % (ktype, expr, ktype)
    elif "QList<" in ktype:
        # QList
        mtype = ktype[6:-3]
        return "makeqpointerlist<%sType>(c,%s,\"qt.%s\")" % (mtype, expr, mtype)
    else:
        return expr

def setExpr(targetexpr, expr, ktype):
    ktype = sstrip(string.replace(ktype, "virtual", ""))
    t = ""
    if setMap.has_key(ktype):
        t = setMap[ktype]
    elif ktype in primitiveTypes:
        return "setqtype<%sType>(%s,%s)" % (ktype, targetexpr, expr)
    elif ktype in pointerTypes:
        return "setqpointer<%sType>(%s,%s)" % (ktype, targetexpr, expr)
    else:
        t = "$O = $E"
    return string.replace(string.replace(t, "$E", expr), "$O", targetexpr)
    

def conditionType(t):
    if t.startswith("flags "):
        return "int"
    else:
        return t

#
#   Qt converter map
#

#
#   During parsing this will get populated with all of the types that have
#   been discovered
#

class API:
    def __init__(self):
        self.types = Set()
        self.classes = {}
        self.tmap = translationMap;

    def finish(self):
        for k in self.classes.keys():
            #self.tmap[k] = "qt." + k
            # for the time being only do classes we've got working so far
            if k in includeClasses:
                self.tmap[k] = k
                c = self.classes[k]
            self.tmap[k] = k
            #c = self.classes[k]
                #for e in c.enums:
                #    self.tmap[e.name] = "int"

    def showClass(self, name):
        c = self.classes[name]
        c.output()

    def translate(self, cpptype, inclass):
        F = lambda x: x not in typeElaborations
        parts = cpptype.split(" ")

        if ("int" in parts or "qreal" in parts) and ("*" in parts):
            return None

        key = " ".join(filter(F, parts))
        # e.g. "const QString &" -> "QString"
        if self.tmap.has_key(key) and (key in includeClasses):
            return self.tmap[key] 
        # e.g. "const char *"
        if self.tmap.has_key(cpptype):
            return self.tmap[cpptype]
        # an enum at the top level?
        #if cpptype.startswith("Qt::"):
        #    return "flags %s" % cpptype
        if cpptype.find("::") != -1:
            return "flags %s" % cpptype

        if inclass.enumInHierarchy(cpptype):
            return "flags %s" % inclass.fullEnumName(cpptype)
        # an enum in the class not qualified
        # test whether the type name needs to be fully qualified
        # e.g. "InsertPolicy" -> "QComboBox::InsertPolicy"
        #if inclass != None:
            #for e in inclass.enums:
            #    if e.name == cpptype or e.flags == cpptype:
            #        return "flags %s::%s" % (inclass.name, cpptype)
        #    return self.translate(inclass.name + "::" + cpptype, None)
        return None


api = API()
verbose = False

def message(s):
    global verbose
    if verbose:
        print s

def sstrip(s):
    return s.lstrip().rstrip()

def addType(t):
    api.types.add(t)

def parseProperty(prop):
    prop = prop[0:-1]
    parts = prop.split(" : ")
    if len(parts) == 2:
        name = sstrip(parts[0])
        type = sstrip(parts[1])
        addType(type)
        return (name, type)
    else:
        return None

def parseType(t):
    global api
    t = sstrip(reduce(lambda x,y: str(x) + " " + str(y), t, ""))
    addType(t)
    return t

def indexInList(el, list):
    i = 0
    for l in list:
        if l == el:
            return i
        i += 1
    return i

def parseParameter(param, n):
    param = sstrip(param)
    if param == "const" or param == "":
        return param
    parts = param.split()
    default = None
    name = "_p%d" % n
    if parts == []:
        return ("", param, None)
    if "=" in parts:
        index = indexInList("=", parts)
        default = sstrip(reduce(lambda x,y: str(x) + " " + str(y), parts[index+1:], ""))
        name = parts[index-1]
        del parts[index-1:]
    elif "*" in parts or "&" in parts:
        if parts[-1] == "*" or parts[-1] == "&":
            #name = None
            pass
        else:
            name = parts[-1]
            del parts[-1]
    elif len(parts) == 1:
        return (name, parts[0], default)
    else:
        name = parts[-1]
        del parts[-1]
    if parts == [] and name == None and default == None:
        return None
    else:
        type = parseType(parts[:])
        return (name, type, default)

def parseFunction(func):
    #parts = func.split("(")
    prop = False
    if len(func) == 0:
        return None
    if func[-1] == "@":
        prop = True
        func = func[0:-1]
    sindex = func.find("(")
    eindex = func.rfind(")")
    thistype = sstrip(func[eindex+1:])
    func = func[0:eindex]
    if sindex == -1:
        return None
    parts = [func[0:sindex], func[sindex+1:]]

    if len(parts) == 2:
        nameproto = parts[0].split()
        allparams = parts[1]

        bracketlevel = 0
        current = ""
        params = []
        count = 0

        for c in allparams:
            if c == ',' or c == ')':
                if bracketlevel == 0:
                    params.append(parseParameter(current, count))
                    current = ""
                else:
                    if c == ')':
                        bracketlevel -= 1
                    current += c
            elif c == '<' or c == '(':
                bracketlevel += 1
                current += c
            elif c == '>' or c == ')':
                bracketlevel -= 1
                current += c
            else:
                current += c

            count = count + 1

        if len(allparams) != 0:
            params.append(parseParameter(current, count))
        return (nameproto[-1], thistype, params, string.join(nameproto[0:-1]), prop)

    return None

##
##  NamespaceInfo holds the final parsed info about a Qt Class The
##  other results are Enumeration and Enum which are the name of the
##  enumeration and each individual name*value pair.
##


class NamespaceInfo:

    def __init__(self, name = None):
        self.name           = name
        self.isclass        = False
        self.functions      = []
        self.slots          = []
        self.signals        = []
        self.protectedfuncs = []
        self.enums          = []
        self.parents        = []
        self.virtuals       = []
        self.properties     = []
        self.globalfuncs    = []
        self.staticfuncs    = []
        self.isclass        = False
        self.includes       = []
        self.inheritedby    = []
        self.inherits       = []

    def output(self):
        if self.isclass:
            print "class", self.name
        else:
            print "namespace", self.name

        print "--inherits--"
        print self.inherits

        print "--inheritedby--"
        print self.inheritedby

        if self.includes:
            print "--includes--"
            for i in self.includes:
                print i

        if self.properties:
            print "--props--"
            for i in self.properties:
                if i != None:
                    print i
        if self.enums:
            print "--enums--"
            for i in self.enums:
                print i.name, i.flags
                for q in i.enums:
                    print "   ", q.name, "=", q.value

        if self.functions:
            print "--member functions--"
            for i in self.functions:
                if i != None:
                    print i

        if self.signals:
            print "--signals functions--"
            for i in self.signals:
                if i != None:
                    print i

        if self.slots:
            print "--slot functions--"
            for i in self.slots:
                if i != None:
                    print i

        if self.staticfuncs:
            print "--static functions--"
            for i in self.staticfuncs:
                if i != None:
                    print i

        if self.globalfuncs:
            print "--global functions--"
            for i in self.globalfuncs:
                if i != None:
                    print i
                    
    def enumInHierarchy(self, name):
        global api
        for i in self.enums:
            fullname = ("%s::%s" % (self.name, name))
            if i.name == name \
                    or i.name == fullname \
                    or i.flags == name \
                    or i.flags == fullname:
                return True
            for p in self.inherits:
                parent = api.classes[p]
                if parent.enumInHierarchy(name):
                    return True
        return False

    def fullEnumName(self, name):
        global api
        debug = name == "OpenMode"
        for i in self.enums:
            fullname = ("%s::%s" % (self.name, name))
            if i.name == name \
                    or i.name == fullname \
                    or i.flags == name \
                    or i.flags == fullname:
                return i.name
            for p in self.inherits:
                parent = api.classes[p]
                x = parent.fullEnumName(name)
                if x:
                    return x
        return None

    def finish(self):
        for q in range(0, len(self.functions)):
            f = self.functions[q]
            (name, fconst, params, rtype, prop) = f
            ctype = self.name + "::" + rtype
            fixed = False
            for e in self.enums:
                if e.name == ctype or e.flags == ctype:
                    self.functions[q] = (name, fconst, params, ctype, prop)
                    fixed = True

            (name, fconst, params, rtype, prop) = self.functions[q]

            for i in range(0, len(params)):
                p = params[i]
                (pname, ptype, pval) = p
                ctype = self.name + "::" + ptype
                for e in self.enums:
                    if e.name == ctype or e.flags == ctype:
                        #print "fixed:", params[i][1], "to", ctype
                        params[i] = (pname, ctype, pval)
            
        

class Enum:

    def __init__(self, name, value):
        self.name = name
        self.value = value

class Enumeration:

    def __init__(self, name):
        self.name = name
        self.enums = []
        self.flags = None

#
#   These are Mu versions of above. By handing MuClass a Namespace
#   from above it will generate MuFunction and MuEnum objects which
#   are then used to produce output
#

class MuEnum:
    
    def __init__(self, enumeration, muclass):
        self.muclass = muclass
        self.name = enumeration.name.split(":")[-1]
        self.flags = None
        self.output = False

        if forceEnumOutput.has_key(muclass.name):
            enums = forceEnumOutput[muclass.name]
            for e in enums:
                if e == self.name:
                    #print "INFO: will output %s.%s\n" % (muclass.name, e) 
                    self.output = True

        xmap = exclusionMap

        if enumeration.flags:
            self.flags = enumeration.flags.split(":")[-1]
        self.symbols = []
        for e in enumeration.enums:
            if e.name != "\n":
                n = e.name.split(":")[-1]
                val = muclass.name + "::" + n
                if not xmap or (not val in xmap):
                    self.symbols.append((n, val))

    def aliasDeclation(self):
        return "new Alias(c, \"%s\", \"int\")" % self.name

    def flagsAliasDeclaration(self):
        if self.flags:
            return "new Alias(c, \"%s\", \"int\")" % self.flags
        else:
            return None

    def symbolDeclaration(self, symbolTuple):
        (name, val) = symbolTuple
        out = "new SymbolicConstant(c, \"%s\", \"int\", Value(int(" % name
        out += "%s)))" % val
        return out
        

class MuFunction:

    def __init__(self, api, muclass, qtfunc):
        #
        #   Iterate over the functions
        #

        c = muclass.qt
        (name, const, args, rtype, isprop) = qtfunc
        if c.name in doProps:
            isprop = False

        count = 0
        if muclass.funcCount.has_key(name):
            count = muclass.funcCount[name]
            count = count + 1
        muclass.funcCount[name] = count

        self.muclass       = muclass
        self.abstract      = isAbstract(name)
        self.name          = name
        self.qtfunc        = qtfunc
        self.isconstructor = self.name == muclass.name
        self.isprop        = isprop
        self.args          = []
        self.rtype         = None
        self.failed        = False
        self.node          = "_n_%s%d" % (name, count)
        self.virtual       = rtype.find("virtual") != -1

        if self.name.find("operator") != -1:
            self.failed = True

        rtype = sstrip(string.replace(rtype, "virtual", ""))

        self.args.append(("this", muclass.name, None))

        for (aname, atype, aval) in args:
            mutype = api.translate(atype, c)
            if mutype == None:
                self.failed = True
                mutype = "\"%s\"" % atype
            self.args.append((aname, mutype, aval))

        self.iscopyconstructor = False

        if self.isconstructor:
            self.rtype = name
            if len(self.args) == 2:
                if self.args[1][1] == self.name:
                    self.iscopyconstructor = True
        else:
            self.rtype = api.translate(rtype, c)

        if self.iscopyconstructor:
            self.failed = True

        if self.rtype == None:
            self.failed = True
            self.rtype = "\"%s\"" % rtype

        self.compiled = "%s_%s" % (name, mangleName(conditionType(self.rtype)))

        #
        #   Test for functions that were already successfully translated
        #   that have the same function signature: if one is found we can't
        #   translate this one because it will shadow the previous
        #   one. 
        #
        overloads = []
        if count > 0:
            for f in muclass.functions:
                if f.name == self.name and not f.failed:
                    overloads.append(f)
            nargs = len(self.args)
            for f in overloads:
                fargs = len(f.args)
                if fargs == nargs and not f.failed:
                    samecount = 0
                    for i in range(0, nargs):
                        a = f.args[i][1]
                        b = self.args[i][1]
                        if a.startswith("flags"):
                            a = "int"
                        if b.startswith("flags"):
                            b = "int"
                        if a == b:
                            samecount = samecount + 1
                    if samecount == nargs:
                        if name == "QVariant":
                            print "FAILED: (shadows) in %s" % str(qtfunc)
                            print "OTHER = %s" % str(f.qtfunc)
                        message("WARNING: %s.%s with %s shadows existing version" % \
                                    (muclass.name, self.name, str(self.args)))
                        self.failed = True

        for a in self.args:
            self.compiled += "_%s" % mangleName(conditionType(a[1]))


    def symbolDeclaration(self):
        # note: assumes the context is in a var called "c"
        rtype = conditionType(self.rtype)
        if self.muclass.muapi.classes.has_key(rtype):
            rtype = "qt." + rtype
        out = "new Function(c, \"%s\", %s, None, Compiled, %s, Return, \"%s\", " % \
                (self.name, self.node, self.compiled, rtype)
        if self.args:
            out += "Parameters, "
            for (aname, atype, aval) in self.args:
                atype = conditionType(atype)
                if self.muclass.muapi.classes.has_key(atype):
                    atype = "qt." + atype
                out += "new Param(c, \"%s\", \"%s\"), " % (aname, atype)
        out += "End)"
        return out

    def nodeImplementation(self):
        if self.failed:
            return "// MISSING NODE: %s" % self.muDeclaration()
        if self.abstract and self.isconstructor:
            return "// NO NODE: CLASS IS ABSTRACT: %s" % self.muDeclaration()
        rep = repMapFind(self.rtype)
        if rep == None:
            return None
        (repType, instType) = rep
        out = "static NODE_IMPLEMENTATION(%s, %s)\n{\n    " % (self.node, repType)
        endParen = False
        if repType != "void":
            out += "NODE_RETURN("
            endParen = True
        out += "%s(NODE_THREAD" % self.compiled
        if self.args:
            count = 0
            for (aname, atype, aval) in self.args:
                rep = repMapFind(atype)
                (repType, instType) = rep
                if count == 0:
                    out += ", NONNIL_NODE_ARG(%d, %s)" % (count, repType)
                else:
                    out += ", NODE_ARG(%d, %s)" % (count, repType)
                count = count + 1
        if endParen:
            out += "));\n"
        else:
            out += ");\n";
        out += "}\n"

        return out

    def derefExp(self, expr, atype):
        muapi = self.muclass.muapi
        ktype = atype;
        if muapi.classes.has_key(atype):
            c = muapi.classes[atype]
            if c.isAByName("QObject"):
                return convertFrom(expr, "qt.QObject", atype)
            elif c.pointertype:
                return convertFrom(expr, "qt." + atype, atype + " *")
            else:
                return convertFrom(expr, "qt." + atype, atype)
        return convertFrom(expr, atype, atype)

    def derefArg(self, arg):
        (aname, atype, aval) = arg
        return self.derefExp("param_" + aname, atype)

    def compiledFunction(self):
        #
        #   This is the function that does the real business
        #
        muclass = self.muclass
        muapi = muclass.muapi
        isQObject = muclass.isAByName("QObject")

        if self.failed:
            return "// MISSING FUNC: %s" % self.muDeclaration()
        if self.abstract and self.isconstructor:
            return "// NO FUNC: CLASS IS ABSTRACT: %s" % self.muDeclaration()
        rep = repMapFind(self.rtype)
        out = "%s %s(Mu::Thread& NODE_THREAD" % (rep[0], self.compiled)
        for (aname, atype, aval) in self.args:
            rep = repMapFind(atype)
            out += ", %s param_%s" % (rep[0], aname)
        out += ")\n{\n"
        body = ""

        qtrtype = self.qtfunc[3]
            
        expr = ""

        if self.isconstructor:
            if muclass.primitivetype:
                expr = "%s(" % self.name
            else:
                if isQObject and allowInheritance:
                    expr = "new MuQt_%s(NODE_THREAD.process()->callEnv()" % self.name
                    if len(self.args) > 1:
                        expr += ", "
                else:
                    expr = "new %s(" % self.name
        else:
            if muclass.primitivetype:
                expr = "arg0.%s(" % self.name
            else:
                expr = "arg0->%s(" % self.name

        for i in range(0, len(self.args)):
            global showit
            showit = self.name == "isDragEnabled"

            a = self.args[i]
            (aname, atype, aval) = a
            (dexpr, dtype) = self.derefArg(a)


            ntype = ""
            
            if i > 0:
                qarg = self.qtfunc[2][i-1]
                if dtype.find("::") != -1 and dtype.find(qarg[1]) != -1:
                    ntype = dtype
                else:
                    ntype = qarg[1]
            else:
                ntype = dtype

            if ntype[-1] == "&":
                ntype = ntype[0:-1]

            if i > 0 or not self.isconstructor:
                body += "    %s arg%d = " % (ntype, i)
                body += dexpr
                body += ";\n"

            if i > 1:
                expr += ", "

            if i > 0:
                expr += "arg%d" % i

        expr += ")"

        rtypeObject = muapi.isAByName(self.rtype, "QObject")

        if isQObject:
            if self.isconstructor:
                body += "    setobject(param_this, %s);\n    return param_this;\n" % expr
            elif self.rtype == "void":
                body += "    %s;\n" % expr
            else:
                needsDeref = muapi.classes.has_key(self.rtype)
                if needsDeref and rtypeObject:
                    body += "    return makeinstance(c, %s, \"%s\");\n" \
                        % (expr, "qt." + self.rtype)
                elif needsDeref:
                    body += "    return %s;\n" % convertTo(expr, self.rtype)
                else:
                    body += "    return %s;\n" % convertTo(expr, qtrtype)
        elif muclass.pointertype:
            if self.isconstructor:
                body += "    %s;\n    return param_this;\n" %  \
                    setExpr("param_this", expr, muclass.name)
            elif self.rtype == "void":
                body += "    %s;\n" % expr
                body += "    %s;\n" % setExpr("param_this", "arg0", muclass.name)
            else:
                body += "    return %s;\n" % convertTo(expr, qtrtype)
        #elif muclass.isBaseClass():
        else:
            if muclass.primitivetype and self.isconstructor:
                n = muclass.name
                #n = muclass.baseClassNames()[0]
                body += "    %s;\n" % setExpr("param_this", expr, n)
                #body += "    setqtype<%sType>(param_this,%s);\n" % (n, expr)
                body += "    return param_this;\n"
            elif self.rtype == "void":
                body += "    %s;\n" % expr
                if muclass.primitivetype:
                    body += "    %s;\n" % setExpr("param_this", "arg0", muclass.name)
            else:
                #body += "    return %s;\n" % convertTo(expr, qtrtype)
                needsDeref = muapi.classes.has_key(self.rtype)
                if needsDeref and rtypeObject:
                    body += "    return makeinstance(c, %s, \"%s\");\n" \
                        % (expr, "qt." + self.rtype)
                elif needsDeref:
                    body += "    return %s;\n" % convertTo(expr, self.rtype)
                else:
                    body += "    return %s;\n" % convertTo(expr, qtrtype)

        out += "    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());\n";
        out += body
        out += "}\n"
        return out
                
    def muDeclaration(self):
        out = "%s (%s; " % (self.name, self.rtype)
        comma = False
        for (aname, mutype, aval) in self.args:
            if comma:
                out += ", "
            out += "%s %s" % (mutype, aname)
            comma = True
        out += ")"
        return out



class MuClass:

    def __init__(self, api, qtnamespace, muapi):
        self.qt            = qtnamespace
        self.name          = qtnamespace.name
        self.isinterface   = self.name in interfaceTypes
        self.functions     = []
        self.virtuals      = []
        self.statics       = []
        self.enums         = []
        self.F_trans       = lambda f: not f.failed and not f.isprop
        self.funcCount     = {}
        self.inherits      = []
        self.inheritedby   = []
        self.muapi         = muapi
        self.primitivetype = isAPrimitiveType(self.name)
        self.pointertype   = isAPointerType(self.name)

        for f in qtnamespace.functions:
            fname = f[0]
            cppname = qtnamespace.name + "::" + fname
            exclude = isFunctionExcluded(qtnamespace, f)
            if not fname.startswith('~') and not exclude:
                self.functions.append(MuFunction(api, self, f))

        for e in qtnamespace.enums:
            cppname = qtnamespace.name + "::" + e.name.split(":")[-1]
            exclude = cppname in exclusionMap
            if not exclude:
                self.enums.append(MuEnum(e, self))

    def outputMuDeclarations(self):
        F_trans  = lambda f: not f.failed and not f.isprop
        F_prop   = lambda f: not f.failed and f.isprop
        F_failed = lambda f: f.failed 

        print "---enums translated---"
        for e in self.enums:
            if e.output:
                print e.name, ":= int"
                if e.flags:
                    print e.flags, ":= int"
                for enum in e.symbols:
                    (name, val) = enum
                    print name, ":=", val

        print "---functions translated---"
        count = 1
        for f in filter(F_trans, self.functions):
            print "% 4d  %s" % (count, f.muDeclaration())
            count = count + 1

        print "---functions that are props---"
        count = 1
        for f in filter(F_prop, self.functions):
            print "% 4d  %s" % (count, f.muDeclaration())
            count = count + 1

        print "---functions that failed---"
        count = 1
        for f in filter(F_failed, self.functions):
            print "% 4d  %s" % (count, f.muDeclaration())
            count = count + 1

    def outputCompiledNodes(self):
        out = ""
        for f in filter(self.F_trans, self.functions):
            out += f.compiledFunction()
            out += "\n"
        return out

    def outputNodeImplementations(self):
        out = ""
        for f in filter(self.F_trans, self.functions):
            out += f.nodeImplementation()
            out += "\n"
        return out

    def isA(self, muclass):
        db = self.name == "QIcon"

        if self == muclass:
            return True
        else:
            for c in self.inherits:
                if c.isA(muclass):
                    return True
        return False

    def isAByName(self, muclassName):
        if self.muapi.classes.has_key(muclassName):
            return self.isA(self.muapi.classes[muclassName])
        else:
            return False

    def baseClassNames(self):
        all = []
        if len(self.inherits) == 0:
            all.append(self.name)
            return all
        for c in self.inherits:
            all.extend(c.baseClassNames())
        return all

    def isBaseClass(self):
        return not self.inherits or len(self.inherits) == 0

    def outputEnumDeclarations(self):

        out = "addSymbols(\n"

        for e in self.enums:
            out += "    %s,\n" % e.aliasDeclation()
            flags = e.flagsAliasDeclaration()
            if flags:
                out += "    %s,\n" % flags
            for enum in e.symbols:
                out += "      %s,\n" % e.symbolDeclaration(enum)

        out += "    EndArguments);\n"
        return out

    def outputSymbolDeclarations(self):

        out = "addSymbols(\n"

        for e in self.enums:
            if e.output:
                out += "    %s,\n" % e.aliasDeclation()
                if e.flags:
                    out += "    %s,\n" % e.flagsAliasDeclaration()
                for enum in e.symbols:
                    out += "      %s,\n" % e.symbolDeclaration(enum)

        for f in self.functions:
            if f.failed:
                out +=  "    // MISSING: %s\n" % f.muDeclaration()
            elif f.isprop:
                out +=  "    // PROP: %s\n" % f.muDeclaration()
            elif f.isconstructor and f.abstract:
                out +=  "    // ABSTRACT CONSTRUCTOR: %s\n" % f.muDeclaration()
            else:
                out +=  "    %s,\n" % f.symbolDeclaration()

        out += "    EndArguments);\n"
        return out

    def outputMuQtNativeImplementation(self):
        if not allowInheritance:
            return ""

        out = "// Inheritable object implemenation\n\n"

        # constructors
        qt = self.qt
        for f in self.functions:
            if not f.failed:
                (name, fconst, params, rtype, prop) = f.qtfunc
                purevirtual = "= 0" in fconst
                fconst = string.replace(fconst, "= 0", "")
                if f.isconstructor or "virtual" in rtype:
                    rtype_clean = string.strip(string.replace(rtype, "virtual", ""))

                    # output the function rtype name and args
                    if f.isconstructor:
                        out += "MuQt_" + name + "::MuQt_" + name + "(const CallEnvironment* ce"
                    else:
                        out += rtype_clean + " MuQt_" + self.name + "::" + name + "("

                    # args
                    for i in range(0, len(params)):
                        p = params[i]
                        (pname, ptype, pval) = p
                        if i > 0 or f.isconstructor:
                            out += ", "
                        out += ptype + " " + pname

                    out += ") " + fconst

                    if f.isconstructor:
                        # call the base class constr
                        out += "\n : " + name + "("
                        for i in range(0, len(params)):
                            p = params[i]
                            (pname, ptype, pval) = p
                            if i > 0:
                                out += ", "
                            out += pname
                        out += ")"

                    if purevirtual:
                        # pure virtual func
                        # what to do here?
                        out += " // pure virtual"

                    out += "\n{\n"

                    # output the rest of the body
                    
                    out += "    "
                    if f.isconstructor:
                        out += "_env = ce;\n"
                    else:
                        if rtype_clean != "void":
                            out += "return "
                        out += self.name + "::" + f.name + "("
                        for i in range(0, len(params)):
                            p = params[i]
                            (pname, ptype, pval) = p
                            if i > 0 or f.isconstructor:
                                out += ", "
                            out += pname
                        out += ");\n"

                    # finish
                    out += "}\n\n"

        return out

    def outputMuQtNativeDeclaration(self):
        if not allowInheritance:
            return ""

        out = "// Inheritable object\n\n"
        out += "class MuQt_%s : public %s\n{\n  public:\n" % (self.name, self.name)

        # constructors
        qt = self.qt
        for f in self.functions:
            if not f.failed:
                (name, fconst, params, rtype, prop) = f.qtfunc
                fconst = string.replace(fconst, "= 0", "")
                if f.isconstructor or "virtual" in rtype:
                    if f.isconstructor:
                        out += "    " + rtype + "MuQt_" + name + "(const CallEnvironment*"
                    else:
                        out += "    " + rtype + " " + name + "("
                    for i in range(0, len(params)):
                        p = params[i]
                        (pname, ptype, pval) = p
                        if i > 0 or f.isconstructor:
                            out += ", "
                        out += ptype + " " + pname
                    out += ") " + fconst + ";\n"
        out += "    const CallEnvironment* _env;\n"
        out += "};\n"
        return out

    def outputSourceFiles(self):

        templateCPP = templateObjectCPP
        templateH   = templateObjectH

        if self.primitivetype:
            templateCPP = templateTypeCPP
            templateH = templateTypeH
        elif self.isinterface:
            templateCPP = templateInterfaceTypeCPP
            templateH = templateInterfaceTypeH
        elif self.pointertype:
            templateCPP = templatePointerTypeCPP
            templateH = templatePointerTypeH

        handrolledSymbols = "handrolled/%sSymbols.cpp" % self.name
        handrolledDefs    = "handrolled/%sDefinitions.cpp" % self.name
        handrolledInclude = "handrolled/%sIncludes.cpp" % self.name

        hsyms = None
        hdefs = None
        hincs = None

        if os.path.exists(handrolledSymbols):
            xfile = open(handrolledSymbols, "r")
            hsyms = xfile.readlines()
            xfile.close()

        if os.path.exists(handrolledDefs):
            xfile = open(handrolledDefs, "r")
            hdefs = xfile.readlines()
            xfile.close()

        if os.path.exists(handrolledInclude):
            xfile = open(handrolledInclude, "r")
            hincs = xfile.readlines()
            xfile.close()

        cppfile = open(templateCPP, "r")

        cpplines = []

        while True:
            line = cppfile.readline()
            if line == "":
                break
            if line.find("{%%definitions%%}") != -1:
                cpplines.append(self.outputCompiledNodes())
                cpplines.append(self.outputNodeImplementations())
            elif line.find("{%%addSymbols%%}") != -1:
                cpplines.append(self.outputSymbolDeclarations())
            elif line.find("{%%addSymbolsEnums%%}") != -1:
                cpplines.append(self.outputEnumDeclarations())
            elif line.find("{%%nativeMuQtClassImplemenation%%}") != -1:
                cpplines.append(self.outputMuQtNativeImplementation())
            elif line.find("{%%nativeObject%%}") != -1:
                if self.name == "QObject":
                    cpplines.append("   new MemberVariable(c, \"native\", \"qt.NativeObject\"),")
            elif line.find("{%%addHandRolledSymbols%%}") != -1:
                if hsyms:
                    cpplines.extend(hsyms)
            elif line.find("{%%handRolledDefinitions%%}") != -1:
                if hdefs:
                    cpplines.extend(hdefs)
            elif line.find("{%%handRolledInclude%%}") != -1:
                if hincs:
                    cpplines.extend(hincs)
            else:
                cpplines.append(string.replace(line, "$T", self.name))
        cppfile.close()

        cppout = open(self.name + "Type.cpp", "w")
        cppout.writelines(cpplines)
        cppout.close()

        if not (self.name in noHFileOutput):
            hfile = open(templateH, "r")
            hlines = []
            while True:
                line = hfile.readline()
                if line == "":
                    break
                elif line.find("{%%nativeMuQtClass%%}") != -1:
                    hlines.append(self.outputMuQtNativeDeclaration())
                elif line.find("{%%typeDeclarations%%}") != -1:
                    if self.name == "QObject":
                        hlines.append("    struct Struct { QObject* object; };\n")
                else:
                    hlines.append(string.replace(line, "$T", self.name))
            hfile.close()

            hout = open(self.name + "Type.h", "w")
            hout.writelines(hlines)
            hout.close()

    def outputModuleDefinition(self, finishedMap):
        out = ""
        inherits = filter(lambda x: not x.isinterface, self.inherits)
        if self not in finishedMap:
            if self.name in includeClasses:
                if len(inherits) > 0:
                    out += "    %sType* t_%s = new %sType(c, \"%s\"" % \
                        (self.name, self.name, self.name, self.name)
                    out += ", t_%s" % inherits[0].name
                    out += ");";
                else:
                    out += "    %sType* t_%s = new %sType(c, \"%s\");" % \
                        (self.name, self.name, self.name, self.name)
                out += " qt->addSymbol(t_%s);\n" % self.name
                finishedMap[self] = self
        for c in self.inheritedby:
            out += c.outputModuleDefinition(finishedMap)
        return out


class MuAPI:

    def __init__(self, api):
        self.module  = None
        self.classes = {}
        self.api     = api

        for k in api.classes.keys():
            qtclass = api.classes[k]
            muclass = MuClass(api, qtclass, self)
            self.classes[muclass.name] = muclass

        for k in self.classes.keys():
            c = self.classes[k]
            for i in c.qt.inheritedby:
                if self.classes.has_key(i):
                    child = self.classes[i]
                    child.inherits.append(c)
                    c.inheritedby.append(child)
                else:
                    pass
                    #print "missing class", i

    def classForName(self, name):
        if self.classes.has_key(name):
            return self.classes[name]
        else:
            return None

    def isAByName(self, name, classname):
        c = self.classForName(name)
        if c:
            return c.isAByName(classname)
        else:
            return False
            
##
##  QtDocParser parses the html file
##
 
class QtDocParser(SGMLParser):

    def __init__(self, url):
        SGMLParser.__init__(self)
        self.buffer       = ""
        self.inlist       = False
        self.infunc       = False
        self.intitle      = False
        self.indetails    = False
        self.funcIsProp   = False
        self.h3           = False
        self.acount       = 0
        self.pcount       = 0
        self.public       = []
        self.globaldefs   = []
        self.staticPublic = []
        self.protected    = []
        self.slots        = []
        self.macros       = []
        self.signals      = []
        self.related      = []
        self.properties   = []
        self.types        = []
        self.enums        = []
        self.enumName     = None
        self.enumValue    = None
        self.defsover     = False
        self.qtnamespace  = None
        self.ininheritedby= False;
        self.ininherits   = False;
        self.childurls    = []
        self.bucket       = self.globaldefs
        self.url          = url
        self.defenum      = False
        self.td           = False
        self.includes     = []
        self.classRE      = re.compile("([A-Za-z0-9]+) Class Reference")
        self.namespaceRE  = re.compile("([A-Za-z0-9]+) Namespace Reference")
        self.includeRE    = re.compile("#include ")
        self.inheritedby  = []
        self.inherits     = []

        ui = self.url.rfind("/")
        self.urlbase = url[:ui+1]

        usock = urllib.urlopen(url)
        self.feed(usock.read())
        usock.close()

        self.qtnamespace.inheritedby = self.inheritedby
        self.qtnamespace.inherits = self.inherits
        self.convertFunctions()
        self.convertProperties()
        self.convertEnums()
        self.qtnamespace.includes = self.includes
        self.qtnamespace.finish()

    def result(self):
        return self.qtnamespace

    def addChildURL(self, url):
        if string.find(url, "q3") != -1:
            return
        p = url.split("/")
        if p[0] == url:
            self.childurls.append(self.urlbase + url)
        else:
            self.childurls.append(url)

    def start_title(self, attrs):
        self.intitle = True

    def end_title(self):
        self.intitle = False
        isclass = True
        g = self.classRE.search(self.title)
        if not g:
            isclass = False
            g = self.namespaceRE.search(self.title)
        self.qtnamespace = NamespaceInfo(g.group(1))
        self.qtnamespace.isclass = isclass

    def end_table(self):
        self.defenum = False
            
    def start_p(self, attrs):
        self.pcount += 1

    def end_p(self):
        self.ininheritedby = False
        self.ininherits = False
        self.pcount -= 1

    def start_a(self, attrs):
        if self.ininheritedby:
            for (attr, value) in attrs:
                if attr == "href":
                    self.addChildURL(value)
        elif self.infunc:
            for (attr, value) in attrs:
                if attr == "href":
                    self.funcIsProp = value.rfind("-prop") != -1
        self.acount += 1

    def end_a(self):
        self.acount -= 1

    def start_h3(self, attrs):
        self.h3 = True

    def end_h3(self):
        self.h3 = False

    def start_li(self, attrs):
        self.inlist = True

    def end_li(self):
        if not self.defsover:
            if self.infunc:
                self.bucket.append(self.buffer)
                if self.funcIsProp:
                    self.bucket[-1] += "@"
                self.buffer = ""
            self.inlist = False
            self.infunc = False
            self.funcIsProp = False

    def start_table(self, attrs):
        pass

    def start_tr(self, attrs):
        self.td = 0

    def start_td(self, attrs):
        self.td = self.td + 1

    def end_tr(self):
        if self.defenum:
            if self.enumName and self.enumValue:
                self.enums[-1].enums.append(Enum(self.enumName, self.enumValue))
        self.enumName  = None
        self.enumValue = None
 
    def start_div(self, attrs):
        self.infunc = ("class", "fn") in attrs

    def handle_data(self, data):
        if self.pcount > 0:
            if data == "Inherited by ":
                self.ininheritedby = True
            elif data == "Inherits ":
                self.ininherits = True
        if data == "Obsolete flags:":   # note obsolete
            self.defenum = False
        elif self.includeRE.search(data):
            self.includes.append(data)
        elif data == " (preliminary)":  # shows up in qwidget.html, messes up everything
            return
        elif not self.defsover:
            if self.intitle:
                self.title = data
            elif self.ininheritedby:
                if not data.startswith(",") and \
                        not data.startswith(".") and \
                        not data.startswith(" and") and \
                        not data.startswith("Inherited"):
                    self.inheritedby.append(data)
            elif self.ininherits:
                if not data.startswith(",") and \
                        not data.startswith(".") and \
                        not data.startswith(" and") and \
                        not data.startswith("Inherits"):
                    self.inherits.append(data)
            elif self.h3:
                if data == "Public Functions":
                    self.bucket = self.public
                elif data == "Protected Functions":
                    self.bucket = self.protected
                elif data == "Static Public Members":
                    self.bucket = self.staticPublic
                elif data == "Related Non-Members":
                    self.bucket = self.related
                elif data == "Signals":
                    self.bucket = self.signals
                elif data == "Public Slots":
                    self.bucket = self.slots
                elif data == "Properties":
                    self.bucket = self.properties
                elif data == "Macros":
                    self.bucket = self.macros
                elif data == "Public Types":
                    self.bucket = self.types
                elif data == "Detailed Description":
                    self.defsover = True
                elif data[0:5] == "enum ":
                    self.defenum = True
                    self.enums.append(Enumeration(data.split()[-1]))
                elif data[0:6] == "flags " and self.defenum:
                    self.enums[-1].flags = data.split()[-1]
            elif self.defenum:
                if self.td == 1:
                    self.enumName = data
                elif self.td == 2:
                    self.enumValue = data
                else:
                    # docs
                    pass
            # Don't add functions that are props: these will get added
            # programatically
            elif self.infunc: #and not self.funcIsProp:
                self.buffer += data

    def convertFunctions(self):
        F = lambda x: x != None
        self.qtnamespace.functions      = filter(F, map(parseFunction, self.public))
        self.qtnamespace.slots          = filter(F, map(parseFunction, self.slots))
        self.qtnamespace.globalfuncs    = filter(F, map(parseFunction, self.globaldefs))
        self.qtnamespace.staticfuncs    = filter(F, map(parseFunction, self.staticPublic))
        self.qtnamespace.signals        = filter(F, map(parseFunction, self.signals))
        self.qtnamespace.protectedfuncs = filter(F, map(parseFunction, self.protected))

    def convertProperties(self):
        if self.properties:
            self.qtnamespace.properties = map(parseProperty, self.properties)
    
    def convertEnums(self):
        self.qtnamespace.enums = self.enums


##
##

def parseURL(url):
    parser = QtDocParser(url)
    result = parser.result()
    message("INFO: parsed " + result.name)
    api.classes[result.name] = result
    return parser

def recursiveParse(url):
    try:
        parser = parseURL(url)
        for u in parser.childurls:
            recursiveParse(u)
    except:
        print "FAILED:", url
        print traceback.print_exc()


#----------------------------------------------------------------------
# parse the args

outputFile       = False
outputStdout     = False
outputMu         = False
outputOtherTypes = False
outputClasses    = []
outputModuleParts = False
outputRawClass    = False

def setrawclass(x):
    global outputRawClass
    outputRawClass = True

def setout(x):
    global outputFile
    outputFile = True

def setstdout(x):
    global outputStdout
    outputStdout = True

def setmu(x):
    global outputMu
    outputMu = True

def setparts(x):
    global outputModuleParts
    outputModuleParts = True

def setother(x):
    global outputOtherTypes
    outputOtherTypes = True

def setverbose(x):
    global verbose
    verbose = True

argMap = {
    "-o" : setout,
    "-v" : setverbose,
    "-mu" : setmu,
    "-module" : setparts,
    "-stdout" : setstdout,
    "-other" : setother,
    "-rawclass" : setrawclass
}

del sys.argv[0]


for a in sys.argv:
    if argMap.has_key(a):
        argMap[a](a)
    elif a.startswith("-"):
        print "ERROR: bad arg", a
        sys.exit(-1)
    else:
        outputClasses.append(a)

if os.path.exists(qtapifile):
    message("INFO: loading Qt API")
    api = pickle.load(open(qtapifile))
else:
    message("INFO: building Qt API")
    for base in baseHTML:
        htmlfile = "%s/%s.html" % (htmlDir, base)
        recursiveParse(htmlfile)
    api.finish()
    message("INFO: dumping Qt API")
    pickle.dump(api, open(qtapifile, "w"))

if outputRawClass:
    if len(outputClasses):
        for cname in outputClasses:
            api.showClass(cname)
    exit

message("INFO: building Mu API")
muapi = MuAPI(api)

if outputModuleParts:
    out = "QWidgetType* addAllQTSymbols(MuLangContext* c, Module* qt)\n{\n"
    finishedMap = {}
    for cname in outputClasses:
        if muapi.classes.has_key(cname):
            c = muapi.classes[cname]
            if c.isBaseClass():
                out += c.outputModuleDefinition(finishedMap)
    out += "return t_QWidget;\n";
    out += "}\n"
    f = open("qtTypeDefinitions.cpp", "w")
    f.write(out)
    f.close()

    includes = ""
    for cname in outputClasses:
        if muapi.classes.has_key(cname):
            if cname in includeClasses:
                includes += "#include \"%sType.h\"\n" % cname
    f = open("qtModuleIncludes.h", "w")
    f.write(includes)
    f.close()

if len(outputClasses):
    for cname in outputClasses:
        if muapi.classes.has_key(cname):
            c = muapi.classes[cname]
            if outputMu:
                c.outputMuDeclarations()
            if outputStdout:
                print c.outputCompiledNodes()
                print c.outputNodeImplementations()
                print c.outputSymbolDeclarations()
                print c.outputEnumDeclarations()
            if outputFile:
                message("INFO: output files for " + cname)
                c.outputSourceFiles()
        else:
            print "WARNING: can't find class", cname
else:
    if outputOtherTypes:
        typelist = []
        print "--other types--"
        for t in api.types:
            typelist.append(t)

        typelist.sort()
        pp.pprint(typelist)

