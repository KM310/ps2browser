#include "buffer_c_api.h"
#include "buffer.hpp"

void* buffer_create(int size) {
    return new Buffer(size);
}

void buffer_destroy(void* buf) {
    delete (Buffer*)buf;
}

char* buffer_data(void* buf) {
    return ((Buffer*)buf)->data();
}

int buffer_size(void* buf) {
    return (int)((Buffer*)buf)->size();
}
