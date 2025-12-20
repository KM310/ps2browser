#ifndef STRING_OPT_H
#define STRING_OPT_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

size_t mips_fast_strlen(const char *s);
void *mips_fast_memcpy(void *dest, const void *src, size_t n);

#ifdef __cplusplus
}
#endif

#endif
