#ifndef LINEARFEEDBACKSHIFTREGISTER_H__
#define LINEARFEEDBACKSHIFTREGISTER_H__

#include <stdint.h>

#include <vector>

using namespace std;

/**
 * @brief fixated LFSR verified with C# unit tests
 *
 */
class LFSR {
   public:
    LFSR(uint8_t seed);
    void ResetNewSeed(uint8_t seed);
    void Reset();
    uint8_t Generate();
    void GenerateMany(vector<uint8_t>& output, uint16_t count);
    uint32_t GeneratedValuesCount;
    uint8_t Seed;
    uint8_t State;

   private:
    uint8_t Taps = 8;
    uint8_t Bit;
};

#endif  // LINEARFEEDBACKSHIFTREGISTER_H__
