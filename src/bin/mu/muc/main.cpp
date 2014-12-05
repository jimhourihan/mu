//
//	Copyright (c) 2001 Jim Hourihan
//
//	The coded instructions herein are the sole property of 
//	Jim Hourihan and may not be modified, redistributed, or 
//	used without permission.
//
#include <Mu/Alias.h>
#include <Mu/Archive.h>
#include <Mu/Function.h>
#include <Mu/MachineRep.h>
#include <Mu/NodePrinter.h>
#include <Mu/NodePrinter.h>
#include <Mu/Process.h>
#include <Mu/Symbol.h>
#include <Mu/SymbolTable.h>
#include <Mu/Type.h>
#include <Mu/Value.h>
#include <Mu/Module.h>
#include <Mu/Exception.h>
#include <Mu/TupleType.h>
#include <MuLang/DynamicArrayType.h>
#include <MuLang/FixedArrayType.h>
#include <MuLang/DynamicArray.h>
#include <MuLang/MuLangContext.h>
#include <MuLang/MuLangLanguage.h>
#include <MuLang/StringType.h>
#include <arg.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#ifndef PLATFORM_WINDOWS
#include <sys/resource.h>
#include <sys/time.h>
#endif
#include <vector>
//#include "CppBackEnd.h"
#include <stl_ext/string_algo.h>

#include <TwkUtil/PathConform.h>

#ifdef LINKED_MODULES
#include <MuAutoDoc/AutoDocModule.h>
#include <MuSystem/SystemModule.h>
#include <MuIO/IOModule.h>
#include <MuImage/ImageModule.h>
#include <MuEncoding/EncodingModule.h>
#include <MuQt/qtUtils.h>
#include <MuQt/qtModule.h>
#endif

using namespace std;
using namespace Mu;
using namespace stl_ext;
using namespace Mu::Archive;

static const char*     outfile    = "out.muc";
static const char*     docfile    = "";
static const char*     verifyfile = 0;
static int             verbose    = 0;
static int             debug      = 0;
static GenericMachine* machine    = 0;
static MuLangContext*  context    = 0;
static MuLangLanguage* language   = 0;
static Process*        process    = 0;
static std::vector<string> infiles;


//----------------------------------------------------------------------

void
writeArchive(Writer& writer,
             string outfile,
             Process* process,
             Context* context)
{
    ofstream file(outfile.c_str(), ios_base::binary);

    if (!file)
    {
        cerr << "ERROR: Unable to open output file" << endl;
        exit(-1);
    }

    writer.write(file);

    if (verbose)
    {
        cout << "INFO: --- root symbols ---" << endl;

        const SymbolSet& ss = writer.rootSymbolSet();

        for (SymbolSet::const_iterator i = ss.begin();
             i != ss.end();
             ++i)
        {
            cout << "    ";
            cout << (*i)->fullyQualifiedName() << endl;
        }
    }
}

void
writeDocfile(Writer& writer,
             string outfile,
             Process* process,
             Context* context)
{
    //
    //  Write to a temp memory buffer and then write the file. This is
    //  necessary because just asking for docs may cause another mud
    //  file (or existing) of the same name to be loaded lazily. 
    //  

    stringstream str;

    if (writer.writeDocumentation(str) > 0)
    {
        ofstream file(outfile.c_str(), ios_base::binary);

        if (!file)
        {
            cerr << "ERROR: Unable to open output (documentation) file" << endl;
            exit(-1);
        }
        
        file << str.str();
    }
    else
    {
        cout << "WARNING: no documentation file (" << outfile << ") created because no documentation found" << endl;
    }
}

void
writeToFile(const string& outfilename, const string& docfilename)
{
    NameVector infileNames;


    //
    //  Collect the primary symbols
    //

    SymbolVector symbols;
    Names names;
    Writer writer(process, context);
    writer.setDebugOutput(verbose);
    writer.setAnnotationOutput(debug);

    for (size_t i = 0; i < infiles.size(); i++)
    {
        writer.collectSymbolsFromFile(context->internName(infiles[i].c_str()), symbols);
    }

    //writer.collectPrimarySymbols(context->globalScope(), symbols);
    writer.collectNames(symbols, names);
    writer.add(symbols);
    writer.add(names);

    if (verbose)
    {
        cout << "INFO: ---- symbols ----" << endl;

        for (int i=0; i < symbols.size(); i++)
        {
            const Symbol* s = symbols[i];
            
            cout << "    ";
            s->output(cout);
            cout << endl;
        }

        cout << "INFO: --- required ----" << endl;

        const ModuleSet& modules = writer.requiredModules();

        for (ModuleSet::const_iterator i = modules.begin();
             i != modules.end();
             ++i)
        {
            cout << "    " << (*i)->fullyQualifiedName() << endl;
        }
    }

    String ext = extension(outfilename).c_str();

    if (outfilename != "") writeArchive(writer, outfilename.c_str(), process, context);
    if (docfilename != "") writeDocfile(writer, docfilename.c_str(), process, context);

    if (verbose)
    {
        cout << "INFO: wrote " << outfilename << endl;
    }
}

