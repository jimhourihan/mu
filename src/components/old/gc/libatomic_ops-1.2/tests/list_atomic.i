# 1 "list_atomic.c"
# 1 "<built-in>"
# 1 "<command line>"
# 1 "list_atomic.c"
# 1 "../src/atomic_ops.h" 1
# 27 "../src/atomic_ops.h"
# 1 "/usr/include/assert.h" 1 3 4
# 42 "/usr/include/assert.h" 3 4
# 1 "/usr/include/sys/cdefs.h" 1 3 4
# 43 "/usr/include/assert.h" 2 3 4
# 28 "../src/atomic_ops.h" 2
# 1 "/usr/lib/gcc/i686-apple-darwin9/4.0.1/include/stddef.h" 1 3 4
# 152 "/usr/lib/gcc/i686-apple-darwin9/4.0.1/include/stddef.h" 3 4
typedef long int ptrdiff_t;
# 214 "/usr/lib/gcc/i686-apple-darwin9/4.0.1/include/stddef.h" 3 4
typedef long unsigned int size_t;
# 326 "/usr/lib/gcc/i686-apple-darwin9/4.0.1/include/stddef.h" 3 4
typedef int wchar_t;
# 29 "../src/atomic_ops.h" 2
# 197 "../src/atomic_ops.h"
# 1 "../src/atomic_ops/sysdeps/gcc/x86_64.h" 1
# 24 "../src/atomic_ops/sysdeps/gcc/x86_64.h"
# 1 "../src/atomic_ops/sysdeps/gcc/../all_aligned_atomic_load_store.h" 1
# 28 "../src/atomic_ops/sysdeps/gcc/../all_aligned_atomic_load_store.h"
# 1 "../src/atomic_ops/sysdeps/gcc/../aligned_atomic_load_store.h" 1
# 28 "../src/atomic_ops/sysdeps/gcc/../aligned_atomic_load_store.h"
static __inline size_t
AO_load(const volatile size_t *addr)
{
  ((void)0);


  return *(size_t *)addr;
}



static __inline void
AO_store(volatile size_t *addr, size_t new_val)
{
  ((void)0);
  (*(size_t *)addr) = new_val;
}
# 29 "../src/atomic_ops/sysdeps/gcc/../all_aligned_atomic_load_store.h" 2
# 1 "../src/atomic_ops/sysdeps/gcc/../char_atomic_load_store.h" 1
# 28 "../src/atomic_ops/sysdeps/gcc/../char_atomic_load_store.h"
static __inline unsigned char
AO_char_load(const volatile unsigned char *addr)
{


  return (*(const unsigned char *)addr);
}



static __inline void
AO_char_store(volatile unsigned char *addr, unsigned char new_val)
{
  (*(unsigned char *)addr) = new_val;
}
# 30 "../src/atomic_ops/sysdeps/gcc/../all_aligned_atomic_load_store.h" 2
# 1 "../src/atomic_ops/sysdeps/gcc/../short_aligned_atomic_load_store.h" 1
# 28 "../src/atomic_ops/sysdeps/gcc/../short_aligned_atomic_load_store.h"
static __inline unsigned short
AO_short_load(const volatile unsigned short *addr)
{
  ((void)0);


  return (*(unsigned short *)addr);
}



static __inline void
AO_short_store(volatile unsigned short *addr, unsigned short new_val)
{
  ((void)0);
  (*(unsigned short *)addr) = new_val;
}
# 31 "../src/atomic_ops/sysdeps/gcc/../all_aligned_atomic_load_store.h" 2
# 1 "../src/atomic_ops/sysdeps/gcc/../int_aligned_atomic_load_store.h" 1
# 28 "../src/atomic_ops/sysdeps/gcc/../int_aligned_atomic_load_store.h"
static __inline unsigned int
AO_int_load(const volatile unsigned int *addr)
{
  ((void)0);


  return (*(unsigned int *)addr);
}



static __inline void
AO_int_store(volatile unsigned int *addr, unsigned int new_val)
{
  ((void)0);
  (*(unsigned int *)addr) = new_val;
}
# 31 "../src/atomic_ops/sysdeps/gcc/../all_aligned_atomic_load_store.h" 2
# 25 "../src/atomic_ops/sysdeps/gcc/x86_64.h" 2
# 33 "../src/atomic_ops/sysdeps/gcc/x86_64.h"
# 1 "../src/atomic_ops/sysdeps/gcc/../ordered_except_wr.h" 1
# 30 "../src/atomic_ops/sysdeps/gcc/../ordered_except_wr.h"
# 1 "../src/atomic_ops/sysdeps/gcc/../read_ordered.h" 1
# 30 "../src/atomic_ops/sysdeps/gcc/../read_ordered.h"
static __inline void
AO_nop_read(void)
{
  __asm__ __volatile__("" : : : "memory");
}





static __inline size_t
AO_load_read(const volatile size_t *addr)
{
  size_t result = AO_load(addr);
  __asm__ __volatile__("" : : : "memory");
  return result;
}
# 56 "../src/atomic_ops/sysdeps/gcc/../read_ordered.h"
static __inline size_t
AO_char_load_read(const volatile unsigned char *addr)
{
  size_t result = AO_char_load(addr);
  __asm__ __volatile__("" : : : "memory");
  return result;
}
# 72 "../src/atomic_ops/sysdeps/gcc/../read_ordered.h"
static __inline size_t
AO_short_load_read(const volatile unsigned short *addr)
{
  size_t result = AO_short_load(addr);
  __asm__ __volatile__("" : : : "memory");
  return result;
}
# 88 "../src/atomic_ops/sysdeps/gcc/../read_ordered.h"
static __inline size_t
AO_int_load_read(const volatile unsigned int *addr)
{
  size_t result = AO_int_load(addr);
  __asm__ __volatile__("" : : : "memory");
  return result;
}
# 31 "../src/atomic_ops/sysdeps/gcc/../ordered_except_wr.h" 2

static __inline void
AO_nop_write(void)
{
  __asm__ __volatile__("" : : : "memory");


}





static __inline void
AO_store_write(volatile size_t *addr, size_t val)
{
  __asm__ __volatile__("" : : : "memory");
  AO_store(addr, val);
}
# 59 "../src/atomic_ops/sysdeps/gcc/../ordered_except_wr.h"
static __inline void
AO_char_store_write(volatile unsigned char *addr, unsigned char val)
{
  __asm__ __volatile__("" : : : "memory");
  AO_char_store(addr, val);
}
# 74 "../src/atomic_ops/sysdeps/gcc/../ordered_except_wr.h"
static __inline void
AO_short_store_write(volatile unsigned short *addr, unsigned short val)
{
  __asm__ __volatile__("" : : : "memory");
  AO_short_store(addr, val);
}
# 89 "../src/atomic_ops/sysdeps/gcc/../ordered_except_wr.h"
static __inline void
AO_int_store_write(volatile unsigned int *addr, unsigned int val)
{
  __asm__ __volatile__("" : : : "memory");
  AO_int_store(addr, val);
}
# 34 "../src/atomic_ops/sysdeps/gcc/x86_64.h" 2

# 1 "../src/atomic_ops/sysdeps/gcc/../test_and_set_t_is_char.h" 1
# 30 "../src/atomic_ops/sysdeps/gcc/../test_and_set_t_is_char.h"
typedef enum {AO_BYTE_TS_clear = 0, AO_BYTE_TS_set = 0xff} AO_BYTE_TS_val;
# 36 "../src/atomic_ops/sysdeps/gcc/x86_64.h" 2

# 1 "../src/atomic_ops/sysdeps/gcc/../standard_ao_double_t.h" 1
# 9 "../src/atomic_ops/sysdeps/gcc/../standard_ao_double_t.h"
# 1 "/usr/lib/gcc/i686-apple-darwin9/4.0.1/include/xmmintrin.h" 1 3 4
# 39 "/usr/lib/gcc/i686-apple-darwin9/4.0.1/include/xmmintrin.h" 3 4
# 1 "/usr/lib/gcc/i686-apple-darwin9/4.0.1/include/mmintrin.h" 1 3 4
# 39 "/usr/lib/gcc/i686-apple-darwin9/4.0.1/include/mmintrin.h" 3 4
typedef long long __m64 __attribute__ ((__vector_size__ (8)));


typedef int __v2si __attribute__ ((__vector_size__ (8)));
typedef short __v4hi __attribute__ ((__vector_size__ (8)));
typedef char __v8qi __attribute__ ((__vector_size__ (8)));







static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_empty (void)
{
  __builtin_ia32_emms ();
}

