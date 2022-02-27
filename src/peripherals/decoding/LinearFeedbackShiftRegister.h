#ifndef LINEARFEEDBACKSHIFTREGISTER_H__
#define LINEARFEEDBACKSHIFTREGISTER_H__

#include <stdint.h>

class LFSR {
   public:
    LFSR();
    void Reset();
    uint8_t Generate();
    uint32_t GeneratedValuesCount;
    uint8_t Seed;
    uint8_t State;

   private:
    uint8_t Taps = 8;
    uint8_t Bit;
};

#endif  // LINEARFEEDBACKSHIFTREGISTER_H__