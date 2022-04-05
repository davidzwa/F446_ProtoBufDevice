#ifndef LCG__H__
#define LCG__H__

#include "stdint.h"

/**
 * @brief Independent random implementation
 *
 */
class LCG {
   public:
    LCG() {
        Reset();
    }

    uint32_t Next(void) {
        return (_state = (uint32_t)((_state * 1103515245L + 12345L) % RAND_LOCAL_MAX));
    }

    uint8_t NextByte(void) {
        return (uint8_t)(Next() >> (32 - 8));
    }

    void ResetSeed(uint32_t seed) {
        _seed = seed;
        Reset();
    }

    void Reset() {
        _state = _seed;
    }

    uint32_t GetSeed() {
        return _seed;
    }

   private:
    uint32_t _seed = 1;
    uint32_t _state;
    const long RAND_LOCAL_MAX = 2147483647L;
};

#endif