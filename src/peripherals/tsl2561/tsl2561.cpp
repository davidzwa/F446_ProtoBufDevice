#include "tsl2561.h"
#include "i2c.h"
#include "delay.h"

#pragma message("Compiled2")

int TSL2561::init(I2c_t* _I2C_hdle) {
    // Optional
    this->i2c_h = _I2C_hdle;
    
    int success = 0;
    
    success += writeRegister(TSL2561_Address, TSL2561_Control, 0x03); // POWER UP   
    success += writeRegister(TSL2561_Address, TSL2561_Timing, 0x00); //No High Gain (1x), integration time of 13ms
    success += writeRegister(TSL2561_Address, TSL2561_Interrupt, 0x00);
    success += writeRegister(TSL2561_Address, TSL2561_Control, 0x00); // POWER Down
    
    return success;
}

uint8_t TSL2561::readRegister(int deviceAddress, uint8_t address) {
    uint8_t value;

    // i2c_h->write(deviceAddress, (char*) &address, 1, true);
    I2cWriteBuffer(&i2c_h, deviceAddress,(uint8_t*) &address, 1);
        
    // i2c_h->read(deviceAddress, (char*) &value, 1);
    I2cReadBuffer(&i2c_h, deviceAddress,(uint8_t*) &value, 1);

    return value;
}

int TSL2561::writeRegister(int deviceAddress, uint8_t address, uint8_t val) {
    uint8_t data[2] = {address, val};
    
    // return i2c_h->write(deviceAddress, (char*) &data, 2);
    return I2cWriteBuffer(&i2c_h, deviceAddress, (uint8_t*) &data, 2);
}

void TSL2561::getLux(void) {
    CH0_LOW = readRegister(TSL2561_Address, TSL2561_Channal0L);
    CH0_HIGH = readRegister(TSL2561_Address, TSL2561_Channal0H);
    //read two bytes from registers 0x0E and 0x0F
    CH1_LOW = readRegister(TSL2561_Address, TSL2561_Channal1L);
    CH1_HIGH = readRegister(TSL2561_Address, TSL2561_Channal1H);

    ch0 = (CH0_HIGH << 8) | CH0_LOW;
    ch1 = (CH1_HIGH << 8) | CH1_LOW;
    
}



uint16_t TSL2561::readIRLuminosity() { // read Infrared channel value only, not convert to lux.
    writeRegister(TSL2561_Address, TSL2561_Control, 0x03); // POWER UP
    Delay(14);
    getLux();

    writeRegister(TSL2561_Address, TSL2561_Control, 0x00); // POWER Down
    if (ch1 == 0) {
        return 0;
    }
    if (ch0 / ch1 < 2 && ch0 > 4900) {
        return 1;  //ch0 out of range, but ch1 not. the lux is not valid in this situation.
    }
    return ch1;
}

uint16_t TSL2561::readFSpecLuminosity() { //read Full Spectrum channel value only,  not convert to lux.
    writeRegister(TSL2561_Address, TSL2561_Control, 0x03); // POWER UP
    Delay(14);
    getLux();

    writeRegister(TSL2561_Address, TSL2561_Control, 0x00); // POWER Down
    if (ch1 == 0) {
        return 0;
    }
    if (ch0 / ch1 < 2 && ch0 > 4900) {
        return 1;  //ch0 out of range, but ch1 not. the lux is not valid in this situation.
    }
    return ch0;
}

signed long TSL2561::readVisibleLux() {
    writeRegister(TSL2561_Address, TSL2561_Control, 0x03); // POWER UP
    Delay(14);
    getLux();

    writeRegister(TSL2561_Address, TSL2561_Control, 0x00); // POWER Down
    if (ch1 == 0) {
        return 0;
    }
    if (ch0 / ch1 < 2 && ch0 > 4900) {
        return -1;  //ch0 out of range, but ch1 not. the lux is not valid in this situation.
    }
    return calculateLux(0, 0, 0);  //T package, no gain, 13ms
}

unsigned long TSL2561::calculateLux(unsigned int iGain, unsigned int tInt, int iType) {
    switch (tInt) {
        case 0:  // 13.7 msec
            chScale = CHSCALE_TINT0;
            break;
        case 1: // 101 msec
            chScale = CHSCALE_TINT1;
            break;
        default: // assume no scaling
            chScale = (1 << CH_SCALE);
            break;
    }
    if (!iGain) {
        chScale = chScale << 4;    // scale 1X to 16X
    }
    // scale the channel values
    channel0 = (ch0 * chScale) >> CH_SCALE;
    channel1 = (ch1 * chScale) >> CH_SCALE;

    ratio1 = 0;
    if (channel0 != 0) {
        ratio1 = (channel1 << (RATIO_SCALE + 1)) / channel0;
    }
    // round the ratio value
    unsigned long ratio = (ratio1 + 1) >> 1;

    switch (iType) {
        case 0: // T package
            if ((ratio >= 0) && (ratio <= K1T)) {
                b = B1T;
                m = M1T;
            } else if (ratio <= K2T) {
                b = B2T;
                m = M2T;
            } else if (ratio <= K3T) {
                b = B3T;
                m = M3T;
            } else if (ratio <= K4T) {
                b = B4T;
                m = M4T;
            } else if (ratio <= K5T) {
                b = B5T;
                m = M5T;
            } else if (ratio <= K6T) {
                b = B6T;
                m = M6T;
            } else if (ratio <= K7T) {
                b = B7T;
                m = M7T;
            } else if (ratio > K8T) {
                b = B8T;
                m = M8T;
            }
            break;
        case 1:// CS package
            if ((ratio >= 0) && (ratio <= K1C)) {
                b = B1C;
                m = M1C;
            } else if (ratio <= K2C) {
                b = B2C;
                m = M2C;
            } else if (ratio <= K3C) {
                b = B3C;
                m = M3C;
            } else if (ratio <= K4C) {
                b = B4C;
                m = M4C;
            } else if (ratio <= K5C) {
                b = B5C;
                m = M5C;
            } else if (ratio <= K6C) {
                b = B6C;
                m = M6C;
            } else if (ratio <= K7C) {
                b = B7C;
                m = M7C;
            }
    }
    temp = ((channel0 * b) - (channel1 * m));
    if (temp < 0) {
        temp = 0;
    }
    temp += (1 << (LUX_SCALE - 1));
    // strip off fractional portion
    lux = temp >> LUX_SCALE;
    return (lux);
}
