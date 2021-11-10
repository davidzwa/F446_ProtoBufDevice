#include <string.h>

#include "ProtoWriteBuffer.h"

void ProtoWriteBuffer::clear() {
    write_index_ = 0;
}

uint32_t ProtoWriteBuffer::get_size() const {
    return write_index_;
}

uint32_t ProtoWriteBuffer::get_max_size() const {
    return MAX_SIZE;
}

uint32_t ProtoWriteBuffer::get_available_size() const {
    return MAX_SIZE - write_index_;
}

bool ProtoWriteBuffer::push(const uint8_t byte) {
    bool return_value = MAX_SIZE > write_index_;
    if (return_value) {
        data_[write_index_] = byte;
        ++write_index_;
    }
    return return_value;
}

bool ProtoWriteBuffer::push(const uint8_t* bytes, const uint32_t length) {
    bool return_value = MAX_SIZE > (write_index_ + length);
    if (return_value) {
        memcpy(data_ + write_index_, bytes, length);
        write_index_ += length;
    }
    return return_value;
}

uint8_t* ProtoWriteBuffer::get_data() {
    return data_;
}
