/*!
 * \file      adc-board.c
 *
 * \brief     Target board ADC driver implementation
 *
 * \copyright Revised BSD License, see section \ref LICENSE.
 *
 * \code
 *                ______                              _
 *               / _____)             _              | |
 *              ( (____  _____ ____ _| |_ _____  ____| |__
 *               \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 *               _____) ) ____| | | || |_| ____( (___| | | |
 *              (______/|_____)_|_|_| \__)_____)\____)_| |_|
 *              (C)2013-2017 Semtech
 *
 * \endcode
 *
 * \author    Miguel Luis ( Semtech )
 *
 * \author    Gregory Cristian ( Semtech )
 */
#include "stm32f4xx.h"
#include "board-config.h"
#include "adc-board.h"

ADC_HandleTypeDef AdcHandle;

void AdcMcuInit(Adc_t *obj, PinNames adcInput)
{
  AdcHandle.Instance = ADC1;

  // EEEEHHH
  // __ADC_CLK_ENABLE();

  HAL_ADC_DeInit(&AdcHandle);

  if (adcInput != NC)
  {
    GpioInit(&obj->AdcInput, adcInput, PIN_ANALOGIC, PIN_PUSH_PULL, PIN_NO_PULL, 0);
  }
}

void AdcMcuConfig(void)
{
  // Configure ADC
  AdcHandle.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV2; // ADC_CLOCK_SYNC_PCLK_DIV1
  AdcHandle.Init.Resolution = ADC_RESOLUTION_12B;
  AdcHandle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  AdcHandle.Init.ContinuousConvMode = DISABLE;
  AdcHandle.Init.DiscontinuousConvMode = DISABLE;
  AdcHandle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  AdcHandle.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  AdcHandle.Init.DMAContinuousRequests = DISABLE;
  AdcHandle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  AdcHandle.Init.NbrOfConversion = 1;
  // AdcHandle.Init.LowPowerAutoWait      = DISABLE;
  HAL_ADC_Init(&AdcHandle);
}

uint16_t AdcMcuReadChannel(Adc_t *obj, uint32_t channel)
{
  ADC_ChannelConfTypeDef adcConf = {0};
  // uint16_t adcData = 0;

  // Enable HSI
  __HAL_RCC_HSI_ENABLE();

  // Wait till HSI is ready
  while (__HAL_RCC_GET_FLAG(RCC_FLAG_HSIRDY) == RESET)
  {
  }

  // EEHHHHH
  // __ADC_CLK_ENABLE();

  // Calibrate ADC if any calibraiton hardware
  // HAL_ADCEx_Calibration_Start( &AdcHandle, ADC_SINGLE_ENDED );

  adcConf.Channel = channel;
  adcConf.Rank = LL_ADC_REG_RANK_1;
  adcConf.SamplingTime = ADC_SAMPLETIME_84CYCLES;

  HAL_ADC_ConfigChannel( &AdcHandle, &adcConf );

  // Start ADC Software Conversion
  HAL_ADC_Start( &AdcHandle );

  HAL_ADC_PollForConversion( &AdcHandle, HAL_MAX_DELAY );

  // adcData = HAL_ADC_GetValue( &AdcHandle );

  __HAL_ADC_DISABLE( &AdcHandle );

  // EEHHHH
  // __HAL_RCC_ADC_CLK_DISABLE( );

  // Disable HSI
  __HAL_RCC_HSI_DISABLE( );

  return 0x00; // adcData;
}
