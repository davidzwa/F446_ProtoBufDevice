#ifndef RLNCFRAME_H__
#define RLNCFRAME_H__

#include <stdint.h>

#include <vector>

using namespace std;

#define SYMB uint8_t

class RlncFrame {
   public:
    RlncFrame(vector<SYMB> encodingVector, const SYMB* payload, const uint32_t size) {
        for (uint8_t i = 0; i < encodingVector.size(); i++) {
            this->augVector.push_back(encodingVector[i]);
        }

        for (uint8_t i = 0; i < size; i++) {
            this->augVector.push_back(payload[i]);
        }
    }

    vector<SYMB> augVector;
};

#endif
