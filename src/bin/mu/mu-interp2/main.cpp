//
//	Copyright (c) 2001 Jim Hourihan
//
//	The coded instructions herein are the sole property of 
//	Jim Hourihan and may not be modified, redistributed, or 
//	used without permission.
//
#include <gc/gc.h>
#include <stdio.h>
#ifdef MU_USE_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif
#if 0
#include <sys/time.h>
#include <sys/resource.h>
#endif
#include <arg.h>
#include <iostream>
#include <sstream>
#define protected public
#include <Mu/Symbol.h>
#undef protected
#include <MuParse/GLRContext.h>
#include <MuLang/MuLangLanguage.h>
#include <MuLang/DynamicArrayType.h>
#include <MuLang/StringType.h>
#include <MuLang/DynamicArray.h>
#include <MuParse/Parse.h>
#include <Mu/Process.h>
#include <Mu/Value.h>
#include <Mu/GarbageCollector.h>
#include <Mu/Type.h>
#include <Mu/NodePrinter.h>
#include <Mu/SymbolTable.h>
#include <Mu/Function.h>
#include <Mu/MachineRep.h>
#include <Mu/NodePrinter.h>
#include <Mu/Thread.h>
#include <Mu/NodeAssembler.h>
#include <Mu/Exception.h>

#ifdef LINKED_MODULES
#include <MuAutoDoc/AutoDocModule.h>
#include <MuSystem/SystemModule.h>
#include <MuIO/IOModule.h>
#include <MuImage/ImageModule.h>
#include <MuEncoding/EncodingModule.h>
#include <MuQt/qtUtils.h>
#include <MuQt/qtModule.h>
#endif

#ifndef RUSAGE_SELF
#define RUSAGE_SELF 0
#endif


using namespace std;
using namespace Mu;
typedef Mu::SymbolTable::SymbolHashTable HT;

#if 0
struct rusage start_usage, end_usage, garbage_usage;
#endif

int noReadline = 1;
int why = 0;
int debug = 0;

GenericMachine* machine=0;
GLRContext*  context=0;
MuLangLanguage* language=0;
Process*       process=0;
Thread*        thread=0;

#if 0
#ifdef MU_USE_BOEHM_COLLECTOR
void * operator new(size_t size) { return GC_MALLOC(size); }
void * operator new[](size_t size) { return GC_MALLOC(size); }
void operator delete(void *pnt) { /*free(pnt);*/ }
void operator delete[](void *pnt) { /*free(pnt);*/ }
#endif
#endif

#if 0
//----------------------------------------------------------------------

double
seconds(timeval start, timeval end)
{
    return double(end.tv_sec) + double(end.tv_usec)/1000000.0	
	 - double(start.tv_sec) - double(start.tv_usec)/1000000.0;
}
#endif

//----------------------------------------------------------------------

int 
getline(char *buffer, int max_size)
{
    int i = 0;

    for (;i < max_size; i++)
    {
	if (!cin.eof() && !cin.fail())
	{
            char c;
	    cin.get(c);
            if (c == '\n')
            {
                buffer[i] = 0;
                return i;
            }
            else
            {
                buffer[i] = c;
            }
	}
	else
	{
	    break;
	}
    }

    if (i)
    {
	if (i != max_size) i--;
	return i;
    }
    else
    {
	return 0;
    }
}


//----------------------------------------------------------------------

void
dumpSymbols(Symbol *s, int depth)
{
    for (int i=0; i<depth; i++) cout << " ";
    cout << hex << s << dec << " ";
    s->output(cout);
    cout << endl;

    if (s->symbolTable())
    {
	HT& table = s->symbolTable()->hashTable();

	for (HT::Iterator it(table); it; ++it)
	{
	    cout << it.index() << ":";
	    for (Symbol *ss = (*it); ss; ss = ss->nextOverload())
	    {
		dumpSymbols(ss,depth+1);
	    }
	}
    }
}

//----------------------------------------------------------------------

void
interactiveMu()
{
    char temp[1024];
#ifndef MU_USE_READLINE
    noReadline = 1;
#endif

    while (1)
    {
        char* line = 0;

        if (noReadline)
        {
            cout << "mu> " << flush;
            size_t s = getline(temp, 1024);
            if (!s) line = 0;
            else line = temp;
        }
        else
        {
#ifdef MU_USE_READLINE
            line = readline ("mu> ");
            if (!line) exit(0);
#endif
        }

        if (!line || !*line) continue;

#ifdef MU_USE_READLINE
        if (!noReadline) add_history(line);
#endif

        string statement(line);
        //statement.push_back(';');
        istringstream str(statement);

        context->setInput(str);
        NodeAssembler assembler(context, process);
        assembler.throwOnError(true);

        try
        {
            if (Process *p = GLRParse("input", &assembler))
            {
                if (p->rootNode())
                {
                    Value v = p->evaluate(thread);
                    const Type *type = thread->returnValueType();
                    
                    if (!thread->uncaughtException() &&
                        type != context->voidType() &&
                        !type->isTypePattern())
                    {
                        type->output(cout);
                        cout << " => ";
                        type->outputValue(cout,v);
                        cout << endl << flush;
                    }
                }
            }
            else
            {
                cout << "nil" << endl;
            }
        }
        catch (...)
        {
            cout << "=> ERROR" << endl;
        }
    }
}

//----------------------------------------------------------------------

#ifdef PLATFORM_WINDOWS
extern "C" void ptw32_processInitialize(void);
#endif

