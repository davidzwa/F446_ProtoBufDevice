/*
*    __________ ____
*   |__  / ____|  _ \ 
*     / /|  _| | | | |
*    / /_| |___| |_| |
*   /____|_____|____/ 
*  Copyright (C) 2020 - 2022
* 
*  License:  Revised BSD License, see LICENSE.TXT file included in the project
*  Authors:  David Zwart (ZED)
*  Version: 0.1.1
*  Date 6 Nov 2021
* 
*  Description:
*   Implement the reading interface for EmbeddedProto Protobuf
*/

#include "ProtoReadBuffer.h"

ProtoReadBuffer::ProtoReadBuffer()
    : data_{0},
      write_index_(0),
      read_index_(0) {
}

uint32_t ProtoReadBuffer::get_size() const {
    return write_index_;
}

uint32_t ProtoReadBuffer::get_max_size() const {
    return MAX_SIZE;
}

bool ProtoReadBuffer::peek(uint8_t& byte) const {
    bool return_value = write_index_ > read_index_;
    if (return_value) {
        byte = data_[read_index_];
    }
    return return_value;
}

void ProtoReadBuffer::advance() {
    ++read_index_;
}

void ProtoReadBuffer::advance(const uint32_t N) {
    read_index_ += N;
}

bool ProtoReadBuffer::pop(uint8_t& byte) {
    bool return_value = write_index_ > read_index_;
    if (return_value) {
        byte = data_[read_index_];
        ++read_index_;
    }
    return return_value;
}

uint8_t* ProtoReadBuffer::get_data_array() {
    return data_;
}

uint32_t& ProtoReadBuffer::get_bytes_written() {
    return write_index_;
}

void ProtoReadBuffer::clear() {
    read_index_ = 0;
    write_index_ = 0;
}

bool ProtoReadBuffer::push(uint8_t& byte) {
    bool return_value = MAX_SIZE > write_index_;
    if (return_value) {
        data_[write_index_] = byte;
        ++write_index_;
    }
    return return_value;
}
