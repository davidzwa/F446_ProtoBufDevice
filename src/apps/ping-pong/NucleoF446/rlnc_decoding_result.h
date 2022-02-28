#ifndef RLNCDECODINGRESULT_H__
#define RLNCDECODINGRESULT_H__

#include <stdint.h>

class RlncDecodingResult {
    public:
     bool success;
     uint8_t generationIndex;
     //  uint8_t decodingOverhead;
     // uint8_t droppedPackets; // Based on seq number?
};

#endif