//----------------------------------------------------------------------

void
verifyFile(const string& filename)
{
    ifstream file(filename.c_str(), ios_base::binary);

    if (!file)
    {
        cerr << "ERROR: Unable to open " << filename << " to verify" << endl;
        exit(-1);
    }

    Reader reader(process, context);
    reader.setDebugOutput(verbose);
    reader.read(file);
    
    if (verbose)
    {
        cout << "--- header ---" << endl;

        const Header& header = reader.header();
        cout << "header.magicNumber = " << hex << header.magicNumber << endl;
        cout << "header.version     = " << dec << header.version << endl;
        cout << "header.sizeType    = " << dec << header.sizeType << endl;

        const NameVector& nameTable = reader.nameTable();
        size_t count = 0;

        cout << "--- name table ---" << endl;

        for (size_t i = 0; i < nameTable.size(); i++)
        {
            if (count) cout << ", ";
            cout << i << "=" << nameTable[i];
            count += strlen(nameTable[i].c_str());
            if (count > 40) { cout << endl; count = 0; }
        }

        cout << endl;
        cout << "--- require modules ---" << endl;

        const NameVector& requiredModules = reader.requiredModules();

        for (size_t i = 0; i < requiredModules.size(); i++)
        {
            cout << requiredModules[i] << endl;
        }

        cout << endl;
    }
}


//----------------------------------------------------------------------

int 
collectInputFiles(int argc, char *argv[])
{
    for (int i=0; i<argc; i++)
    {
	infiles.push_back(TwkUtil::pathConform(argv[i]));
    }
    
    return 0;
}

int
main(int argc, char **argv)
{
    GarbageCollector::init();

    if (arg_parse
	(argc, argv,
	 "", "Usage: %s [options]", argv[0],
	 "", "Mu compiler",
	 "", ARG_SUBR(collectInputFiles), "input .mu source files",
	 "-o %S", &outfile, "output .muc/.cpp/.so file (default=%s)", outfile,
	 "-d %S", &docfile, "output .mud file (default=no output)", 
         "-v", ARG_FLAG(&verbose), "verbose",
         "-G", ARG_FLAG(&debug), "debug output",
         "-verify %S", &verifyfile, "verify previously created file",
	 0) < 0)
    {
        exit( -1 );
    }

    if (*docfile != 0)
    {
        string n = TwkUtil::pathConform(docfile);
        docfile = strdup(n.c_str());
    }

    if (*outfile != 0)
    {
        string n = TwkUtil::pathConform(outfile);
        outfile = strdup(n.c_str());
    }

    if (*verifyfile != 0)
    {
        string n = TwkUtil::pathConform(verifyfile);
        verifyfile = strdup(n.c_str());
    }

    machine  = new GenericMachine();
    context  = new MuLangContext("compile","main");
    language = new MuLangLanguage();
    process  = new Process(context);

#ifdef LINKED_MODULES
    Module* autodoc  = new Mu::AutoDocModule(context, "autodoc");
    Module* io       = new Mu::IOModule(context, "io");
    Module* image    = new Mu::ImageModule(context, "image");
    Module* sys      = new Mu::SystemModule(context, "system");
    Module* enc      = new Mu::SystemModule(context, "encoding");
    Module* qt       = new Mu::qtModule(context, "qt");

    context->globalScope()->addSymbol(autodoc);
    context->globalScope()->addSymbol(image);
    context->globalScope()->addSymbol(io);
    context->globalScope()->addSymbol(sys);
    context->globalScope()->addSymbol(enc);
    context->globalScope()->addSymbol(qt);
#endif

    context->debugging(true);

    if (verifyfile)
    {
        verifyFile(verifyfile);
        exit(0);
    }

    try
    {
        Context::PrimaryBit fence(context, true);

        if (!infiles.size())
        {
            if (verbose) cout << "INFO: parsing stdin" << endl;
            context->parseStdin(process);
        }
        else
        {
            for (int i=0; i < infiles.size(); i++)
            {
                if (verbose) cout << "INFO: parsing " << infiles[i] << endl;
                Context::SourceFileScope fileScope(context, 
                                                   context->internName(infiles[i].c_str()));
                context->parseFile(process, infiles[i].c_str());
            }
        }
    }
    catch (Exception& exc)
    {
        cerr << "ERROR: " << exc.what() << endl;
        exit(-1);
    }
    catch (std::exception& exc)
    {
        cerr << "ERROR: (std) " << exc.what() << endl;
        exit(-1);
    }
    catch (...)
    {
        cerr << "ERROR: Uncaught exception" << endl;
        exit(-1);
    }

    if (!process)
    {
	cout << "ERROR: Parse Failed\n" << flush;
	return -1;
    }

    try
    {
        writeToFile(outfile, docfile);
    }
    catch (std::exception& exc)
    {
        cout << "ERROR: caught: " << exc.what() << endl;
    }
    catch (...)
    {
        cout << "ERROR: uncaught exception" << endl;
    }

    return 0;
}

