#include "buffer.hpp"
#include <cstdlib>
#include "asm/asm_api.h"

Buffer::Buffer(size_t size) {
    ptr = (char*)malloc(size);
    len = size;
}

Buffer::~Buffer() {
    free(ptr);
}

char* Buffer::data() {
    return ptr;
}

size_t Buffer::size() const {
    return len;
}
