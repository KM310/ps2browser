#pragma once
#include <cstddef>

class Buffer {
public:
    Buffer(size_t size);
    ~Buffer();

    char* data();
    size_t size() const;

private:
    char* ptr;
    size_t len;
};
