PROJECT     = "stl_ext"
TYPE        = Types.LIBRARY

CXX_FLAGS = "-DPLATFORM_DARWIN"
CXX_FILES = ["string_algo.cpp", "block_alloc_arena.cpp",
             "fixed_block_allocator.cpp", "fixed_block_arena.cpp",
             "hash_table.cpp", "thread_group.cpp",
             "string_hash_table.cpp"]
