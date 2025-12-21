#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void* buffer_create(int size);
void  buffer_destroy(void* buf);
char* buffer_data(void* buf);
int   buffer_size(void* buf);

#ifdef __cplusplus
}
#endif