static __inline void __attribute__((__always_inline__, __nodebug__))
_m_empty (void)
{
  _mm_empty ();
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_cvtsi32_si64 (int __i)
{
  return (__m64) __builtin_ia32_vec_init_v2si (__i, 0);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_from_int (int __i)
{
  return _mm_cvtsi32_si64 (__i);
}





static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_from_int64 (long long __i)
{
  return (__m64) __i;
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_cvtsi64_m64 (long long __i)
{
  return (__m64) __i;
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_cvtsi64x_si64 (long long __i)
{
  return (__m64) __i;
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_set_pi64x (long long __i)
{
  return (__m64) __i;
}



static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_cvtsi64_si32 (__m64 __i)
{
  return __builtin_ia32_vec_ext_v2si ((__v2si)__i, 0);
}

static __inline int __attribute__((__always_inline__, __nodebug__))
_m_to_int (__m64 __i)
{
  return _mm_cvtsi64_si32 (__i);
}





static __inline long long __attribute__((__always_inline__, __nodebug__))
_m_to_int64 (__m64 __i)
{
  return (long long)__i;
}

static __inline long long __attribute__((__always_inline__, __nodebug__))
_mm_cvtm64_si64 (__m64 __i)
{
  return (long long)__i;
}


static __inline long long __attribute__((__always_inline__, __nodebug__))
_mm_cvtsi64_si64x (__m64 __i)
{
  return (long long)__i;
}





static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_packs_pi16 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_packsswb ((__v4hi)__m1, (__v4hi)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_packsswb (__m64 __m1, __m64 __m2)
{
  return _mm_packs_pi16 (__m1, __m2);
}




static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_packs_pi32 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_packssdw ((__v2si)__m1, (__v2si)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_packssdw (__m64 __m1, __m64 __m2)
{
  return _mm_packs_pi32 (__m1, __m2);
}




static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_packs_pu16 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_packuswb ((__v4hi)__m1, (__v4hi)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_packuswb (__m64 __m1, __m64 __m2)
{
  return _mm_packs_pu16 (__m1, __m2);
}



static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_unpackhi_pi8 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_punpckhbw ((__v8qi)__m1, (__v8qi)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_punpckhbw (__m64 __m1, __m64 __m2)
{
  return _mm_unpackhi_pi8 (__m1, __m2);
}



static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_unpackhi_pi16 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_punpckhwd ((__v4hi)__m1, (__v4hi)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_punpckhwd (__m64 __m1, __m64 __m2)
{
  return _mm_unpackhi_pi16 (__m1, __m2);
}



static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_unpackhi_pi32 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_punpckhdq ((__v2si)__m1, (__v2si)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_punpckhdq (__m64 __m1, __m64 __m2)
{
  return _mm_unpackhi_pi32 (__m1, __m2);
}



static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_unpacklo_pi8 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_punpcklbw ((__v8qi)__m1, (__v8qi)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_punpcklbw (__m64 __m1, __m64 __m2)
{
  return _mm_unpacklo_pi8 (__m1, __m2);
}



static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_unpacklo_pi16 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_punpcklwd ((__v4hi)__m1, (__v4hi)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_punpcklwd (__m64 __m1, __m64 __m2)
{
  return _mm_unpacklo_pi16 (__m1, __m2);
}



static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_unpacklo_pi32 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_punpckldq ((__v2si)__m1, (__v2si)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_punpckldq (__m64 __m1, __m64 __m2)
{
  return _mm_unpacklo_pi32 (__m1, __m2);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_add_pi8 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_paddb ((__v8qi)__m1, (__v8qi)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_paddb (__m64 __m1, __m64 __m2)
{
  return _mm_add_pi8 (__m1, __m2);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_add_pi16 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_paddw ((__v4hi)__m1, (__v4hi)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_paddw (__m64 __m1, __m64 __m2)
{
  return _mm_add_pi16 (__m1, __m2);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_add_pi32 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_paddd ((__v2si)__m1, (__v2si)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_paddd (__m64 __m1, __m64 __m2)
{
  return _mm_add_pi32 (__m1, __m2);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_add_si64 (__m64 __m1, __m64 __m2)
{

  return (__m64) __builtin_ia32_paddq (__m1, __m2);
}



static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_adds_pi8 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_paddsb ((__v8qi)__m1, (__v8qi)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_paddsb (__m64 __m1, __m64 __m2)
{
  return _mm_adds_pi8 (__m1, __m2);
}



static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_adds_pi16 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_paddsw ((__v4hi)__m1, (__v4hi)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_paddsw (__m64 __m1, __m64 __m2)
{
  return _mm_adds_pi16 (__m1, __m2);
}



static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_adds_pu8 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_paddusb ((__v8qi)__m1, (__v8qi)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_paddusb (__m64 __m1, __m64 __m2)
{
  return _mm_adds_pu8 (__m1, __m2);
}



static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_adds_pu16 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_paddusw ((__v4hi)__m1, (__v4hi)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_paddusw (__m64 __m1, __m64 __m2)
{
  return _mm_adds_pu16 (__m1, __m2);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_sub_pi8 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_psubb ((__v8qi)__m1, (__v8qi)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_psubb (__m64 __m1, __m64 __m2)
{
  return _mm_sub_pi8 (__m1, __m2);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_sub_pi16 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_psubw ((__v4hi)__m1, (__v4hi)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_psubw (__m64 __m1, __m64 __m2)
{
  return _mm_sub_pi16 (__m1, __m2);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_sub_pi32 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_psubd ((__v2si)__m1, (__v2si)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_psubd (__m64 __m1, __m64 __m2)
{
  return _mm_sub_pi32 (__m1, __m2);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_sub_si64 (__m64 __m1, __m64 __m2)
{

  return (__m64) __builtin_ia32_psubq (__m1, __m2);
}



static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_subs_pi8 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_psubsb ((__v8qi)__m1, (__v8qi)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_psubsb (__m64 __m1, __m64 __m2)
{
  return _mm_subs_pi8 (__m1, __m2);
}



static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_subs_pi16 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_psubsw ((__v4hi)__m1, (__v4hi)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_psubsw (__m64 __m1, __m64 __m2)
{
  return _mm_subs_pi16 (__m1, __m2);
}



static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_subs_pu8 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_psubusb ((__v8qi)__m1, (__v8qi)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_psubusb (__m64 __m1, __m64 __m2)
{
  return _mm_subs_pu8 (__m1, __m2);
}



static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_subs_pu16 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_psubusw ((__v4hi)__m1, (__v4hi)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_psubusw (__m64 __m1, __m64 __m2)
{
  return _mm_subs_pu16 (__m1, __m2);
}




static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_madd_pi16 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_pmaddwd ((__v4hi)__m1, (__v4hi)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_pmaddwd (__m64 __m1, __m64 __m2)
{
  return _mm_madd_pi16 (__m1, __m2);
}



static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_mulhi_pi16 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_pmulhw ((__v4hi)__m1, (__v4hi)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_pmulhw (__m64 __m1, __m64 __m2)
{
  return _mm_mulhi_pi16 (__m1, __m2);
}



static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_mullo_pi16 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_pmullw ((__v4hi)__m1, (__v4hi)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_pmullw (__m64 __m1, __m64 __m2)
{
  return _mm_mullo_pi16 (__m1, __m2);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_sll_pi16 (__m64 __m, __m64 __count)
{

  return (__m64) __builtin_ia32_psllw ((__v4hi)__m, __count);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_psllw (__m64 __m, __m64 __count)
{
  return _mm_sll_pi16 (__m, __count);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_slli_pi16 (__m64 __m, int __count)
{

  return (__m64) __builtin_ia32_psllwi ((__v4hi)__m, __count);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_psllwi (__m64 __m, int __count)
{
  return _mm_slli_pi16 (__m, __count);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_sll_pi32 (__m64 __m, __m64 __count)
{

  return (__m64) __builtin_ia32_pslld ((__v2si)__m, __count);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_pslld (__m64 __m, __m64 __count)
{
  return _mm_sll_pi32 (__m, __count);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_slli_pi32 (__m64 __m, int __count)
{

  return (__m64) __builtin_ia32_pslldi ((__v2si)__m, __count);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_pslldi (__m64 __m, int __count)
{
  return _mm_slli_pi32 (__m, __count);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_sll_si64 (__m64 __m, __m64 __count)
{

  return (__m64) __builtin_ia32_psllq (__m, __count);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_psllq (__m64 __m, __m64 __count)
{
  return _mm_sll_si64 (__m, __count);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_slli_si64 (__m64 __m, int __count)
{

  return (__m64) __builtin_ia32_psllqi (__m, __count);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_psllqi (__m64 __m, int __count)
{
  return _mm_slli_si64 (__m, __count);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_sra_pi16 (__m64 __m, __m64 __count)
{

  return (__m64) __builtin_ia32_psraw ((__v4hi)__m, __count);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_psraw (__m64 __m, __m64 __count)
{
  return _mm_sra_pi16 (__m, __count);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_srai_pi16 (__m64 __m, int __count)
{

  return (__m64) __builtin_ia32_psrawi ((__v4hi)__m, __count);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_psrawi (__m64 __m, int __count)
{
  return _mm_srai_pi16 (__m, __count);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_sra_pi32 (__m64 __m, __m64 __count)
{

  return (__m64) __builtin_ia32_psrad ((__v2si)__m, __count);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_psrad (__m64 __m, __m64 __count)
{
  return _mm_sra_pi32 (__m, __count);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_srai_pi32 (__m64 __m, int __count)
{

  return (__m64) __builtin_ia32_psradi ((__v2si)__m, __count);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_psradi (__m64 __m, int __count)
{
  return _mm_srai_pi32 (__m, __count);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_srl_pi16 (__m64 __m, __m64 __count)
{

  return (__m64) __builtin_ia32_psrlw ((__v4hi)__m, __count);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_psrlw (__m64 __m, __m64 __count)
{
  return _mm_srl_pi16 (__m, __count);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_srli_pi16 (__m64 __m, int __count)
{

  return (__m64) __builtin_ia32_psrlwi ((__v4hi)__m, __count);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_psrlwi (__m64 __m, int __count)
{
  return _mm_srli_pi16 (__m, __count);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_srl_pi32 (__m64 __m, __m64 __count)
{

  return (__m64) __builtin_ia32_psrld ((__v2si)__m, __count);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_psrld (__m64 __m, __m64 __count)
{
  return _mm_srl_pi32 (__m, __count);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_srli_pi32 (__m64 __m, int __count)
{

  return (__m64) __builtin_ia32_psrldi ((__v2si)__m, __count);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_psrldi (__m64 __m, int __count)
{
  return _mm_srli_pi32 (__m, __count);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_srl_si64 (__m64 __m, __m64 __count)
{

  return (__m64) __builtin_ia32_psrlq (__m, __count);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_psrlq (__m64 __m, __m64 __count)
{
  return _mm_srl_si64 (__m, __count);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_srli_si64 (__m64 __m, int __count)
{

  return (__m64) __builtin_ia32_psrlqi (__m, __count);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_psrlqi (__m64 __m, int __count)
{
  return _mm_srli_si64 (__m, __count);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_and_si64 (__m64 __m1, __m64 __m2)
{
  return __builtin_ia32_pand (__m1, __m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_pand (__m64 __m1, __m64 __m2)
{
  return _mm_and_si64 (__m1, __m2);
}



static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_andnot_si64 (__m64 __m1, __m64 __m2)
{
  return __builtin_ia32_pandn (__m1, __m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_pandn (__m64 __m1, __m64 __m2)
{
  return _mm_andnot_si64 (__m1, __m2);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_or_si64 (__m64 __m1, __m64 __m2)
{
  return __builtin_ia32_por (__m1, __m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_por (__m64 __m1, __m64 __m2)
{
  return _mm_or_si64 (__m1, __m2);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_xor_si64 (__m64 __m1, __m64 __m2)
{
  return __builtin_ia32_pxor (__m1, __m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_pxor (__m64 __m1, __m64 __m2)
{
  return _mm_xor_si64 (__m1, __m2);
}



static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_cmpeq_pi8 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_pcmpeqb ((__v8qi)__m1, (__v8qi)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_pcmpeqb (__m64 __m1, __m64 __m2)
{
  return _mm_cmpeq_pi8 (__m1, __m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_cmpgt_pi8 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_pcmpgtb ((__v8qi)__m1, (__v8qi)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_pcmpgtb (__m64 __m1, __m64 __m2)
{
  return _mm_cmpgt_pi8 (__m1, __m2);
}



static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_cmpeq_pi16 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_pcmpeqw ((__v4hi)__m1, (__v4hi)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_pcmpeqw (__m64 __m1, __m64 __m2)
{
  return _mm_cmpeq_pi16 (__m1, __m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_cmpgt_pi16 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_pcmpgtw ((__v4hi)__m1, (__v4hi)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_pcmpgtw (__m64 __m1, __m64 __m2)
{
  return _mm_cmpgt_pi16 (__m1, __m2);
}



static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_cmpeq_pi32 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_pcmpeqd ((__v2si)__m1, (__v2si)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_pcmpeqd (__m64 __m1, __m64 __m2)
{
  return _mm_cmpeq_pi32 (__m1, __m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_cmpgt_pi32 (__m64 __m1, __m64 __m2)
{
  return (__m64) __builtin_ia32_pcmpgtd ((__v2si)__m1, (__v2si)__m2);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_pcmpgtd (__m64 __m1, __m64 __m2)
{
  return _mm_cmpgt_pi32 (__m1, __m2);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_setzero_si64 (void)
{
  return (__m64)0LL;
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_set_pi32 (int __i1, int __i0)
{
  return (__m64) __builtin_ia32_vec_init_v2si (__i0, __i1);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_set_pi16 (short __w3, short __w2, short __w1, short __w0)
{
  return (__m64) __builtin_ia32_vec_init_v4hi (__w0, __w1, __w2, __w3);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_set_pi8 (char __b7, char __b6, char __b5, char __b4,
      char __b3, char __b2, char __b1, char __b0)
{
  return (__m64) __builtin_ia32_vec_init_v8qi (__b0, __b1, __b2, __b3,
            __b4, __b5, __b6, __b7);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_setr_pi32 (int __i0, int __i1)
{
  return _mm_set_pi32 (__i1, __i0);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_setr_pi16 (short __w0, short __w1, short __w2, short __w3)
{
  return _mm_set_pi16 (__w3, __w2, __w1, __w0);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_setr_pi8 (char __b0, char __b1, char __b2, char __b3,
       char __b4, char __b5, char __b6, char __b7)
{
  return _mm_set_pi8 (__b7, __b6, __b5, __b4, __b3, __b2, __b1, __b0);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_set1_pi32 (int __i)
{
  return _mm_set_pi32 (__i, __i);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_set1_pi16 (short __w)
{
  return _mm_set_pi16 (__w, __w, __w, __w);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_set1_pi8 (char __b)
{
  return _mm_set_pi8 (__b, __b, __b, __b, __b, __b, __b, __b);
}
# 40 "/usr/lib/gcc/i686-apple-darwin9/4.0.1/include/xmmintrin.h" 2 3 4


# 1 "/usr/lib/gcc/i686-apple-darwin9/4.0.1/include/mm_malloc.h" 1 3 4
# 30 "/usr/lib/gcc/i686-apple-darwin9/4.0.1/include/mm_malloc.h" 3 4
# 1 "/usr/include/stdlib.h" 1 3 4
# 61 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/available.h" 1 3 4
# 62 "/usr/include/stdlib.h" 2 3 4

# 1 "/usr/include/_types.h" 1 3 4
# 27 "/usr/include/_types.h" 3 4
# 1 "/usr/include/sys/_types.h" 1 3 4
# 33 "/usr/include/sys/_types.h" 3 4
# 1 "/usr/include/machine/_types.h" 1 3 4
# 34 "/usr/include/machine/_types.h" 3 4
# 1 "/usr/include/i386/_types.h" 1 3 4
# 37 "/usr/include/i386/_types.h" 3 4
typedef signed char __int8_t;



typedef unsigned char __uint8_t;
typedef short __int16_t;
typedef unsigned short __uint16_t;
typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef long long __int64_t;
typedef unsigned long long __uint64_t;

typedef long __darwin_intptr_t;
typedef unsigned int __darwin_natural_t;
# 70 "/usr/include/i386/_types.h" 3 4
typedef int __darwin_ct_rune_t;





typedef union {
 char __mbstate8[128];
 long long _mbstateL;
} __mbstate_t;

typedef __mbstate_t __darwin_mbstate_t;


typedef long int __darwin_ptrdiff_t;





typedef long unsigned int __darwin_size_t;





typedef __builtin_va_list __darwin_va_list;





typedef int __darwin_wchar_t;




typedef __darwin_wchar_t __darwin_rune_t;


typedef int __darwin_wint_t;




typedef unsigned long __darwin_clock_t;
typedef __uint32_t __darwin_socklen_t;
typedef long __darwin_ssize_t;
typedef long __darwin_time_t;
# 35 "/usr/include/machine/_types.h" 2 3 4
# 34 "/usr/include/sys/_types.h" 2 3 4
# 58 "/usr/include/sys/_types.h" 3 4
struct __darwin_pthread_handler_rec
{
 void (*__routine)(void *);
 void *__arg;
 struct __darwin_pthread_handler_rec *__next;
};
struct _opaque_pthread_attr_t { long __sig; char __opaque[56]; };
struct _opaque_pthread_cond_t { long __sig; char __opaque[40]; };
struct _opaque_pthread_condattr_t { long __sig; char __opaque[8]; };
struct _opaque_pthread_mutex_t { long __sig; char __opaque[56]; };
struct _opaque_pthread_mutexattr_t { long __sig; char __opaque[8]; };
struct _opaque_pthread_once_t { long __sig; char __opaque[8]; };
struct _opaque_pthread_rwlock_t { long __sig; char __opaque[192]; };
struct _opaque_pthread_rwlockattr_t { long __sig; char __opaque[16]; };
struct _opaque_pthread_t { long __sig; struct __darwin_pthread_handler_rec *__cleanup_stack; char __opaque[1168]; };
# 94 "/usr/include/sys/_types.h" 3 4
typedef __int64_t __darwin_blkcnt_t;
typedef __int32_t __darwin_blksize_t;
typedef __int32_t __darwin_dev_t;
typedef unsigned int __darwin_fsblkcnt_t;
typedef unsigned int __darwin_fsfilcnt_t;
typedef __uint32_t __darwin_gid_t;
typedef __uint32_t __darwin_id_t;
typedef __uint64_t __darwin_ino64_t;



typedef __uint32_t __darwin_ino_t;

typedef __darwin_natural_t __darwin_mach_port_name_t;
typedef __darwin_mach_port_name_t __darwin_mach_port_t;
typedef __uint16_t __darwin_mode_t;
typedef __int64_t __darwin_off_t;
typedef __int32_t __darwin_pid_t;
typedef struct _opaque_pthread_attr_t
   __darwin_pthread_attr_t;
typedef struct _opaque_pthread_cond_t
   __darwin_pthread_cond_t;
typedef struct _opaque_pthread_condattr_t
   __darwin_pthread_condattr_t;
typedef unsigned long __darwin_pthread_key_t;
typedef struct _opaque_pthread_mutex_t
   __darwin_pthread_mutex_t;
typedef struct _opaque_pthread_mutexattr_t
   __darwin_pthread_mutexattr_t;
typedef struct _opaque_pthread_once_t
   __darwin_pthread_once_t;
typedef struct _opaque_pthread_rwlock_t
   __darwin_pthread_rwlock_t;
typedef struct _opaque_pthread_rwlockattr_t
   __darwin_pthread_rwlockattr_t;
typedef struct _opaque_pthread_t
   *__darwin_pthread_t;
typedef __uint32_t __darwin_sigset_t;
typedef __int32_t __darwin_suseconds_t;
typedef __uint32_t __darwin_uid_t;
typedef __uint32_t __darwin_useconds_t;
typedef unsigned char __darwin_uuid_t[16];
# 28 "/usr/include/_types.h" 2 3 4

typedef int __darwin_nl_item;
typedef int __darwin_wctrans_t;

typedef __uint32_t __darwin_wctype_t;
# 64 "/usr/include/stdlib.h" 2 3 4

# 1 "/usr/include/sys/wait.h" 1 3 4
# 79 "/usr/include/sys/wait.h" 3 4
typedef enum {
 P_ALL,
 P_PID,
 P_PGID
} idtype_t;






typedef __darwin_pid_t pid_t;




typedef __darwin_id_t id_t;
# 116 "/usr/include/sys/wait.h" 3 4
# 1 "/usr/include/sys/signal.h" 1 3 4
# 73 "/usr/include/sys/signal.h" 3 4
# 1 "/usr/include/sys/appleapiopts.h" 1 3 4
# 74 "/usr/include/sys/signal.h" 2 3 4







# 1 "/usr/include/machine/signal.h" 1 3 4
# 34 "/usr/include/machine/signal.h" 3 4
# 1 "/usr/include/i386/signal.h" 1 3 4
# 39 "/usr/include/i386/signal.h" 3 4
typedef int sig_atomic_t;
# 55 "/usr/include/i386/signal.h" 3 4
# 1 "/usr/include/i386/_structs.h" 1 3 4
# 56 "/usr/include/i386/signal.h" 2 3 4
# 35 "/usr/include/machine/signal.h" 2 3 4
# 82 "/usr/include/sys/signal.h" 2 3 4
# 154 "/usr/include/sys/signal.h" 3 4
# 1 "/usr/include/sys/_structs.h" 1 3 4
# 57 "/usr/include/sys/_structs.h" 3 4
# 1 "/usr/include/machine/_structs.h" 1 3 4
# 31 "/usr/include/machine/_structs.h" 3 4
# 1 "/usr/include/i386/_structs.h" 1 3 4
# 38 "/usr/include/i386/_structs.h" 3 4
# 1 "/usr/include/mach/i386/_structs.h" 1 3 4
# 43 "/usr/include/mach/i386/_structs.h" 3 4
struct __darwin_i386_thread_state
{
    unsigned int __eax;
    unsigned int __ebx;
    unsigned int __ecx;
    unsigned int __edx;
    unsigned int __edi;
    unsigned int __esi;
    unsigned int __ebp;
    unsigned int __esp;
    unsigned int __ss;
    unsigned int __eflags;
    unsigned int __eip;
    unsigned int __cs;
    unsigned int __ds;
    unsigned int __es;
    unsigned int __fs;
    unsigned int __gs;
};
# 89 "/usr/include/mach/i386/_structs.h" 3 4
struct __darwin_fp_control
{
    unsigned short __invalid :1,
        __denorm :1,
    __zdiv :1,
    __ovrfl :1,
    __undfl :1,
    __precis :1,
      :2,
    __pc :2,





    __rc :2,






             :1,
      :3;
};
typedef struct __darwin_fp_control __darwin_fp_control_t;
# 147 "/usr/include/mach/i386/_structs.h" 3 4
struct __darwin_fp_status
{
    unsigned short __invalid :1,
        __denorm :1,
    __zdiv :1,
    __ovrfl :1,
    __undfl :1,
    __precis :1,
    __stkflt :1,
    __errsumm :1,
    __c0 :1,
    __c1 :1,
    __c2 :1,
    __tos :3,
    __c3 :1,
    __busy :1;
};
typedef struct __darwin_fp_status __darwin_fp_status_t;
# 191 "/usr/include/mach/i386/_structs.h" 3 4
struct __darwin_mmst_reg
{
 char __mmst_reg[10];
 char __mmst_rsrv[6];
};
# 210 "/usr/include/mach/i386/_structs.h" 3 4
struct __darwin_xmm_reg
{
 char __xmm_reg[16];
};
# 232 "/usr/include/mach/i386/_structs.h" 3 4
struct __darwin_i386_float_state
{
 int __fpu_reserved[2];
 struct __darwin_fp_control __fpu_fcw;
 struct __darwin_fp_status __fpu_fsw;
 __uint8_t __fpu_ftw;
 __uint8_t __fpu_rsrv1;
 __uint16_t __fpu_fop;
 __uint32_t __fpu_ip;
 __uint16_t __fpu_cs;
 __uint16_t __fpu_rsrv2;
 __uint32_t __fpu_dp;
 __uint16_t __fpu_ds;
 __uint16_t __fpu_rsrv3;
 __uint32_t __fpu_mxcsr;
 __uint32_t __fpu_mxcsrmask;
 struct __darwin_mmst_reg __fpu_stmm0;
 struct __darwin_mmst_reg __fpu_stmm1;
 struct __darwin_mmst_reg __fpu_stmm2;
 struct __darwin_mmst_reg __fpu_stmm3;
 struct __darwin_mmst_reg __fpu_stmm4;
 struct __darwin_mmst_reg __fpu_stmm5;
 struct __darwin_mmst_reg __fpu_stmm6;
 struct __darwin_mmst_reg __fpu_stmm7;
 struct __darwin_xmm_reg __fpu_xmm0;
 struct __darwin_xmm_reg __fpu_xmm1;
 struct __darwin_xmm_reg __fpu_xmm2;
 struct __darwin_xmm_reg __fpu_xmm3;
 struct __darwin_xmm_reg __fpu_xmm4;
 struct __darwin_xmm_reg __fpu_xmm5;
 struct __darwin_xmm_reg __fpu_xmm6;
 struct __darwin_xmm_reg __fpu_xmm7;
 char __fpu_rsrv4[14*16];
 int __fpu_reserved1;
};
# 308 "/usr/include/mach/i386/_structs.h" 3 4
struct __darwin_i386_exception_state
{
    unsigned int __trapno;
    unsigned int __err;
    unsigned int __faultvaddr;
};
# 326 "/usr/include/mach/i386/_structs.h" 3 4
struct __darwin_x86_debug_state32
{
 unsigned int __dr0;
 unsigned int __dr1;
 unsigned int __dr2;
 unsigned int __dr3;
 unsigned int __dr4;
 unsigned int __dr5;
 unsigned int __dr6;
 unsigned int __dr7;
};
# 358 "/usr/include/mach/i386/_structs.h" 3 4
struct __darwin_x86_thread_state64
{
 __uint64_t __rax;
 __uint64_t __rbx;
 __uint64_t __rcx;
 __uint64_t __rdx;
 __uint64_t __rdi;
 __uint64_t __rsi;
 __uint64_t __rbp;
 __uint64_t __rsp;
 __uint64_t __r8;
 __uint64_t __r9;
 __uint64_t __r10;
 __uint64_t __r11;
 __uint64_t __r12;
 __uint64_t __r13;
 __uint64_t __r14;
 __uint64_t __r15;
 __uint64_t __rip;
 __uint64_t __rflags;
 __uint64_t __cs;
 __uint64_t __fs;
 __uint64_t __gs;
};
# 413 "/usr/include/mach/i386/_structs.h" 3 4
struct __darwin_x86_float_state64
{
 int __fpu_reserved[2];
 struct __darwin_fp_control __fpu_fcw;
 struct __darwin_fp_status __fpu_fsw;
 __uint8_t __fpu_ftw;
 __uint8_t __fpu_rsrv1;
 __uint16_t __fpu_fop;


 __uint32_t __fpu_ip;
 __uint16_t __fpu_cs;

 __uint16_t __fpu_rsrv2;


 __uint32_t __fpu_dp;
 __uint16_t __fpu_ds;

 __uint16_t __fpu_rsrv3;
 __uint32_t __fpu_mxcsr;
 __uint32_t __fpu_mxcsrmask;
 struct __darwin_mmst_reg __fpu_stmm0;
 struct __darwin_mmst_reg __fpu_stmm1;
 struct __darwin_mmst_reg __fpu_stmm2;
 struct __darwin_mmst_reg __fpu_stmm3;
 struct __darwin_mmst_reg __fpu_stmm4;
 struct __darwin_mmst_reg __fpu_stmm5;
 struct __darwin_mmst_reg __fpu_stmm6;
 struct __darwin_mmst_reg __fpu_stmm7;
 struct __darwin_xmm_reg __fpu_xmm0;
 struct __darwin_xmm_reg __fpu_xmm1;
 struct __darwin_xmm_reg __fpu_xmm2;
 struct __darwin_xmm_reg __fpu_xmm3;
 struct __darwin_xmm_reg __fpu_xmm4;
 struct __darwin_xmm_reg __fpu_xmm5;
 struct __darwin_xmm_reg __fpu_xmm6;
 struct __darwin_xmm_reg __fpu_xmm7;
 struct __darwin_xmm_reg __fpu_xmm8;
 struct __darwin_xmm_reg __fpu_xmm9;
 struct __darwin_xmm_reg __fpu_xmm10;
 struct __darwin_xmm_reg __fpu_xmm11;
 struct __darwin_xmm_reg __fpu_xmm12;
 struct __darwin_xmm_reg __fpu_xmm13;
 struct __darwin_xmm_reg __fpu_xmm14;
 struct __darwin_xmm_reg __fpu_xmm15;
 char __fpu_rsrv4[6*16];
 int __fpu_reserved1;
};
# 517 "/usr/include/mach/i386/_structs.h" 3 4
struct __darwin_x86_exception_state64
{
    unsigned int __trapno;
    unsigned int __err;
    __uint64_t __faultvaddr;
};
# 535 "/usr/include/mach/i386/_structs.h" 3 4
struct __darwin_x86_debug_state64
{
 __uint64_t __dr0;
 __uint64_t __dr1;
 __uint64_t __dr2;
 __uint64_t __dr3;
 __uint64_t __dr4;
 __uint64_t __dr5;
 __uint64_t __dr6;
 __uint64_t __dr7;
};
# 39 "/usr/include/i386/_structs.h" 2 3 4
# 48 "/usr/include/i386/_structs.h" 3 4
struct __darwin_mcontext32
{
 struct __darwin_i386_exception_state __es;
 struct __darwin_i386_thread_state __ss;
 struct __darwin_i386_float_state __fs;
};
# 68 "/usr/include/i386/_structs.h" 3 4
struct __darwin_mcontext64
{
 struct __darwin_x86_exception_state64 __es;
 struct __darwin_x86_thread_state64 __ss;
 struct __darwin_x86_float_state64 __fs;
};
# 91 "/usr/include/i386/_structs.h" 3 4
typedef struct __darwin_mcontext64 *mcontext_t;
# 32 "/usr/include/machine/_structs.h" 2 3 4
# 58 "/usr/include/sys/_structs.h" 2 3 4
# 75 "/usr/include/sys/_structs.h" 3 4
struct __darwin_sigaltstack
{
 void *ss_sp;
 __darwin_size_t ss_size;
 int ss_flags;
};
# 128 "/usr/include/sys/_structs.h" 3 4
struct __darwin_ucontext
{
 int uc_onstack;
 __darwin_sigset_t uc_sigmask;
 struct __darwin_sigaltstack uc_stack;
 struct __darwin_ucontext *uc_link;
 __darwin_size_t uc_mcsize;
 struct __darwin_mcontext64 *uc_mcontext;



};
# 218 "/usr/include/sys/_structs.h" 3 4
typedef struct __darwin_sigaltstack stack_t;
# 227 "/usr/include/sys/_structs.h" 3 4
typedef struct __darwin_ucontext ucontext_t;
# 155 "/usr/include/sys/signal.h" 2 3 4
# 163 "/usr/include/sys/signal.h" 3 4
typedef __darwin_pthread_attr_t pthread_attr_t;




typedef __darwin_sigset_t sigset_t;
# 178 "/usr/include/sys/signal.h" 3 4
typedef __darwin_uid_t uid_t;


union sigval {

 int sival_int;
 void *sival_ptr;
};





struct sigevent {
 int sigev_notify;
 int sigev_signo;
 union sigval sigev_value;
 void (*sigev_notify_function)(union sigval);
 pthread_attr_t *sigev_notify_attributes;
};


typedef struct __siginfo {
 int si_signo;
 int si_errno;
 int si_code;
 pid_t si_pid;
 uid_t si_uid;
 int si_status;
 void *si_addr;
 union sigval si_value;
 long si_band;
 unsigned long __pad[7];
} siginfo_t;
# 292 "/usr/include/sys/signal.h" 3 4
union __sigaction_u {
 void (*__sa_handler)(int);
 void (*__sa_sigaction)(int, struct __siginfo *,
         void *);
};


struct __sigaction {
 union __sigaction_u __sigaction_u;
 void (*sa_tramp)(void *, int, int, siginfo_t *, void *);
 sigset_t sa_mask;
 int sa_flags;
};




struct sigaction {
 union __sigaction_u __sigaction_u;
 sigset_t sa_mask;
 int sa_flags;
};
# 354 "/usr/include/sys/signal.h" 3 4
typedef void (*sig_t)(int);
# 371 "/usr/include/sys/signal.h" 3 4
struct sigvec {
 void (*sv_handler)(int);
 int sv_mask;
 int sv_flags;
};
# 390 "/usr/include/sys/signal.h" 3 4
struct sigstack {
 char *ss_sp;
 int ss_onstack;
};
# 412 "/usr/include/sys/signal.h" 3 4

void (*signal(int, void (*)(int)))(int);

# 117 "/usr/include/sys/wait.h" 2 3 4
# 1 "/usr/include/sys/resource.h" 1 3 4
# 76 "/usr/include/sys/resource.h" 3 4
# 1 "/usr/include/sys/_structs.h" 1 3 4
# 100 "/usr/include/sys/_structs.h" 3 4
struct timeval
{
 __darwin_time_t tv_sec;
 __darwin_suseconds_t tv_usec;
};
# 77 "/usr/include/sys/resource.h" 2 3 4
# 88 "/usr/include/sys/resource.h" 3 4
typedef __uint64_t rlim_t;
# 142 "/usr/include/sys/resource.h" 3 4
struct rusage {
 struct timeval ru_utime;
 struct timeval ru_stime;
# 153 "/usr/include/sys/resource.h" 3 4
 long ru_maxrss;

 long ru_ixrss;
 long ru_idrss;
 long ru_isrss;
 long ru_minflt;
 long ru_majflt;
 long ru_nswap;
 long ru_inblock;
 long ru_oublock;
 long ru_msgsnd;
 long ru_msgrcv;
 long ru_nsignals;
 long ru_nvcsw;
 long ru_nivcsw;


};
# 213 "/usr/include/sys/resource.h" 3 4
struct rlimit {
 rlim_t rlim_cur;
 rlim_t rlim_max;
};
# 235 "/usr/include/sys/resource.h" 3 4

int getpriority(int, id_t);

int getiopolicy_np(int, int);

int getrlimit(int, struct rlimit *) __asm("_" "getrlimit" );
int getrusage(int, struct rusage *);
int setpriority(int, id_t, int);

int setiopolicy_np(int, int, int);

int setrlimit(int, const struct rlimit *) __asm("_" "setrlimit" );

# 118 "/usr/include/sys/wait.h" 2 3 4
# 193 "/usr/include/sys/wait.h" 3 4
# 1 "/usr/include/machine/endian.h" 1 3 4
# 37 "/usr/include/machine/endian.h" 3 4
# 1 "/usr/include/i386/endian.h" 1 3 4
# 99 "/usr/include/i386/endian.h" 3 4
# 1 "/usr/include/sys/_endian.h" 1 3 4
# 124 "/usr/include/sys/_endian.h" 3 4
# 1 "/usr/include/libkern/_OSByteOrder.h" 1 3 4
# 66 "/usr/include/libkern/_OSByteOrder.h" 3 4
# 1 "/usr/include/libkern/i386/_OSByteOrder.h" 1 3 4
# 44 "/usr/include/libkern/i386/_OSByteOrder.h" 3 4
static __inline__
__uint16_t
_OSSwapInt16(
    __uint16_t _data
)
{
    return ((_data << 8) | (_data >> 8));
}

static __inline__
__uint32_t
_OSSwapInt32(
    __uint32_t _data
)
{
    __asm__ ("bswap   %0" : "+r" (_data));
    return _data;
}
# 77 "/usr/include/libkern/i386/_OSByteOrder.h" 3 4
static __inline__
__uint64_t
_OSSwapInt64(
    __uint64_t _data
)
{
    __asm__ ("bswap   %0" : "+r" (_data));
    return _data;
}
# 67 "/usr/include/libkern/_OSByteOrder.h" 2 3 4
# 125 "/usr/include/sys/_endian.h" 2 3 4
# 100 "/usr/include/i386/endian.h" 2 3 4
# 38 "/usr/include/machine/endian.h" 2 3 4
# 194 "/usr/include/sys/wait.h" 2 3 4







union wait {
 int w_status;



 struct {

  unsigned int w_Termsig:7,
    w_Coredump:1,
    w_Retcode:8,
    w_Filler:16;







 } w_T;





 struct {

  unsigned int w_Stopval:8,
    w_Stopsig:8,
    w_Filler:16;






 } w_S;
};
# 254 "/usr/include/sys/wait.h" 3 4

pid_t wait(int *) __asm("_" "wait" );
pid_t waitpid(pid_t, int *, int) __asm("_" "waitpid" );

int waitid(idtype_t, id_t, siginfo_t *, int) __asm("_" "waitid" );


pid_t wait3(int *, int, struct rusage *);
pid_t wait4(pid_t, int *, int, struct rusage *);


# 66 "/usr/include/stdlib.h" 2 3 4

# 1 "/usr/include/alloca.h" 1 3 4
# 35 "/usr/include/alloca.h" 3 4

void *alloca(size_t);

# 68 "/usr/include/stdlib.h" 2 3 4
# 81 "/usr/include/stdlib.h" 3 4
typedef __darwin_ct_rune_t ct_rune_t;




typedef __darwin_rune_t rune_t;
# 97 "/usr/include/stdlib.h" 3 4
typedef struct {
 int quot;
 int rem;
} div_t;

typedef struct {
 long quot;
 long rem;
} ldiv_t;


typedef struct {
 long long quot;
 long long rem;
} lldiv_t;
# 134 "/usr/include/stdlib.h" 3 4
extern int __mb_cur_max;
# 144 "/usr/include/stdlib.h" 3 4

void abort(void) __attribute__((__noreturn__));
int abs(int) __attribute__((__const__));
int atexit(void (*)(void));
double atof(const char *);
int atoi(const char *);
long atol(const char *);

long long
  atoll(const char *);

void *bsearch(const void *, const void *, size_t,
     size_t, int (*)(const void *, const void *));
void *calloc(size_t, size_t);
div_t div(int, int) __attribute__((__const__));
void exit(int) __attribute__((__noreturn__));
void free(void *);
char *getenv(const char *);
long labs(long) __attribute__((__const__));
ldiv_t ldiv(long, long) __attribute__((__const__));

long long
  llabs(long long);
lldiv_t lldiv(long long, long long);

void *malloc(size_t);
int mblen(const char *, size_t);
size_t mbstowcs(wchar_t * , const char * , size_t);
int mbtowc(wchar_t * , const char * , size_t);
void qsort(void *, size_t, size_t,
     int (*)(const void *, const void *));
int rand(void);
void *realloc(void *, size_t);
void srand(unsigned);
double strtod(const char *, char **) __asm("_" "strtod" );
float strtof(const char *, char **) __asm("_" "strtof" );
long strtol(const char *, char **, int);
long double
  strtold(const char *, char **) ;

long long
  strtoll(const char *, char **, int);

unsigned long
  strtoul(const char *, char **, int);

unsigned long long
  strtoull(const char *, char **, int);

int system(const char *) __asm("_" "system" );
size_t wcstombs(char * , const wchar_t * , size_t);
int wctomb(char *, wchar_t);


void _Exit(int) __attribute__((__noreturn__));
long a64l(const char *);
double drand48(void);
char *ecvt(double, int, int *, int *);
double erand48(unsigned short[3]);
char *fcvt(double, int, int *, int *);
char *gcvt(double, int, char *);
int getsubopt(char **, char * const *, char **);
int grantpt(int);

char *initstate(unsigned, char *, size_t);



long jrand48(unsigned short[3]);
char *l64a(long);
void lcong48(unsigned short[7]);
long lrand48(void);
char *mktemp(char *);
int mkstemp(char *);
long mrand48(void);
long nrand48(unsigned short[3]);
int posix_openpt(int);
char *ptsname(int);
int putenv(char *) __asm("_" "putenv" );
long random(void);
int rand_r(unsigned *);

char *realpath(const char * , char * ) __asm("_" "realpath" "$DARWIN_EXTSN");



unsigned short
 *seed48(unsigned short[3]);
int setenv(const char *, const char *, int) __asm("_" "setenv" );

void setkey(const char *) __asm("_" "setkey" );



char *setstate(const char *);
void srand48(long);

void srandom(unsigned);



int unlockpt(int);

int unsetenv(const char *) __asm("_" "unsetenv" );






# 1 "/usr/include/machine/types.h" 1 3 4
# 37 "/usr/include/machine/types.h" 3 4
# 1 "/usr/include/i386/types.h" 1 3 4
# 78 "/usr/include/i386/types.h" 3 4
typedef signed char int8_t;

typedef unsigned char u_int8_t;


typedef short int16_t;

typedef unsigned short u_int16_t;


typedef int int32_t;

typedef unsigned int u_int32_t;


typedef long long int64_t;

typedef unsigned long long u_int64_t;


typedef int64_t register_t;






typedef __darwin_intptr_t intptr_t;



typedef unsigned long int uintptr_t;




typedef u_int64_t user_addr_t;
typedef u_int64_t user_size_t;
typedef int64_t user_ssize_t;
typedef int64_t user_long_t;
typedef u_int64_t user_ulong_t;
typedef int64_t user_time_t;





typedef u_int64_t syscall_arg_t;
# 38 "/usr/include/machine/types.h" 2 3 4
# 255 "/usr/include/stdlib.h" 2 3 4


typedef __darwin_dev_t dev_t;




typedef __darwin_mode_t mode_t;



u_int32_t
  arc4random(void);
void arc4random_addrandom(unsigned char *dat, int datlen);
void arc4random_stir(void);


char *cgetcap(char *, const char *, int);
int cgetclose(void);
int cgetent(char **, char **, const char *);
int cgetfirst(char **, char **);
int cgetmatch(const char *, const char *);
int cgetnext(char **, char **);
int cgetnum(char *, const char *, long *);
int cgetset(const char *);
int cgetstr(char *, const char *, char **);
int cgetustr(char *, const char *, char **);

int daemon(int, int) __asm("_" "daemon" "$1050") __attribute__((deprecated));
char *devname(dev_t, mode_t);
char *devname_r(dev_t, mode_t, char *buf, int len);
char *getbsize(int *, long *);
int getloadavg(double [], int);
const char
 *getprogname(void);

int heapsort(void *, size_t, size_t,
     int (*)(const void *, const void *));
int mergesort(void *, size_t, size_t,
     int (*)(const void *, const void *));
void qsort_r(void *, size_t, size_t, void *,
     int (*)(void *, const void *, const void *));
int radixsort(const unsigned char **, int, const unsigned char *,
     unsigned);
void setprogname(const char *);
int sradixsort(const unsigned char **, int, const unsigned char *,
     unsigned);
void sranddev(void);
void srandomdev(void);
void *reallocf(void *, size_t);

long long
  strtoq(const char *, char **, int);
unsigned long long
  strtouq(const char *, char **, int);

extern char *suboptarg;
void *valloc(size_t);







# 31 "/usr/lib/gcc/i686-apple-darwin9/4.0.1/include/mm_malloc.h" 2 3 4
# 1 "/usr/include/errno.h" 1 3 4
# 23 "/usr/include/errno.h" 3 4
# 1 "/usr/include/sys/errno.h" 1 3 4
# 73 "/usr/include/sys/errno.h" 3 4

extern int * __error(void);


# 24 "/usr/include/errno.h" 2 3 4
# 32 "/usr/lib/gcc/i686-apple-darwin9/4.0.1/include/mm_malloc.h" 2 3 4

static __inline__ void*
_mm_malloc (size_t size, size_t align)
{
  void * malloc_ptr;
  void * aligned_ptr;


  if (align & (align - 1))
    {
      (*__error()) = 22;
      return ((void*) 0);
    }

  if (size == 0)
    return ((void *) 0);





    if (align < 2 * sizeof (void *))
      align = 2 * sizeof (void *);

  malloc_ptr = malloc (size + align);
  if (!malloc_ptr)
    return ((void *) 0);


  aligned_ptr = (void *) (((size_t) malloc_ptr + align)
     & ~((size_t) (align) - 1));


  ((void **) aligned_ptr) [-1] = malloc_ptr;

  return aligned_ptr;
}

static __inline__ void
_mm_free (void * aligned_ptr)
{
  if (aligned_ptr)
    free (((void **) aligned_ptr) [-1]);
}
# 43 "/usr/lib/gcc/i686-apple-darwin9/4.0.1/include/xmmintrin.h" 2 3 4


typedef float __m128 __attribute__ ((__vector_size__ (16)));


typedef float __v4sf __attribute__ ((__vector_size__ (16)));






enum _mm_hint
{
  _MM_HINT_T0 = 3,
  _MM_HINT_T1 = 2,
  _MM_HINT_T2 = 1,
  _MM_HINT_NTA = 0
};
# 96 "/usr/lib/gcc/i686-apple-darwin9/4.0.1/include/xmmintrin.h" 3 4
static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_setzero_ps (void)
{
  return __extension__ (__m128){ 0.0f, 0.0f, 0.0f, 0.0f };
}





static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_add_ss (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_addss ((__v4sf)__A, (__v4sf)__B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_sub_ss (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_subss ((__v4sf)__A, (__v4sf)__B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_mul_ss (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_mulss ((__v4sf)__A, (__v4sf)__B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_div_ss (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_divss ((__v4sf)__A, (__v4sf)__B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_sqrt_ss (__m128 __A)
{
  return (__m128) __builtin_ia32_sqrtss ((__v4sf)__A);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_rcp_ss (__m128 __A)
{
  return (__m128) __builtin_ia32_rcpss ((__v4sf)__A);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_rsqrt_ss (__m128 __A)
{
  return (__m128) __builtin_ia32_rsqrtss ((__v4sf)__A);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_min_ss (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_minss ((__v4sf)__A, (__v4sf)__B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_max_ss (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_maxss ((__v4sf)__A, (__v4sf)__B);
}



static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_add_ps (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_addps ((__v4sf)__A, (__v4sf)__B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_sub_ps (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_subps ((__v4sf)__A, (__v4sf)__B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_mul_ps (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_mulps ((__v4sf)__A, (__v4sf)__B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_div_ps (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_divps ((__v4sf)__A, (__v4sf)__B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_sqrt_ps (__m128 __A)
{
  return (__m128) __builtin_ia32_sqrtps ((__v4sf)__A);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_rcp_ps (__m128 __A)
{
  return (__m128) __builtin_ia32_rcpps ((__v4sf)__A);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_rsqrt_ps (__m128 __A)
{
  return (__m128) __builtin_ia32_rsqrtps ((__v4sf)__A);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_min_ps (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_minps ((__v4sf)__A, (__v4sf)__B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_max_ps (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_maxps ((__v4sf)__A, (__v4sf)__B);
}



static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_and_ps (__m128 __A, __m128 __B)
{
  return __builtin_ia32_andps (__A, __B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_andnot_ps (__m128 __A, __m128 __B)
{
  return __builtin_ia32_andnps (__A, __B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_or_ps (__m128 __A, __m128 __B)
{
  return __builtin_ia32_orps (__A, __B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_xor_ps (__m128 __A, __m128 __B)
{
  return __builtin_ia32_xorps (__A, __B);
}





static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cmpeq_ss (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_cmpeqss ((__v4sf)__A, (__v4sf)__B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cmplt_ss (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_cmpltss ((__v4sf)__A, (__v4sf)__B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cmple_ss (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_cmpless ((__v4sf)__A, (__v4sf)__B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cmpgt_ss (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_movss ((__v4sf) __A,
     (__v4sf)
     __builtin_ia32_cmpltss ((__v4sf) __B,
        (__v4sf)
        __A));
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cmpge_ss (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_movss ((__v4sf) __A,
     (__v4sf)
     __builtin_ia32_cmpless ((__v4sf) __B,
        (__v4sf)
        __A));
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cmpneq_ss (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_cmpneqss ((__v4sf)__A, (__v4sf)__B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cmpnlt_ss (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_cmpnltss ((__v4sf)__A, (__v4sf)__B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cmpnle_ss (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_cmpnless ((__v4sf)__A, (__v4sf)__B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cmpngt_ss (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_movss ((__v4sf) __A,
     (__v4sf)
     __builtin_ia32_cmpnltss ((__v4sf) __B,
         (__v4sf)
         __A));
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cmpnge_ss (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_movss ((__v4sf) __A,
     (__v4sf)
     __builtin_ia32_cmpnless ((__v4sf) __B,
         (__v4sf)
         __A));
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cmpord_ss (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_cmpordss ((__v4sf)__A, (__v4sf)__B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cmpunord_ss (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_cmpunordss ((__v4sf)__A, (__v4sf)__B);
}





static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cmpeq_ps (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_cmpeqps ((__v4sf)__A, (__v4sf)__B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cmplt_ps (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_cmpltps ((__v4sf)__A, (__v4sf)__B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cmple_ps (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_cmpleps ((__v4sf)__A, (__v4sf)__B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cmpgt_ps (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_cmpgtps ((__v4sf)__A, (__v4sf)__B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cmpge_ps (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_cmpgeps ((__v4sf)__A, (__v4sf)__B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cmpneq_ps (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_cmpneqps ((__v4sf)__A, (__v4sf)__B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cmpnlt_ps (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_cmpnltps ((__v4sf)__A, (__v4sf)__B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cmpnle_ps (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_cmpnleps ((__v4sf)__A, (__v4sf)__B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cmpngt_ps (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_cmpngtps ((__v4sf)__A, (__v4sf)__B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cmpnge_ps (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_cmpngeps ((__v4sf)__A, (__v4sf)__B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cmpord_ps (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_cmpordps ((__v4sf)__A, (__v4sf)__B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cmpunord_ps (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_cmpunordps ((__v4sf)__A, (__v4sf)__B);
}




static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_comieq_ss (__m128 __A, __m128 __B)
{
  return __builtin_ia32_comieq ((__v4sf)__A, (__v4sf)__B);
}

static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_comilt_ss (__m128 __A, __m128 __B)
{
  return __builtin_ia32_comilt ((__v4sf)__A, (__v4sf)__B);
}

static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_comile_ss (__m128 __A, __m128 __B)
{
  return __builtin_ia32_comile ((__v4sf)__A, (__v4sf)__B);
}

static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_comigt_ss (__m128 __A, __m128 __B)
{
  return __builtin_ia32_comigt ((__v4sf)__A, (__v4sf)__B);
}

static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_comige_ss (__m128 __A, __m128 __B)
{
  return __builtin_ia32_comige ((__v4sf)__A, (__v4sf)__B);
}

static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_comineq_ss (__m128 __A, __m128 __B)
{
  return __builtin_ia32_comineq ((__v4sf)__A, (__v4sf)__B);
}

static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_ucomieq_ss (__m128 __A, __m128 __B)
{
  return __builtin_ia32_ucomieq ((__v4sf)__A, (__v4sf)__B);
}

static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_ucomilt_ss (__m128 __A, __m128 __B)
{
  return __builtin_ia32_ucomilt ((__v4sf)__A, (__v4sf)__B);
}

static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_ucomile_ss (__m128 __A, __m128 __B)
{
  return __builtin_ia32_ucomile ((__v4sf)__A, (__v4sf)__B);
}

static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_ucomigt_ss (__m128 __A, __m128 __B)
{
  return __builtin_ia32_ucomigt ((__v4sf)__A, (__v4sf)__B);
}

static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_ucomige_ss (__m128 __A, __m128 __B)
{
  return __builtin_ia32_ucomige ((__v4sf)__A, (__v4sf)__B);
}

static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_ucomineq_ss (__m128 __A, __m128 __B)
{
  return __builtin_ia32_ucomineq ((__v4sf)__A, (__v4sf)__B);
}



static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_cvtss_si32 (__m128 __A)
{
  return __builtin_ia32_cvtss2si ((__v4sf) __A);
}

static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_cvt_ss2si (__m128 __A)
{
  return _mm_cvtss_si32 (__A);
}





static __inline long long __attribute__((__always_inline__, __nodebug__))
_mm_cvtss_si64 (__m128 __A)
{
  return __builtin_ia32_cvtss2si64 ((__v4sf) __A);
}


static __inline long long __attribute__((__always_inline__, __nodebug__))
_mm_cvtss_si64x (__m128 __A)
{
  return __builtin_ia32_cvtss2si64 ((__v4sf) __A);
}




static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_cvtps_pi32 (__m128 __A)
{
  return (__m64) __builtin_ia32_cvtps2pi ((__v4sf) __A);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_cvt_ps2pi (__m128 __A)
{
  return _mm_cvtps_pi32 (__A);
}


static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_cvttss_si32 (__m128 __A)
{
  return __builtin_ia32_cvttss2si ((__v4sf) __A);
}

static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_cvtt_ss2si (__m128 __A)
{
  return _mm_cvttss_si32 (__A);
}





static __inline long long __attribute__((__always_inline__, __nodebug__))
_mm_cvttss_si64 (__m128 __A)
{
  return __builtin_ia32_cvttss2si64 ((__v4sf) __A);
}


static __inline long long __attribute__((__always_inline__, __nodebug__))
_mm_cvttss_si64x (__m128 __A)
{
  return __builtin_ia32_cvttss2si64 ((__v4sf) __A);
}




static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_cvttps_pi32 (__m128 __A)
{
  return (__m64) __builtin_ia32_cvttps2pi ((__v4sf) __A);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_cvtt_ps2pi (__m128 __A)
{
  return _mm_cvttps_pi32 (__A);
}


static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cvtsi32_ss (__m128 __A, int __B)
{
  return (__m128) __builtin_ia32_cvtsi2ss ((__v4sf) __A, __B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cvt_si2ss (__m128 __A, int __B)
{
  return _mm_cvtsi32_ss (__A, __B);
}





static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cvtsi64_ss (__m128 __A, long long __B)
{
  return (__m128) __builtin_ia32_cvtsi642ss ((__v4sf) __A, __B);
}


static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cvtsi64x_ss (__m128 __A, long long __B)
{
  return (__m128) __builtin_ia32_cvtsi642ss ((__v4sf) __A, __B);
}




static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cvtpi32_ps (__m128 __A, __m64 __B)
{
  return (__m128) __builtin_ia32_cvtpi2ps ((__v4sf) __A, (__v2si)__B);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cvt_pi2ps (__m128 __A, __m64 __B)
{
  return _mm_cvtpi32_ps (__A, __B);
}


static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cvtpi16_ps (__m64 __A)
{
  __v4hi __sign;
  __v2si __hisi, __losi;
  __v4sf __r;




  __sign = __builtin_ia32_pcmpgtw ((__v4hi)0LL, (__v4hi)__A);


  __hisi = (__v2si) __builtin_ia32_punpckhwd ((__v4hi)__A, __sign);
  __losi = (__v2si) __builtin_ia32_punpcklwd ((__v4hi)__A, __sign);


  __r = (__v4sf) _mm_setzero_ps ();
  __r = __builtin_ia32_cvtpi2ps (__r, __hisi);
  __r = __builtin_ia32_movlhps (__r, __r);
  __r = __builtin_ia32_cvtpi2ps (__r, __losi);

  return (__m128) __r;
}


static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cvtpu16_ps (__m64 __A)
{
  __v2si __hisi, __losi;
  __v4sf __r;


  __hisi = (__v2si) __builtin_ia32_punpckhwd ((__v4hi)__A, (__v4hi)0LL);
  __losi = (__v2si) __builtin_ia32_punpcklwd ((__v4hi)__A, (__v4hi)0LL);


  __r = (__v4sf) _mm_setzero_ps ();
  __r = __builtin_ia32_cvtpi2ps (__r, __hisi);
  __r = __builtin_ia32_movlhps (__r, __r);
  __r = __builtin_ia32_cvtpi2ps (__r, __losi);

  return (__m128) __r;
}


static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cvtpi8_ps (__m64 __A)
{
  __v8qi __sign;




  __sign = __builtin_ia32_pcmpgtb ((__v8qi)0LL, (__v8qi)__A);


  __A = (__m64) __builtin_ia32_punpcklbw ((__v8qi)__A, __sign);

  return _mm_cvtpi16_ps(__A);
}


static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cvtpu8_ps(__m64 __A)
{
  __A = (__m64) __builtin_ia32_punpcklbw ((__v8qi)__A, (__v8qi)0LL);
  return _mm_cvtpu16_ps(__A);
}


static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cvtpi32x2_ps(__m64 __A, __m64 __B)
{
  __v4sf __zero = (__v4sf) _mm_setzero_ps ();
  __v4sf __sfa = __builtin_ia32_cvtpi2ps (__zero, (__v2si)__A);
  __v4sf __sfb = __builtin_ia32_cvtpi2ps (__zero, (__v2si)__B);
  return (__m128) __builtin_ia32_movlhps (__sfa, __sfb);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_cvtps_pi16(__m128 __A)
{
  __v4sf __hisf = (__v4sf)__A;
  __v4sf __losf = __builtin_ia32_movhlps (__hisf, __hisf);
  __v2si __hisi = __builtin_ia32_cvtps2pi (__hisf);
  __v2si __losi = __builtin_ia32_cvtps2pi (__losf);
  return (__m64) __builtin_ia32_packssdw (__hisi, __losi);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_cvtps_pi8(__m128 __A)
{
  __v4hi __tmp = (__v4hi) _mm_cvtps_pi16 (__A);
  return (__m64) __builtin_ia32_packsswb (__tmp, (__v4hi)0LL);
}
# 735 "/usr/lib/gcc/i686-apple-darwin9/4.0.1/include/xmmintrin.h" 3 4
static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_unpackhi_ps (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_unpckhps ((__v4sf)__A, (__v4sf)__B);
}


static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_unpacklo_ps (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_unpcklps ((__v4sf)__A, (__v4sf)__B);
}



static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_loadh_pi (__m128 __A, __m64 const *__P)
{
  return (__m128) __builtin_ia32_loadhps ((__v4sf)__A, (__v2si *)__P);
}


static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_storeh_pi (__m64 *__P, __m128 __A)
{
  __builtin_ia32_storehps ((__v2si *)__P, (__v4sf)__A);
}


static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_movehl_ps (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_movhlps ((__v4sf)__A, (__v4sf)__B);
}


static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_movelh_ps (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_movlhps ((__v4sf)__A, (__v4sf)__B);
}



static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_loadl_pi (__m128 __A, __m64 const *__P)
{
  return (__m128) __builtin_ia32_loadlps ((__v4sf)__A, (__v2si *)__P);
}


static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_storel_pi (__m64 *__P, __m128 __A)
{
  __builtin_ia32_storelps ((__v2si *)__P, (__v4sf)__A);
}


static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_movemask_ps (__m128 __A)
{
  return __builtin_ia32_movmskps ((__v4sf)__A);
}


static __inline unsigned int __attribute__((__always_inline__, __nodebug__))
_mm_getcsr (void)
{
  return __builtin_ia32_stmxcsr ();
}


static __inline unsigned int __attribute__((__always_inline__, __nodebug__))
_MM_GET_EXCEPTION_STATE (void)
{
  return _mm_getcsr() & 0x003f;
}

static __inline unsigned int __attribute__((__always_inline__, __nodebug__))
_MM_GET_EXCEPTION_MASK (void)
{
  return _mm_getcsr() & 0x1f80;
}

static __inline unsigned int __attribute__((__always_inline__, __nodebug__))
_MM_GET_ROUNDING_MODE (void)
{
  return _mm_getcsr() & 0x6000;
}

static __inline unsigned int __attribute__((__always_inline__, __nodebug__))
_MM_GET_FLUSH_ZERO_MODE (void)
{
  return _mm_getcsr() & 0x8000;
}


static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_setcsr (unsigned int __I)
{
  __builtin_ia32_ldmxcsr (__I);
}


static __inline void __attribute__((__always_inline__, __nodebug__))
_MM_SET_EXCEPTION_STATE(unsigned int __mask)
{
  _mm_setcsr((_mm_getcsr() & ~0x003f) | __mask);
}

static __inline void __attribute__((__always_inline__, __nodebug__))
_MM_SET_EXCEPTION_MASK (unsigned int __mask)
{
  _mm_setcsr((_mm_getcsr() & ~0x1f80) | __mask);
}

static __inline void __attribute__((__always_inline__, __nodebug__))
_MM_SET_ROUNDING_MODE (unsigned int __mode)
{
  _mm_setcsr((_mm_getcsr() & ~0x6000) | __mode);
}

static __inline void __attribute__((__always_inline__, __nodebug__))
_MM_SET_FLUSH_ZERO_MODE (unsigned int __mode)
{
  _mm_setcsr((_mm_getcsr() & ~0x8000) | __mode);
}


static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_set_ss (float __F)
{
  return __extension__ (__m128)(__v4sf){ __F, 0, 0, 0 };
}


static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_set1_ps (float __F)
{
  return __extension__ (__m128)(__v4sf){ __F, __F, __F, __F };
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_set_ps1 (float __F)
{
  return _mm_set1_ps (__F);
}


static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_load_ss (float const *__P)
{
  return _mm_set_ss (*__P);
}


static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_load1_ps (float const *__P)
{
  return _mm_set1_ps (*__P);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_load_ps1 (float const *__P)
{
  return _mm_load1_ps (__P);
}


static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_load_ps (float const *__P)
{
  return (__m128) *(__v4sf *)__P;
}


static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_loadu_ps (float const *__P)
{
  return (__m128) __builtin_ia32_loadups (__P);
}


static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_loadr_ps (float const *__P)
{
  __v4sf __tmp = *(__v4sf *)__P;
  return (__m128) __builtin_ia32_shufps (__tmp, __tmp, (((0) << 6) | ((1) << 4) | ((2) << 2) | (3)));
}


static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_set_ps (const float __Z, const float __Y, const float __X, const float __W)
{
  return __extension__ (__m128)(__v4sf){ __W, __X, __Y, __Z };
}


static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_setr_ps (float __Z, float __Y, float __X, float __W)
{
  return __extension__ (__m128)(__v4sf){ __Z, __Y, __X, __W };
}


static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_store_ss (float *__P, __m128 __A)
{
  *__P = __builtin_ia32_vec_ext_v4sf ((__v4sf)__A, 0);
}

static __inline float __attribute__((__always_inline__, __nodebug__))
_mm_cvtss_f32 (__m128 __A)
{
  return __builtin_ia32_vec_ext_v4sf ((__v4sf)__A, 0);
}


static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_store_ps (float *__P, __m128 __A)
{
  *(__v4sf *)__P = (__v4sf)__A;
}


static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_storeu_ps (float *__P, __m128 __A)
{
  __builtin_ia32_storeups (__P, (__v4sf)__A);
}


static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_store1_ps (float *__P, __m128 __A)
{
  __v4sf __va = (__v4sf)__A;
  __v4sf __tmp = __builtin_ia32_shufps (__va, __va, (((0) << 6) | ((0) << 4) | ((0) << 2) | (0)));
  _mm_storeu_ps (__P, __tmp);
}

static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_store_ps1 (float *__P, __m128 __A)
{
  _mm_store1_ps (__P, __A);
}


static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_storer_ps (float *__P, __m128 __A)
{
  __v4sf __va = (__v4sf)__A;
  __v4sf __tmp = __builtin_ia32_shufps (__va, __va, (((0) << 6) | ((1) << 4) | ((2) << 2) | (3)));
  _mm_store_ps (__P, __tmp);
}


static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_move_ss (__m128 __A, __m128 __B)
{
  return (__m128) __builtin_ia32_movss ((__v4sf)__A, (__v4sf)__B);
}
# 1036 "/usr/lib/gcc/i686-apple-darwin9/4.0.1/include/xmmintrin.h" 3 4
static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_max_pi16 (__m64 __A, __m64 __B)
{
  return (__m64) __builtin_ia32_pmaxsw ((__v4hi)__A, (__v4hi)__B);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_pmaxsw (__m64 __A, __m64 __B)
{
  return _mm_max_pi16 (__A, __B);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_max_pu8 (__m64 __A, __m64 __B)
{
  return (__m64) __builtin_ia32_pmaxub ((__v8qi)__A, (__v8qi)__B);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_pmaxub (__m64 __A, __m64 __B)
{
  return _mm_max_pu8 (__A, __B);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_min_pi16 (__m64 __A, __m64 __B)
{
  return (__m64) __builtin_ia32_pminsw ((__v4hi)__A, (__v4hi)__B);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_pminsw (__m64 __A, __m64 __B)
{
  return _mm_min_pi16 (__A, __B);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_min_pu8 (__m64 __A, __m64 __B)
{
  return (__m64) __builtin_ia32_pminub ((__v8qi)__A, (__v8qi)__B);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_pminub (__m64 __A, __m64 __B)
{
  return _mm_min_pu8 (__A, __B);
}


static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_movemask_pi8 (__m64 __A)
{
  return __builtin_ia32_pmovmskb ((__v8qi)__A);
}

static __inline int __attribute__((__always_inline__, __nodebug__))
_m_pmovmskb (__m64 __A)
{
  return _mm_movemask_pi8 (__A);
}



static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_mulhi_pu16 (__m64 __A, __m64 __B)
{
  return (__m64) __builtin_ia32_pmulhuw ((__v4hi)__A, (__v4hi)__B);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_pmulhuw (__m64 __A, __m64 __B)
{
  return _mm_mulhi_pu16 (__A, __B);
}
# 1137 "/usr/lib/gcc/i686-apple-darwin9/4.0.1/include/xmmintrin.h" 3 4
static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_maskmove_si64 (__m64 __A, __m64 __N, char *__P)
{
  __builtin_ia32_maskmovq ((__v8qi)__A, (__v8qi)__N, __P);
}

static __inline void __attribute__((__always_inline__, __nodebug__))
_m_maskmovq (__m64 __A, __m64 __N, char *__P)
{
  _mm_maskmove_si64 (__A, __N, __P);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_avg_pu8 (__m64 __A, __m64 __B)
{
  return (__m64) __builtin_ia32_pavgb ((__v8qi)__A, (__v8qi)__B);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_pavgb (__m64 __A, __m64 __B)
{
  return _mm_avg_pu8 (__A, __B);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_avg_pu16 (__m64 __A, __m64 __B)
{
  return (__m64) __builtin_ia32_pavgw ((__v4hi)__A, (__v4hi)__B);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_pavgw (__m64 __A, __m64 __B)
{
  return _mm_avg_pu16 (__A, __B);
}




static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_sad_pu8 (__m64 __A, __m64 __B)
{
  return (__m64) __builtin_ia32_psadbw ((__v8qi)__A, (__v8qi)__B);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_m_psadbw (__m64 __A, __m64 __B)
{
  return _mm_sad_pu8 (__A, __B);
}
# 1204 "/usr/lib/gcc/i686-apple-darwin9/4.0.1/include/xmmintrin.h" 3 4
static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_stream_pi (__m64 *__P, __m64 __A)
{

  __builtin_ia32_movntq (__P, __A);
}


static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_stream_ps (float *__P, __m128 __A)
{
  __builtin_ia32_movntps (__P, (__v4sf)__A);
}



static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_sfence (void)
{
  __builtin_ia32_sfence ();
}




static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_pause (void)
{
  __asm__ __volatile__ ("rep; nop" : : );
}
# 1257 "/usr/lib/gcc/i686-apple-darwin9/4.0.1/include/xmmintrin.h" 3 4
# 1 "/usr/lib/gcc/i686-apple-darwin9/4.0.1/include/emmintrin.h" 1 3 4
# 35 "/usr/lib/gcc/i686-apple-darwin9/4.0.1/include/emmintrin.h" 3 4
# 1 "/usr/lib/gcc/i686-apple-darwin9/4.0.1/include/xmmintrin.h" 1 3 4
# 36 "/usr/lib/gcc/i686-apple-darwin9/4.0.1/include/emmintrin.h" 2 3 4


typedef double __v2df __attribute__ ((__vector_size__ (16)));
typedef long long __v2di __attribute__ ((__vector_size__ (16)));
typedef int __v4si __attribute__ ((__vector_size__ (16)));
typedef short __v8hi __attribute__ ((__vector_size__ (16)));
typedef char __v16qi __attribute__ ((__vector_size__ (16)));

typedef __v2di __m128i;
typedef __v2df __m128d;
# 57 "/usr/lib/gcc/i686-apple-darwin9/4.0.1/include/emmintrin.h" 3 4
static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_set_sd (double __F)
{
  return __extension__ (__m128d){ __F, 0 };
}


static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_set1_pd (double __F)
{
  return __extension__ (__m128d){ __F, __F };
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_set_pd1 (double __F)
{
  return _mm_set1_pd (__F);
}


static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_set_pd (double __W, double __X)
{
  return __extension__ (__m128d){ __X, __W };
}


static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_setr_pd (double __W, double __X)
{
  return __extension__ (__m128d){ __W, __X };
}


static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_setzero_pd (void)
{
  return __extension__ (__m128d){ 0.0, 0.0 };
}


static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_move_sd (__m128d __A, __m128d __B)
{
  return (__m128d) __builtin_ia32_movsd ((__v2df)__A, (__v2df)__B);
}


static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_load_pd (double const *__P)
{
  return *(__m128d *)__P;
}


static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_loadu_pd (double const *__P)
{
  return __builtin_ia32_loadupd (__P);
}


static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_load1_pd (double const *__P)
{
  return _mm_set1_pd (*__P);
}


static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_load_sd (double const *__P)
{
  return _mm_set_sd (*__P);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_load_pd1 (double const *__P)
{
  return _mm_load1_pd (__P);
}


static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_loadr_pd (double const *__P)
{
  __m128d __tmp = _mm_load_pd (__P);
  return __builtin_ia32_shufpd (__tmp, __tmp, (((0) << 1) | (1)));
}


static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_store_pd (double *__P, __m128d __A)
{
  *(__m128d *)__P = __A;
}


static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_storeu_pd (double *__P, __m128d __A)
{
  __builtin_ia32_storeupd (__P, __A);
}


static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_store_sd (double *__P, __m128d __A)
{
  *__P = __builtin_ia32_vec_ext_v2df (__A, 0);
}

static __inline double __attribute__((__always_inline__, __nodebug__))
_mm_cvtsd_f64 (__m128d __A)
{
  return __builtin_ia32_vec_ext_v2df (__A, 0);
}

static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_storel_pd (double *__P, __m128d __A)
{
  _mm_store_sd (__P, __A);
}


static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_storeh_pd (double *__P, __m128d __A)
{
  *__P = __builtin_ia32_vec_ext_v2df (__A, 1);
}



static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_store1_pd (double *__P, __m128d __A)
{
  _mm_store_pd (__P, __builtin_ia32_shufpd (__A, __A, (((0) << 1) | (0))));
}

static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_store_pd1 (double *__P, __m128d __A)
{
  _mm_store1_pd (__P, __A);
}


static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_storer_pd (double *__P, __m128d __A)
{
  _mm_store_pd (__P, __builtin_ia32_shufpd (__A, __A, (((0) << 1) | (1))));
}

static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_cvtsi128_si32 (__m128i __A)
{
  return __builtin_ia32_vec_ext_v4si ((__v4si)__A, 0);
}



static __inline long long __attribute__((__always_inline__, __nodebug__))
_mm_cvtsi128_si64 (__m128i __A)
{
  return __builtin_ia32_vec_ext_v2di ((__v2di)__A, 0);
}


static __inline long long __attribute__((__always_inline__, __nodebug__))
_mm_cvtsi128_si64x (__m128i __A)
{
  return __builtin_ia32_vec_ext_v2di ((__v2di)__A, 0);
}


static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_add_pd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_addpd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_add_sd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_addsd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_sub_pd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_subpd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_sub_sd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_subsd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_mul_pd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_mulpd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_mul_sd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_mulsd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_div_pd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_divpd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_div_sd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_divsd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_sqrt_pd (__m128d __A)
{
  return (__m128d)__builtin_ia32_sqrtpd ((__v2df)__A);
}


static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_sqrt_sd (__m128d __A, __m128d __B)
{
  __v2df __tmp = __builtin_ia32_movsd ((__v2df)__A, (__v2df)__B);
  return (__m128d)__builtin_ia32_sqrtsd ((__v2df)__tmp);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_min_pd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_minpd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_min_sd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_minsd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_max_pd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_maxpd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_max_sd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_maxsd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_and_pd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_andpd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_andnot_pd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_andnpd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_or_pd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_orpd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_xor_pd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_xorpd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_cmpeq_pd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_cmpeqpd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_cmplt_pd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_cmpltpd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_cmple_pd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_cmplepd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_cmpgt_pd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_cmpgtpd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_cmpge_pd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_cmpgepd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_cmpneq_pd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_cmpneqpd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_cmpnlt_pd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_cmpnltpd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_cmpnle_pd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_cmpnlepd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_cmpngt_pd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_cmpngtpd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_cmpnge_pd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_cmpngepd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_cmpord_pd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_cmpordpd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_cmpunord_pd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_cmpunordpd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_cmpeq_sd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_cmpeqsd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_cmplt_sd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_cmpltsd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_cmple_sd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_cmplesd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_cmpgt_sd (__m128d __A, __m128d __B)
{
  return (__m128d) __builtin_ia32_movsd ((__v2df) __A,
      (__v2df)
      __builtin_ia32_cmpltsd ((__v2df) __B,
         (__v2df)
         __A));
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_cmpge_sd (__m128d __A, __m128d __B)
{
  return (__m128d) __builtin_ia32_movsd ((__v2df) __A,
      (__v2df)
      __builtin_ia32_cmplesd ((__v2df) __B,
         (__v2df)
         __A));
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_cmpneq_sd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_cmpneqsd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_cmpnlt_sd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_cmpnltsd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_cmpnle_sd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_cmpnlesd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_cmpngt_sd (__m128d __A, __m128d __B)
{
  return (__m128d) __builtin_ia32_movsd ((__v2df) __A,
      (__v2df)
      __builtin_ia32_cmpnltsd ((__v2df) __B,
          (__v2df)
          __A));
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_cmpnge_sd (__m128d __A, __m128d __B)
{
  return (__m128d) __builtin_ia32_movsd ((__v2df) __A,
      (__v2df)
      __builtin_ia32_cmpnlesd ((__v2df) __B,
          (__v2df)
          __A));
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_cmpord_sd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_cmpordsd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_cmpunord_sd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_cmpunordsd ((__v2df)__A, (__v2df)__B);
}

static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_comieq_sd (__m128d __A, __m128d __B)
{
  return __builtin_ia32_comisdeq ((__v2df)__A, (__v2df)__B);
}

static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_comilt_sd (__m128d __A, __m128d __B)
{
  return __builtin_ia32_comisdlt ((__v2df)__A, (__v2df)__B);
}

static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_comile_sd (__m128d __A, __m128d __B)
{
  return __builtin_ia32_comisdle ((__v2df)__A, (__v2df)__B);
}

static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_comigt_sd (__m128d __A, __m128d __B)
{
  return __builtin_ia32_comisdgt ((__v2df)__A, (__v2df)__B);
}

static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_comige_sd (__m128d __A, __m128d __B)
{
  return __builtin_ia32_comisdge ((__v2df)__A, (__v2df)__B);
}

static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_comineq_sd (__m128d __A, __m128d __B)
{
  return __builtin_ia32_comisdneq ((__v2df)__A, (__v2df)__B);
}

static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_ucomieq_sd (__m128d __A, __m128d __B)
{
  return __builtin_ia32_ucomisdeq ((__v2df)__A, (__v2df)__B);
}

static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_ucomilt_sd (__m128d __A, __m128d __B)
{
  return __builtin_ia32_ucomisdlt ((__v2df)__A, (__v2df)__B);
}

static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_ucomile_sd (__m128d __A, __m128d __B)
{
  return __builtin_ia32_ucomisdle ((__v2df)__A, (__v2df)__B);
}

static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_ucomigt_sd (__m128d __A, __m128d __B)
{
  return __builtin_ia32_ucomisdgt ((__v2df)__A, (__v2df)__B);
}

static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_ucomige_sd (__m128d __A, __m128d __B)
{
  return __builtin_ia32_ucomisdge ((__v2df)__A, (__v2df)__B);
}

static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_ucomineq_sd (__m128d __A, __m128d __B)
{
  return __builtin_ia32_ucomisdneq ((__v2df)__A, (__v2df)__B);
}



static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_set_epi64x (long long __q1, long long __q0)
{
  return __extension__ (__m128i)(__v2di){ __q0, __q1 };
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_set_epi64 (__m64 __q1, __m64 __q0)
{
  return _mm_set_epi64x ((long long)__q1, (long long)__q0);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_set_epi32 (int __q3, int __q2, int __q1, int __q0)
{
  return __extension__ (__m128i)(__v4si){ __q0, __q1, __q2, __q3 };
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_set_epi16 (short __q7, short __q6, short __q5, short __q4,
        short __q3, short __q2, short __q1, short __q0)
{
  return __extension__ (__m128i)(__v8hi){
    __q0, __q1, __q2, __q3, __q4, __q5, __q6, __q7 };
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_set_epi8 (char __q15, char __q14, char __q13, char __q12,
       char __q11, char __q10, char __q09, char __q08,
       char __q07, char __q06, char __q05, char __q04,
       char __q03, char __q02, char __q01, char __q00)
{
  return __extension__ (__m128i)(__v16qi){
    __q00, __q01, __q02, __q03, __q04, __q05, __q06, __q07,
    __q08, __q09, __q10, __q11, __q12, __q13, __q14, __q15
  };
}
# 618 "/usr/lib/gcc/i686-apple-darwin9/4.0.1/include/emmintrin.h" 3 4
static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_setr_epi64 (__m64 __q0, __m64 __q1)
{
  return _mm_set_epi64 (__q1, __q0);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_setr_epi32 (int __q0, int __q1, int __q2, int __q3)
{
  return _mm_set_epi32 (__q3, __q2, __q1, __q0);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_setr_epi16 (short __q0, short __q1, short __q2, short __q3,
         short __q4, short __q5, short __q6, short __q7)
{
  return _mm_set_epi16 (__q7, __q6, __q5, __q4, __q3, __q2, __q1, __q0);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_setr_epi8 (char __q00, char __q01, char __q02, char __q03,
        char __q04, char __q05, char __q06, char __q07,
        char __q08, char __q09, char __q10, char __q11,
        char __q12, char __q13, char __q14, char __q15)
{
  return _mm_set_epi8 (__q15, __q14, __q13, __q12, __q11, __q10, __q09, __q08,
         __q07, __q06, __q05, __q04, __q03, __q02, __q01, __q00);
}



static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_load_si128 (__m128i const *__P)
{
  return *__P;
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_loadu_si128 (__m128i const *__P)
{
  return (__m128i) __builtin_ia32_loaddqu ((char const *)__P);
}


static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_loadl_epi64 (__m128i const *__P)
{
  return (__m128i)__builtin_ia32_loadlv4si ((__v2si *)__P);
}


static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_store_si128 (__m128i *__P, __m128i __B)
{
  *__P = __B;
}

static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_storeu_si128 (__m128i *__P, __m128i __B)
{
  __builtin_ia32_storedqu ((char *)__P, (__v16qi)__B);
}


static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_storel_epi64 (__m128i *__P, __m128i __B)
{
  __builtin_ia32_storelv4si ((__v2si *)__P, __B);
}


static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_movepi64_pi64 (__m128i __B)
{
  return (__m64) __builtin_ia32_vec_ext_v2di ((__v2di)__B, 0);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_movpi64_epi64 (__m64 __A)
{
  return _mm_set_epi64 ((__m64)0LL, __A);
}


static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_move_epi64 (__m128i __A)
{
  return (__m128i)__builtin_ia32_movqv4si ((__v4si)__A) ;
}



static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_setzero_si128 (void)
{
  return __extension__ (__m128i)(__v4si){ 0, 0, 0, 0 };
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_cvtepi32_pd (__m128i __A)
{
  return (__m128d)__builtin_ia32_cvtdq2pd ((__v4si) __A);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cvtepi32_ps (__m128i __A)
{
  return (__m128)__builtin_ia32_cvtdq2ps ((__v4si) __A);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_cvtpd_epi32 (__m128d __A)
{
  return (__m128i)__builtin_ia32_cvtpd2dq ((__v2df) __A);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_cvtpd_pi32 (__m128d __A)
{
  return (__m64)__builtin_ia32_cvtpd2pi ((__v2df) __A);
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cvtpd_ps (__m128d __A)
{
  return (__m128)__builtin_ia32_cvtpd2ps ((__v2df) __A);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_cvttpd_epi32 (__m128d __A)
{
  return (__m128i)__builtin_ia32_cvttpd2dq ((__v2df) __A);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_cvttpd_pi32 (__m128d __A)
{
  return (__m64)__builtin_ia32_cvttpd2pi ((__v2df) __A);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_cvtpi32_pd (__m64 __A)
{
  return (__m128d)__builtin_ia32_cvtpi2pd ((__v2si) __A);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_cvtps_epi32 (__m128 __A)
{
  return (__m128i)__builtin_ia32_cvtps2dq ((__v4sf) __A);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_cvttps_epi32 (__m128 __A)
{
  return (__m128i)__builtin_ia32_cvttps2dq ((__v4sf) __A);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_cvtps_pd (__m128 __A)
{
  return (__m128d)__builtin_ia32_cvtps2pd ((__v4sf) __A);
}

static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_cvtsd_si32 (__m128d __A)
{
  return __builtin_ia32_cvtsd2si ((__v2df) __A);
}



static __inline long long __attribute__((__always_inline__, __nodebug__))
_mm_cvtsd_si64 (__m128d __A)
{
  return __builtin_ia32_cvtsd2si64 ((__v2df) __A);
}


static __inline long long __attribute__((__always_inline__, __nodebug__))
_mm_cvtsd_si64x (__m128d __A)
{
  return __builtin_ia32_cvtsd2si64 ((__v2df) __A);
}


static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_cvttsd_si32 (__m128d __A)
{
  return __builtin_ia32_cvttsd2si ((__v2df) __A);
}



static __inline long long __attribute__((__always_inline__, __nodebug__))
_mm_cvttsd_si64 (__m128d __A)
{
  return __builtin_ia32_cvttsd2si64 ((__v2df) __A);
}


static __inline long long __attribute__((__always_inline__, __nodebug__))
_mm_cvttsd_si64x (__m128d __A)
{
  return __builtin_ia32_cvttsd2si64 ((__v2df) __A);
}


static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_cvtsd_ss (__m128 __A, __m128d __B)
{
  return (__m128)__builtin_ia32_cvtsd2ss ((__v4sf) __A, (__v2df) __B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_cvtsi32_sd (__m128d __A, int __B)
{
  return (__m128d)__builtin_ia32_cvtsi2sd ((__v2df) __A, __B);
}



static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_cvtsi64_sd (__m128d __A, long long __B)
{
  return (__m128d)__builtin_ia32_cvtsi642sd ((__v2df) __A, __B);
}


static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_cvtsi64x_sd (__m128d __A, long long __B)
{
  return (__m128d)__builtin_ia32_cvtsi642sd ((__v2df) __A, __B);
}


static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_cvtss_sd (__m128d __A, __m128 __B)
{
  return (__m128d)__builtin_ia32_cvtss2sd ((__v2df) __A, (__v4sf)__B);
}




static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_unpackhi_pd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_unpckhpd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_unpacklo_pd (__m128d __A, __m128d __B)
{
  return (__m128d)__builtin_ia32_unpcklpd ((__v2df)__A, (__v2df)__B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_loadh_pd (__m128d __A, double const *__B)
{
  return (__m128d)__builtin_ia32_loadhpd ((__v2df)__A, __B);
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_loadl_pd (__m128d __A, double const *__B)
{
  return (__m128d)__builtin_ia32_loadlpd ((__v2df)__A, __B);
}

static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_movemask_pd (__m128d __A)
{
  return __builtin_ia32_movmskpd ((__v2df)__A);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_packs_epi16 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_packsswb128 ((__v8hi)__A, (__v8hi)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_packs_epi32 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_packssdw128 ((__v4si)__A, (__v4si)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_packus_epi16 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_packuswb128 ((__v8hi)__A, (__v8hi)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_unpackhi_epi8 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_punpckhbw128 ((__v16qi)__A, (__v16qi)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_unpackhi_epi16 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_punpckhwd128 ((__v8hi)__A, (__v8hi)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_unpackhi_epi32 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_punpckhdq128 ((__v4si)__A, (__v4si)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_unpackhi_epi64 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_punpckhqdq128 ((__v2di)__A, (__v2di)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_unpacklo_epi8 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_punpcklbw128 ((__v16qi)__A, (__v16qi)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_unpacklo_epi16 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_punpcklwd128 ((__v8hi)__A, (__v8hi)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_unpacklo_epi32 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_punpckldq128 ((__v4si)__A, (__v4si)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_unpacklo_epi64 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_punpcklqdq128 ((__v2di)__A, (__v2di)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_add_epi8 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_paddb128 ((__v16qi)__A, (__v16qi)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_add_epi16 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_paddw128 ((__v8hi)__A, (__v8hi)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_add_epi32 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_paddd128 ((__v4si)__A, (__v4si)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_add_epi64 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_paddq128 ((__v2di)__A, (__v2di)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_adds_epi8 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_paddsb128 ((__v16qi)__A, (__v16qi)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_adds_epi16 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_paddsw128 ((__v8hi)__A, (__v8hi)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_adds_epu8 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_paddusb128 ((__v16qi)__A, (__v16qi)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_adds_epu16 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_paddusw128 ((__v8hi)__A, (__v8hi)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_sub_epi8 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_psubb128 ((__v16qi)__A, (__v16qi)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_sub_epi16 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_psubw128 ((__v8hi)__A, (__v8hi)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_sub_epi32 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_psubd128 ((__v4si)__A, (__v4si)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_sub_epi64 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_psubq128 ((__v2di)__A, (__v2di)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_subs_epi8 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_psubsb128 ((__v16qi)__A, (__v16qi)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_subs_epi16 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_psubsw128 ((__v8hi)__A, (__v8hi)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_subs_epu8 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_psubusb128 ((__v16qi)__A, (__v16qi)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_subs_epu16 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_psubusw128 ((__v8hi)__A, (__v8hi)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_madd_epi16 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_pmaddwd128 ((__v8hi)__A, (__v8hi)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_mulhi_epi16 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_pmulhw128 ((__v8hi)__A, (__v8hi)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_mullo_epi16 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_pmullw128 ((__v8hi)__A, (__v8hi)__B);
}

static __inline __m64 __attribute__((__always_inline__, __nodebug__))
_mm_mul_su32 (__m64 __A, __m64 __B)
{
  return (__m64)__builtin_ia32_pmuludq ((__v2si)__A, (__v2si)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_mul_epu32 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_pmuludq128 ((__v4si)__A, (__v4si)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_slli_epi16 (__m128i __A, int __B)
{
  return (__m128i)__builtin_ia32_psllwi128 ((__v8hi)__A, __B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_slli_epi32 (__m128i __A, int __B)
{
  return (__m128i)__builtin_ia32_pslldi128 ((__v4si)__A, __B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_slli_epi64 (__m128i __A, int __B)
{
  return (__m128i)__builtin_ia32_psllqi128 ((__v2di)__A, __B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_srai_epi16 (__m128i __A, int __B)
{
  return (__m128i)__builtin_ia32_psrawi128 ((__v8hi)__A, __B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_srai_epi32 (__m128i __A, int __B)
{
  return (__m128i)__builtin_ia32_psradi128 ((__v4si)__A, __B);
}
# 1134 "/usr/lib/gcc/i686-apple-darwin9/4.0.1/include/emmintrin.h" 3 4
static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_srli_epi16 (__m128i __A, int __B)
{
  return (__m128i)__builtin_ia32_psrlwi128 ((__v8hi)__A, __B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_srli_epi32 (__m128i __A, int __B)
{
  return (__m128i)__builtin_ia32_psrldi128 ((__v4si)__A, __B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_srli_epi64 (__m128i __A, int __B)
{
  return (__m128i)__builtin_ia32_psrlqi128 ((__v2di)__A, __B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_sll_epi16 (__m128i __A, __m128i __B)
{
  return _mm_slli_epi16 (__A, _mm_cvtsi128_si32 (__B));
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_sll_epi32 (__m128i __A, __m128i __B)
{
  return _mm_slli_epi32 (__A, _mm_cvtsi128_si32 (__B));
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_sll_epi64 (__m128i __A, __m128i __B)
{
  return _mm_slli_epi64 (__A, _mm_cvtsi128_si32 (__B));
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_sra_epi16 (__m128i __A, __m128i __B)
{
  return _mm_srai_epi16 (__A, _mm_cvtsi128_si32 (__B));
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_sra_epi32 (__m128i __A, __m128i __B)
{
  return _mm_srai_epi32 (__A, _mm_cvtsi128_si32 (__B));
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_srl_epi16 (__m128i __A, __m128i __B)
{
  return _mm_srli_epi16 (__A, _mm_cvtsi128_si32 (__B));
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_srl_epi32 (__m128i __A, __m128i __B)
{
  return _mm_srli_epi32 (__A, _mm_cvtsi128_si32 (__B));
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_srl_epi64 (__m128i __A, __m128i __B)
{
  return _mm_srli_epi64 (__A, _mm_cvtsi128_si32 (__B));
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_and_si128 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_pand128 ((__v2di)__A, (__v2di)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_andnot_si128 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_pandn128 ((__v2di)__A, (__v2di)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_or_si128 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_por128 ((__v2di)__A, (__v2di)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_xor_si128 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_pxor128 ((__v2di)__A, (__v2di)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_cmpeq_epi8 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_pcmpeqb128 ((__v16qi)__A, (__v16qi)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_cmpeq_epi16 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_pcmpeqw128 ((__v8hi)__A, (__v8hi)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_cmpeq_epi32 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_pcmpeqd128 ((__v4si)__A, (__v4si)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_cmplt_epi8 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_pcmpgtb128 ((__v16qi)__B, (__v16qi)__A);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_cmplt_epi16 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_pcmpgtw128 ((__v8hi)__B, (__v8hi)__A);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_cmplt_epi32 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_pcmpgtd128 ((__v4si)__B, (__v4si)__A);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_cmpgt_epi8 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_pcmpgtb128 ((__v16qi)__A, (__v16qi)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_cmpgt_epi16 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_pcmpgtw128 ((__v8hi)__A, (__v8hi)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_cmpgt_epi32 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_pcmpgtd128 ((__v4si)__A, (__v4si)__B);
}
# 1297 "/usr/lib/gcc/i686-apple-darwin9/4.0.1/include/emmintrin.h" 3 4
static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_max_epi16 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_pmaxsw128 ((__v8hi)__A, (__v8hi)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_max_epu8 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_pmaxub128 ((__v16qi)__A, (__v16qi)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_min_epi16 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_pminsw128 ((__v8hi)__A, (__v8hi)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_min_epu8 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_pminub128 ((__v16qi)__A, (__v16qi)__B);
}

static __inline int __attribute__((__always_inline__, __nodebug__))
_mm_movemask_epi8 (__m128i __A)
{
  return __builtin_ia32_pmovmskb128 ((__v16qi)__A);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_mulhi_epu16 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_pmulhuw128 ((__v8hi)__A, (__v8hi)__B);
}







static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_maskmoveu_si128 (__m128i __A, __m128i __B, char *__C)
{
  __builtin_ia32_maskmovdqu ((__v16qi)__A, (__v16qi)__B, __C);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_avg_epu8 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_pavgb128 ((__v16qi)__A, (__v16qi)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_avg_epu16 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_pavgw128 ((__v8hi)__A, (__v8hi)__B);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_sad_epu8 (__m128i __A, __m128i __B)
{
  return (__m128i)__builtin_ia32_psadbw128 ((__v16qi)__A, (__v16qi)__B);
}

static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_stream_si32 (int *__A, int __B)
{
  __builtin_ia32_movnti (__A, __B);
}

static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_stream_si128 (__m128i *__A, __m128i __B)
{
  __builtin_ia32_movntdq ((__v2di *)__A, (__v2di)__B);
}

static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_stream_pd (double *__A, __m128d __B)
{
  __builtin_ia32_movntpd (__A, (__v2df)__B);
}

static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_clflush (void const *__A)
{
  __builtin_ia32_clflush (__A);
}

static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_lfence (void)
{
  __builtin_ia32_lfence ();
}

static __inline void __attribute__((__always_inline__, __nodebug__))
_mm_mfence (void)
{
  __builtin_ia32_mfence ();
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_cvtsi32_si128 (int __A)
{
  return _mm_set_epi32 (0, 0, 0, __A);
}



static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_cvtsi64_si128 (long long __A)
{
  return _mm_set_epi64x (0, __A);
}


static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_cvtsi64x_si128 (long long __A)
{
  return _mm_set_epi64x (0, __A);
}




static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_castpd_ps(__m128d __A)
{
  return (__m128) __A;
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_castpd_si128(__m128d __A)
{
  return (__m128i) __A;
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_castps_pd(__m128 __A)
{
  return (__m128d) __A;
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_castps_si128(__m128 __A)
{
  return (__m128i) __A;
}

static __inline __m128 __attribute__((__always_inline__, __nodebug__))
_mm_castsi128_ps(__m128i __A)
{
  return (__m128) __A;
}

static __inline __m128d __attribute__((__always_inline__, __nodebug__))
_mm_castsi128_pd(__m128i __A)
{
  return (__m128d) __A;
}





static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_set1_epi64x (long long __A)
{
  return _mm_set_epi64x (__A, __A);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_set1_epi64 (__m64 __A)
{
  return _mm_set_epi64 (__A, __A);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_set1_epi32 (int __A)
{
  return _mm_set_epi32 (__A, __A, __A, __A);
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_set1_epi16 (short __A)
{
  __m128i temp, temp2, temp3;
  temp = _mm_cvtsi32_si128((int)__A);
  temp2 = _mm_unpacklo_epi16(temp, temp);
  temp3 = ((__m128i)__builtin_ia32_pshufd ((__v4si)(temp2), 0));
  return temp3;
}

static __inline __m128i __attribute__((__always_inline__, __nodebug__))
_mm_set1_epi8 (char __A)
{
    __m128i temp, temp2, temp3, temp4;
    temp = _mm_cvtsi32_si128 ((int)__A);
    temp2 = _mm_unpacklo_epi8 (temp, temp);
    temp3 = _mm_unpacklo_epi8 (temp2, temp2);
    temp4 = ((__m128i)__builtin_ia32_pshufd ((__v4si)(temp3), 0));
    return temp4;
}
# 1258 "/usr/lib/gcc/i686-apple-darwin9/4.0.1/include/xmmintrin.h" 2 3 4
# 10 "../src/atomic_ops/sysdeps/gcc/../standard_ao_double_t.h" 2
   typedef __m128 double_ptr_storage;
# 29 "../src/atomic_ops/sysdeps/gcc/../standard_ao_double_t.h"
typedef union {
    double_ptr_storage AO_whole;
    struct {size_t AO_v1; size_t AO_v2;} AO_parts;
} AO_double_t;
# 38 "../src/atomic_ops/sysdeps/gcc/x86_64.h" 2
# 60 "../src/atomic_ops/sysdeps/gcc/x86_64.h"
static __inline size_t
AO_fetch_and_add_full (volatile size_t *p, size_t incr)
{
  size_t result;

  __asm__ __volatile__ ("lock; xaddq %0, %1" :
   "=r" (result), "=m" (*p) : "0" (incr), "m" (*p)
   : "memory");
  return result;
}



static __inline unsigned char
AO_char_fetch_and_add_full (volatile unsigned char *p, unsigned char incr)
{
  unsigned char result;

  __asm__ __volatile__ ("lock; xaddb %0, %1" :
   "=q" (result), "=m" (*p) : "0" (incr), "m" (*p)
   : "memory");
  return result;
}



static __inline unsigned short
AO_short_fetch_and_add_full (volatile unsigned short *p, unsigned short incr)
{
  unsigned short result;

  __asm__ __volatile__ ("lock; xaddw %0, %1" :
   "=r" (result), "=m" (*p) : "0" (incr), "m" (*p)
   : "memory");
  return result;
}



static __inline unsigned int
AO_int_fetch_and_add_full (volatile unsigned int *p, unsigned int incr)
{
  unsigned int result;

  __asm__ __volatile__ ("lock; xaddl %0, %1" :
   "=r" (result), "=m" (*p) : "0" (incr), "m" (*p)
   : "memory");
  return result;
}




static __inline void
AO_or_full (volatile size_t *p, size_t incr)
{
  __asm__ __volatile__ ("lock; orq %1, %0" :
   "=m" (*p) : "r" (incr), "m" (*p) : "memory");
}



static __inline AO_BYTE_TS_val
AO_test_and_set_full(volatile unsigned char *addr)
{
  unsigned char oldval;

  __asm__ __volatile__("xchgb %0, %1"
  : "=q"(oldval), "=m"(*addr)
  : "0"(0xff), "m"(*addr) : "memory");
  return (AO_BYTE_TS_val)oldval;
}




static __inline int
AO_compare_and_swap_full(volatile size_t *addr,
      size_t old, size_t new_val)
{
  char result;
  __asm__ __volatile__("lock; cmpxchgq %3, %0; setz %1"
             : "=m"(*addr), "=q"(result)
         : "m"(*addr), "r" (new_val), "a"(old) : "memory");
  return (int) result;
}
# 198 "../src/atomic_ops.h" 2
# 293 "../src/atomic_ops.h"
# 1 "../src/atomic_ops/generalize.h" 1
# 146 "../src/atomic_ops/generalize.h"
   static __inline void AO_nop(void) {}




   static __inline void
   AO_nop_full(void)
   {
     unsigned char dummy = (size_t)AO_BYTE_TS_clear;
     AO_test_and_set_full(&dummy);
   }
# 1082 "../src/atomic_ops/generalize.h"
# 1 "../src/atomic_ops/generalize-small.h" 1
# 1083 "../src/atomic_ops/generalize.h" 2
# 294 "../src/atomic_ops.h" 2
# 2 "list_atomic.c" 2
# 15 "list_atomic.c"
void list_atomic(void)
{
  size_t *addr, val, newval, oldval;
  unsigned char tsaddr;
  long incr;


    "AO_nop(): ";
    AO_nop();




    "AO_load(addr):";
    AO_load(addr);




    "AO_store(addr, val):";
    AO_store(addr, val);




    "AO_test_and_set(tsaddr):";
    AO_test_and_set_full(tsaddr);




    "AO_fetch_and_add1(addr):";
    AO_fetch_and_add_full(addr, 1);




    "AO_fetch_and_sub1(addr):";
    AO_fetch_and_add_full(addr, (size_t)(-1));




    "AO_fetch_and_add(addr, incr):";
    AO_fetch_and_add_full(addr, incr);




    "AO_compare_and_swap(addr, oldval, newval):";
    AO_compare_and_swap_full(addr, oldval, newval);



}
# 86 "list_atomic.c"
void list_atomic_release(void)
{
  size_t *addr, val, newval, oldval;
  unsigned char tsaddr;
  long incr;





    "No AO_nop_release";





    "No AO_load_release";


    "AO_store_release(addr, val):";
    AO_store_write(addr, val);




    "AO_test_and_set_release(tsaddr):";
    AO_test_and_set_full(tsaddr);




    "AO_fetch_and_add1_release(addr):";
    AO_fetch_and_add_full(addr, 1);




    "AO_fetch_and_sub1_release(addr):";
    AO_fetch_and_add_full(addr, (size_t)(-1));




    "AO_fetch_and_add_release(addr, incr):";
    AO_fetch_and_add_full(addr, incr);




    "AO_compare_and_swap_release(addr, oldval, newval):";
    AO_compare_and_swap_full(addr, oldval, newval);



}
# 157 "list_atomic.c"
void list_atomic_acquire(void)
{
  size_t *addr, val, newval, oldval;
  unsigned char tsaddr;
  long incr;





    "No AO_nop_acquire";


    "AO_load_acquire(addr):";
    AO_load_read(addr);







    "No AO_store_acquire";


    "AO_test_and_set_acquire(tsaddr):";
    AO_test_and_set_full(tsaddr);




    "AO_fetch_and_add1_acquire(addr):";
    AO_fetch_and_add_full(addr, 1);




    "AO_fetch_and_sub1_acquire(addr):";
    AO_fetch_and_add_full(addr, (size_t)(-1));




    "AO_fetch_and_add_acquire(addr, incr):";
    AO_fetch_and_add_full(addr, incr);




    "AO_compare_and_swap_acquire(addr, oldval, newval):";
    AO_compare_and_swap_full(addr, oldval, newval);



}
# 228 "list_atomic.c"
void list_atomic_read(void)
{
  size_t *addr, val, newval, oldval;
  unsigned char tsaddr;
  long incr;


    "AO_nop_read(): ";
    AO_nop_full();




    "AO_load_read(addr):";
    AO_load_read(addr);







    "No AO_store_read";


    "AO_test_and_set_read(tsaddr):";
    AO_test_and_set_full(tsaddr);




    "AO_fetch_and_add1_read(addr):";
    AO_fetch_and_add_full(addr, 1);




    "AO_fetch_and_sub1_read(addr):";
    AO_fetch_and_add_full(addr, (size_t)(-1));




    "AO_fetch_and_add_read(addr, incr):";
    AO_fetch_and_add_full(addr, incr);




    "AO_compare_and_swap_read(addr, oldval, newval):";
    AO_compare_and_swap_full(addr, oldval, newval);



}
# 299 "list_atomic.c"
void list_atomic_write(void)
{
  size_t *addr, val, newval, oldval;
  unsigned char tsaddr;
  long incr;


    "AO_nop_write(): ";
    AO_nop_full();







    "No AO_load_write";


    "AO_store_write(addr, val):";
    AO_store_write(addr, val);




    "AO_test_and_set_write(tsaddr):";
    AO_test_and_set_full(tsaddr);




    "AO_fetch_and_add1_write(addr):";
    AO_fetch_and_add_full(addr, 1);




    "AO_fetch_and_sub1_write(addr):";
    AO_fetch_and_add_full(addr, (size_t)(-1));




    "AO_fetch_and_add_write(addr, incr):";
    AO_fetch_and_add_full(addr, incr);




    "AO_compare_and_swap_write(addr, oldval, newval):";
    AO_compare_and_swap_full(addr, oldval, newval);



}
# 370 "list_atomic.c"
void list_atomic_full(void)
{
  size_t *addr, val, newval, oldval;
  unsigned char tsaddr;
  long incr;


    "AO_nop_full(): ";
    AO_nop_full();




    "AO_load_full(addr):";
    (AO_nop_full(), AO_load_read(addr));




    "AO_store_full(addr, val):";
    (AO_store_write(addr, val), AO_nop_full());




    "AO_test_and_set_full(tsaddr):";
    AO_test_and_set_full(tsaddr);




    "AO_fetch_and_add1_full(addr):";
    AO_fetch_and_add_full(addr,1);




    "AO_fetch_and_sub1_full(addr):";
    AO_fetch_and_add_full(addr,(size_t)(-1));




    "AO_fetch_and_add_full(addr, incr):";
    AO_fetch_and_add_full(addr, incr);




    "AO_compare_and_swap_full(addr, oldval, newval):";
    AO_compare_and_swap_full(addr, oldval, newval);



}
# 441 "list_atomic.c"
void list_atomic_release_write(void)
{
  size_t *addr, val, newval, oldval;
  unsigned char tsaddr;
  long incr;





    "No AO_nop_release_write";





    "No AO_load_release_write";


    "AO_store_release_write(addr, val):";
    AO_store_write(addr, val);




    "AO_test_and_set_release_write(tsaddr):";
    AO_test_and_set_full(tsaddr);




    "AO_fetch_and_add1_release_write(addr):";
    AO_fetch_and_add_full(addr, 1);




    "AO_fetch_and_sub1_release_write(addr):";
    AO_fetch_and_add_full(addr, (size_t)(-1));




    "AO_fetch_and_add_release_write(addr, incr):";
    AO_fetch_and_add_full(addr, incr);




    "AO_compare_and_swap_release_write(addr, oldval, newval):";
    AO_compare_and_swap_full(addr, oldval, newval);



}
# 512 "list_atomic.c"
void list_atomic_acquire_read(void)
{
  size_t *addr, val, newval, oldval;
  unsigned char tsaddr;
  long incr;





    "No AO_nop_acquire_read";


    "AO_load_acquire_read(addr):";
    AO_load_read(addr);







    "No AO_store_acquire_read";


    "AO_test_and_set_acquire_read(tsaddr):";
    AO_test_and_set_full(tsaddr);




    "AO_fetch_and_add1_acquire_read(addr):";
    AO_fetch_and_add_full(addr, 1);




    "AO_fetch_and_sub1_acquire_read(addr):";
    AO_fetch_and_add_full(addr, (size_t)(-1));




    "AO_fetch_and_add_acquire_read(addr, incr):";
    AO_fetch_and_add_full(addr, incr);




    "AO_compare_and_swap_acquire_read(addr, oldval, newval):";
    AO_compare_and_swap_full(addr, oldval, newval);



}
