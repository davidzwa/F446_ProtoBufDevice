#ifndef BME688_H
#define BME688_H

#include "bme68x.h"
#include "bme68x_common.h"

class BME688 {
  public:
    BME688(void){};
    int init(I2c_t* _I2C_hdle);
    int measure(struct bme68x_data* data);
  private:
    struct bme68x_dev bme;
    struct bme68x_conf conf;
    struct bme68x_heatr_conf heatr_conf;
};

#endif // BME688_H
