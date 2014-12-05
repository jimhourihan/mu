// muc GENERATED INTERMEDIATE FILE
// Aug 15 2008, 08:49:57
#include <MuLang/Native.h>

using namespace Mu;

// Globals/Constants
struct ModuleGlobals
{
    Pointer cn268b18; // string
    Pointer cn268b1a; // string
    Pointer cn268b34; // string
};

static ModuleGlobals globals;
class mandelbrot : public Module
{ public:
    mandelbrot(Context* c) : Module("mandelbrot",c) {}
    virtual ~mandelbrot() {}
    virtual void load();
};


// PROTO ----------------------------------------
NODE_DECLARATION(NODE_mandelbrot_doit_void, void);
void mandelbrot_doit_void(Mu::Thread& NODE_THREAD);
NODE_DECLARATION(NODE_mandelbrot_test_int_float_float, int);
int mandelbrot_test_int_float_float(Mu::Thread& NODE_THREAD, float x, float y);
// NATIVE ----------------------------------------
void mandelbrot_doit_void(Mu::Thread& NODE_THREAD)
{
    float x;
    int i;
    float y;
    float& n26ec11 = y;
    const float n268b3e = -39.0f;
    float& n26ec0e = EQ__floatAmp__floatAmp__float(NODE_THREAD, n26ec11, n268b3e);
    for(;;)
    {
        const float n26ec09 = y;
        const float n268b38 = 39.0f;
        const bool n26ec2e = LT__bool_float_float(NODE_THREAD, n26ec09, n268b38);
        if (!(n26ec2e)) break;
        const Pointer n268b34 = globals.cn268b34;
        print_void_string(NODE_THREAD, n268b34);
        float& n26ecda = x;
        const float n268b2c = -39.0f;
        float& n26ece1 = EQ__floatAmp__floatAmp__float(NODE_THREAD, n26ecda, n268b2c);
        for(;;)
        {
            const float n26ecec = x;
            const float n268b26 = 39.0f;
            const bool n26ecf2 = LT__bool_float_float(NODE_THREAD, n26ecec, n268b26);
            if (!(n26ecf2)) break;
            {
                int& n26ec87 = i;
                const float n26ecf3 = x;
                const float n268b22 = 40.0f;
                const float n26eca1 = Slash__float_float_float(NODE_THREAD, n26ecf3, n268b22);
                const float n26ec9c = y;
                const float n268b20 = 40.0f;
                const float n26ec9a = Slash__float_float_float(NODE_THREAD, n26ec9c, n268b20);
                const int n26ec92 = mandelbrot_test_int_float_float(NODE_THREAD, n26eca1, n26ec9a);
                int& n26ec83 = EQ__intAmp__intAmp__int(NODE_THREAD, n26ec87, n26ec92);
            }
            const int n26ec77 = i;
            const int n268b1c = 0;
            const bool n26ec68 = EQ_EQ__bool_int_int(NODE_THREAD, n26ec77, n268b1c);
            if (n26ec68)
            {
                const Pointer n268b1a = globals.cn268b1a;
                print_void_string(NODE_THREAD, n268b1a);

            }
            else
            {
                const Pointer n268b18 = globals.cn268b18;
                print_void_string(NODE_THREAD, n268b18);

            }
            float& n26c35a = x;
            const float n26ecff = postPlus_Plus__float_floatAmp_(NODE_THREAD, n26c35a);
        }
        float& n26ec31 = y;
        const float n26ec38 = postPlus_Plus__float_floatAmp_(NODE_THREAD, n26ec31);
    }
}

