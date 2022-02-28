#ifndef RLNCFRAME_H__
#define RLNCFRAME_H__

#include <stdint.h>

class RlncFrame {
   public:
    RlncFrame(uint8_t* payload, uint8_t size) {
        this->payload = payload;
        this->payloadSize = size;
    }

    void SetEncodingVector(uint8_t* encodingVector, uint8_t size) {
        this->encodingVector = encodingVector;
        this->encodingVectorSize = size;
    }

   private:
    uint8_t* payload;
    uint8_t payloadSize;
    uint8_t* encodingVector;
    uint8_t encodingVectorSize;
};

#endif
