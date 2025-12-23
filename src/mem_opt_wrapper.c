#include "mem_opt.h"
#include <string.h>

void* fast_memcpy(void* dst, const void* src, unsigned int size) {
#if defined(__mips__) || defined(__mips)
    return mips_fast_memcpy(dst, src, size);
#else
    return memcpy(dst, src, size);
#endif
}
