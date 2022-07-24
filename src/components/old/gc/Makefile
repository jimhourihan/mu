#  -*- mode: makefile -*-

PROJECT	   = gc
TYPE       = LIBRARY
VERSION    = release-7.2

#OPTFLAGS   = -O3
#OPTFLAGS   = -g 

CFLAGS    += $(addprefix -D,$(DEFS)) 
CXXFLAGS  += $(addprefix -D,$(DEFS))
IPATH     += gc libatomic_ops-1.2/src 

CFLAGS_CLANG = -Wno-incompatible-pointer-types \
	       -Wno-deprecated-declarations


#
#   We don't want global C++ new and delete
#
#CXXFILES   = gc_cpp

CFILES_PTHREAD = pthread_support pthread_stop_world pthread_start
CFILES_DARWIN  = $(CFILES_PTHREAD) darwin_stop_world
CFILES_LINUX   = $(CFILES_PTHREAD)
CFILES_WINDOWS = win32_threads

CFILES    = allchblk alloc blacklst checksums dbg_mlc \
	    dyn_load finalize gc_dlopen gcj_mlc headers malloc \
	    mallocx mark mark_rts misc new_hblk obj_map \
	    os_dep pcr_interface ptr_chck real_malloc reclaim \
	    specific stubborn typd_mlc backgraph \
	    thread_local_alloc mach_dep

SFILES_LINUX_IA64 = ia64_save_regs_in_stack

include $(SRC_ROOT)/build/Makefile.master

#
#   Platform neutral. The first group of defs basically determines the
#   main features of the collector. In our case we want interior
#   pointers to be considered, parallel marking (which means more
#   threads unforunately), and atomic uncollectable (which may not be
#   used anymore), and esp thread local allocation which hugely
#   increases allocation speed when running in parallel.
#

DEFS     += ALL_INTERIOR_POINTERS=1			\
	    THREAD_LOCAL_ALLOC=1			\
	    GC_THREADS=1				\
	    GC_VERSION_MAJOR=7				\
	    GC_VERSION_MINOR=2				\
	    VERSION=\"7.2\"				\
	    PACKAGE=\"gc\"				\
	    PACKAGE_BUGREPORT=\"Hans.Boehm@hp.com\"	\
	    PACKAGE_NAME=\"gc\"				\
	    PACKAGE_STRING=\"gc\ 7.2\"			\
	    PACKAGE_TARNAME=\"gc\"			\
	    PACKAGE_VERSION=\"7.2\"			\


## ------------------------------ DARWIN ------------------------------
ifeq ($(PLATFORM),DARWIN)
DARWIN_VERSION := $(findstring Version 8.,$(shell uname -v))

DEFS     += GC_DARWIN_THREADS=1				\
	    ATOMIC_UNCOLLECTABLE=1			\
	    GC_GCJ_SUPPORT=1				\
	    HAVE_DLFCN_H=1				\
	    HAVE_INTTYPES_H=1				\
	    HAVE_MEMORY_H=1				\
	    HAVE_STDINT_H=1				\
	    HAVE_STDLIB_H=1				\
	    HAVE_STRINGS_H=1				\
	    HAVE_STRING_H=1				\
	    HAVE_SYS_STAT_H=1				\
	    HAVE_SYS_TYPES_H=1				\
	    HAVE_UNISTD_H=1				\
	    JAVA_FINALIZATION=1				\
	    PIC=1					\
	    NO_EXECUTE_PERMISSION=1			\
	    NO_UCONTEXT=1   \
	    STDC_HEADERS=1				

ifeq ($(ARCH),PPC32)
DEFS 	 += HAS_PPC_THREAD_STATE64_R0=1		\
	    HAS_PPC_THREAD_STATE_R0=1
else
#
#   We're still building for 10.4 target, so this needs to pretend to be
#   Darwin 8 even on Darwin 9
#

ifeq ($(MACOSX_DEPLOYMENT_TARGET),10.4)
DEFS 	 += HAS_X86_THREAD_STATE32_EAX=1
else
DEFS 	 += HAS_X86_THREAD_STATE32___EAX=1
endif

endif # IA32


endif # DARWIN
## --------------------------------------------------------------------

ifeq ($(PLATFORM),LINUX)

DEFS     += GC_GCJ_SUPPORT=1 				\
	    ATOMIC_UNCOLLECTABLE=1			\
	    GC_LINUX_THREADS=1 				\
	    HAVE_DLFCN_H=1 				\
	    HAVE_INTTYPES_H=1 				\
	    HAVE_MEMORY_H=1 				\
	    HAVE_STDINT_H=1 				\
	    HAVE_STDLIB_H=1 				\
	    HAVE_STRINGS_H=1 				\
	    HAVE_STRING_H=1 				\
	    HAVE_SYS_STAT_H=1 				\
	    HAVE_SYS_TYPES_H=1 				\
	    HAVE_UNISTD_H=1 				\
	    JAVA_FINALIZATION=1 			\
	    NO_EXECUTE_PERMISSION=1 			\
	    STDC_HEADERS=1 				\
	    _REENTRANT=1 

endif

ifeq ($(PLATFORM),WINDOWS)
GCFLAGS  += 
DEFS     += GC_BUILD					\
	    GC_NOT_DLL					\
	    _LIB       					\
	    GC_WIN32_THREADS 
endif