int mandelbrot_test_int_float_float(Mu::Thread& NODE_THREAD, float x, float y)
{
    float zr;
    int i;
    float zr2;
    float temp;
    float zi2;
    float ci;
    float cr;
    float zi;
    {
        float& n26c339 = cr;
        const float n26c368 = y;
        const float n268b60 = 0.5f;
        const float n26c32e = Minus__float_float_float(NODE_THREAD, n26c368, n268b60);
        float& n26c34b = EQ__floatAmp__floatAmp__float(NODE_THREAD, n26c339, n26c32e);
        float& n26c342 = ci;
        const float n26c340 = x;
        float& n26c338 = EQ__floatAmp__floatAmp__float(NODE_THREAD, n26c342, n26c340);
        float& n26c32b = zi;
        const float n268b5c = 0.0f;
        float& n26c326 = EQ__floatAmp__floatAmp__float(NODE_THREAD, n26c32b, n268b5c);
        float& n26c31e = zr;
        const float n268b5a = 0.0f;
        float& n26c319 = EQ__floatAmp__floatAmp__float(NODE_THREAD, n26c31e, n268b5a);
    }
    int& n26c303 = i;
    const int n268b56 = 0;
    int& n26c301 = EQ__intAmp__intAmp__int(NODE_THREAD, n26c303, n268b56);
    for(;;)
    {
        const int n26c315 = i;
        const int n268b52 = 1000;
        const bool n26c32a = LT_EQ__bool_int_int(NODE_THREAD, n26c315, n268b52);
        if (!(n26c32a)) break;
        {
            float& n26c360 = temp;
            const float n26c3a8 = zr;
            const float n268a47 = zi;
            const float n26c33c = Star__float_float_float(NODE_THREAD, n26c3a8, n268a47);
            float& n26c370 = EQ__floatAmp__floatAmp__float(NODE_THREAD, n26c360, n26c33c);
            float& n26ecfd = zr2;
            const float n26ae8e = zr;
            const float n26aed1 = zr;
            const float n26c345 = Star__float_float_float(NODE_THREAD, n26ae8e, n26aed1);
            float& n26ecfa = EQ__floatAmp__floatAmp__float(NODE_THREAD, n26ecfd, n26c345);
            float& n26eced = zi2;
            const float n26ecf6 = zi;
            const float n26ecf5 = zi;
            const float n26ecf1 = Star__float_float_float(NODE_THREAD, n26ecf6, n26ecf5);
            float& n26ecea = EQ__floatAmp__floatAmp__float(NODE_THREAD, n26eced, n26ecf1);
        }
        float& n26ece4 = zr;
        const float n26ece3 = zr2;
        const float n26ece2 = zi2;
        const float n26ecdf = Minus__float_float_float(NODE_THREAD, n26ece3, n26ece2);
        const float n26ecdc = cr;
        const float n26ec82 = Plus__float_float_float(NODE_THREAD, n26ecdf, n26ecdc);
        float& n26ec7d = EQ__floatAmp__floatAmp__float(NODE_THREAD, n26ece4, n26ec82);
        float& n26ec7a = zi;
        const float n26ec79 = temp;
        const float n26ec78 = temp;
        const float n26ec73 = Plus__float_float_float(NODE_THREAD, n26ec79, n26ec78);
        const float n26ec70 = ci;
        const float n26ec6b = Plus__float_float_float(NODE_THREAD, n26ec73, n26ec70);
        float& n26ec66 = EQ__floatAmp__floatAmp__float(NODE_THREAD, n26ec7a, n26ec6b);
        const float n26ec63 = zi2;
        const float n26ec62 = zr2;
        const float n26ec5d = Plus__float_float_float(NODE_THREAD, n26ec63, n26ec62);
        const float n268b4c = 16.0f;
        const bool n26ec40 = GT__bool_float_float(NODE_THREAD, n26ec5d, n268b4c);
        if (n26ec40)
        {
            const int n26ec3b = i;
            return n26ec3b;

        }
        int& n26c302 = i;
        const int n26c3eb = postPlus_Plus__int_intAmp_(NODE_THREAD, n26c302);
    }
    const int n268b4a = 0;
    return n268b4a;
}

// NODES ----------------------------------------
NODE_IMPLEMENTATION(NODE_mandelbrot_doit_void, void)
{
    mandelbrot_doit_void(NODE_THREAD);
}

NODE_IMPLEMENTATION(NODE_mandelbrot_test_int_float_float, int)
{
    float a0 = NODE_ARG(0, float);
    float a1 = NODE_ARG(1, float);
    NODE_RETURN(mandelbrot_test_int_float_float(NODE_THREAD, a0, a1));
}

void
mandelbrot::load()
{
    USING_MU_FUNCTION_SYMBOLS;MuLangContext* c = (MuLangContext*)(globalModule()->context());Symbol* S = this;
    {
        Function* F = new Function("doit", NODE_mandelbrot_doit_void, 0,
                                   Return, "void",
                                   Compiled, mandelbrot_doit_void, 
                                   End);
        S->addSymbol(F);
        {
            Symbol* S = F;
        }
    }
    {
        Function* F = new Function("test", NODE_mandelbrot_test_int_float_float, 0,
                                   Return, "int",
                                   Compiled, mandelbrot_test_int_float_float, 
                                   Parameters, 
                                   new Param("x", "float"),
                                   new Param("y", "float"),
                                   End);
        S->addSymbol(F);
        {
            Symbol* S = F;
        }
    }
}

extern "C" {
Module*
MuInitialize(const char* name, Context* c, Process* p)
{ USING_MU_FUNCTION_SYMBOLS;
    Symbol *s = c->globalScope();
    Thread *thread__ = p->newApplicationThread();
    Thread& thread_ = *thread__;
// ADD MODULE
    Module* __module = new mandelbrot(c);
    s->addSymbol(__module);
// CONSTRUCT CONSTANTS
    const Pointer n268b18 = MU_NEW_STRING(" ");
    p->constants().push_back((Object*)(globals.cn268b18 = n268b18));
    const Pointer n268b1a = MU_NEW_STRING("*");
    p->constants().push_back((Object*)(globals.cn268b1a = n268b1a));
    const Pointer n268b34 = MU_NEW_STRING("\n");
    p->constants().push_back((Object*)(globals.cn268b34 = n268b34));
// PROLOG
    p->releaseApplicationThread(thread__);
    return __module;
}
};
