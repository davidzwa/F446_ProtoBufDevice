#ifndef RLNCFRAME_H__
#define RLNCFRAME_H__

#include <stdint.h>

#include <vector>

using namespace std;

#define SYMB uint8_t

class RlncFrame {
   public:
    RlncFrame(SYMB* encBuffer, uint8_t encSize, const SYMB* payload, const uint32_t size) {
        for (uint8_t i; i < encSize; i++) {
            this->augVector.push_back(encBuffer[i]);
        }

        for (uint8_t i; i < size; i++) {
            this->augVector.push_back(payload[i]);
        }
    }

    vector<SYMB> augVector;
};

#endif
