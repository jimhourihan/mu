#  -*- mode: makefile -*-
# 
#  Copyright (c) 2001 Tweak Films.
#  All rights reserved. 
# 

PROJECT    = stl_ext
TYPE       = SHARED_LIBRARY

CXXFILES   = hash_table string_hash_table string_algo thread_group \
	    fixed_block_allocator block_alloc_arena fixed_block_arena 

LIBS_WINDOWS = win_pthreads nedmalloc
LIBS_LINUX = rt nedmalloc
CXXFLAGS_WINDOWS = -DSTL_EXT_BUILD=1

include $(SRC_ROOT)/build/Makefile.master