int
main(int argc, char **argv)
{
//#ifdef PLATFORM_WINDOWS
    //ptw32_processInitialize();
//#endif

    char* inFile = 0;
    char* printFunc = 0;
    char* streamName = 0;
    int print = 0;
    int symbols = 0;
    int noeval = 0;
    int callmain = 0;
    int noninteractive = 0;
    int usage = 0;
    int notruncate = 0;

    GarbageCollector::init();

    if (arg_parse
	(argc, argv,
	 "", "Usage: %s [options]", argv[0],
	 "[%S]", &inFile, "input .mu source file",
	 "-print", ARG_FLAG(&print), "print parse tree in lispy form",
	 "-printFunc %S", &printFunc, "print function in lispy form",
         "-stdin", ARG_FLAG(&noninteractive), "non interactive mode",
         "-no-readline", ARG_FLAG(&noReadline), "don't use readline library",
         "-why", ARG_FLAG(&why), "verbose function choice information",
         "-debug", ARG_FLAG(&debug), "include debug information",
	 "-symbols", ARG_FLAG(&symbols), "output root symbol table",
	 "-noeval", ARG_FLAG(&noeval), "don't evaluate",
         "-notruncate", ARG_FLAG(&notruncate), "don't truncate long output",
         "-usage", ARG_FLAG(&usage), "show usage",
         "-name", ARG_FLAG(&streamName), "name to use for error reporting",
	 "-main", ARG_FLAG(&callmain), "call the main() function if it exists",
	 NULL) < 0)
    {
        exit( -1 );
    }

    machine  = new GenericMachine();
    context  = new GLRContext("basic","main");
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

    context->verbose(why ? true : false);
    context->debugging(debug ? true : false);
    thread = process->newApplicationThread();
    
    if (!noninteractive && !inFile)
    {
        interactiveMu();
    }

    Context::PrimaryBit fence(context, true);

    try
    {
        if (!inFile)
        {
            context->parseStdin(process, streamName);
        }
        else
        {
            context->parseFile(process, inFile);
        }
    }
    catch (Exception& exc)
    {
        cerr << "ERROR: " << exc.what() << endl;
        if (exc.backtrace().size())
        {
            cerr << exc.backtraceAsString();
        }
        else
        {
            cerr << "no backtrace available" << endl;
        }
        exit(-1);
    }
    catch (std::exception& e)
    {
        cerr << "ERROR: (std) " << e.what() << endl;
        exit(-1);
    }
    catch (...)
    {
        cerr << "ERROR: Uncaught exception" << endl;
        exit(-1);
    }
	
    if (symbols)
    {
	cout << "SYMBOLS\n" << flush;
	cout << "-------\n" << flush;
	dumpSymbols(context->globalScope(),0);
	cout << endl << flush;
    }

    if (process->rootNode())
    {
	if (print)
	{
	    cout << "\nNODE TREE\n" << flush;
	    NodePrinter printer(process->rootNode(), cout,
				NodePrinter::Lispy);
	    printer.traverse();
            cout << endl;
	}

	
#if 0
	getrusage(RUSAGE_SELF, &start_usage);
#endif

	if (!noeval)
	{
	    Value v = process->evaluate(thread);

            if (const Type *type = thread->returnValueType())
            {
                if (!type->isTypePattern())
                {
                    //type->output(cout);
                    cout << "result";
                    cout << " => ";
                    type->outputValue(cout, v, notruncate != 0);
                    cout << endl << flush;
                }
            }
            else
            {
                cout << "=> Unknown return type and value" << endl;
            }
	}
    }

    if (printFunc)
    {
	QualifiedName n = context->internName(printFunc);

        if (const Symbol *sym =
            context->globalScope()->findSymbolByQualifiedName(n, false))
        {
            for (const Symbol *s = sym->firstOverload(); s; s = s->nextOverload())
            {
                if (const Mu::Function *f = dynamic_cast<const Mu::Function*>(s))
                {
                    cout << "Function: " << f->name() << " ";

                    if (f->body())
                    {
                        NodePrinter printer(f->body(), cout,
                                            NodePrinter::Lispy);
                        printer.traverse();
                    }
                    else
                    {
                        cout << " is native";
                    }

                    cout << endl << flush;
                }
            }
        }
    }

    if (callmain)
    {
	if (Name n = context->lookupName("main"))
	{
	    if (Mu::Function *f = 
		context->globalScope()->findSymbolOfType<Mu::Function>(n))
	    {
		StringType *stype = context->globalScope()->
		    findSymbolOfType<StringType>(context->lookupName("string"));

		DynamicArrayType *arrayType = 
                    static_cast<DynamicArrayType*>(context->arrayType(stype, 1, 0));
		DynamicArray *array = new DynamicArray(arrayType, 1);

		array->resize(argc);

		for (int i=0; i < argc; i++)
		{
		    StringType::String *s = stype->allocate(argv[i]);
		    array->element<StringType::String*>(i) = s;
		}

		cout << "RUNNING MAIN:\n";

		Mu::Function::ArgumentVector vargs;
		vargs.push_back(Value(array));
		process->call(thread, f, vargs);
	    }
	}
    }

#if 0
    getrusage(RUSAGE_SELF, &end_usage);
    GarbageCollector::collect();
    getrusage(RUSAGE_SELF, &garbage_usage);

    if (usage && (!noeval || callmain))
    {
	cout << "EVALUATION USAGE: "
	     << seconds(start_usage.ru_utime, end_usage.ru_utime)
	     << " user, "
	     << seconds(start_usage.ru_stime, end_usage.ru_stime)
	     << " system.\n";

	cout << "FINAL GARBAGE USAGE: "
	     << seconds(end_usage.ru_utime, garbage_usage.ru_utime)
	     << " user, "
	     << seconds(end_usage.ru_stime, garbage_usage.ru_stime)
	     << " system.\n";
    }
#endif


    return 0;
}

