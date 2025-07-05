#ifndef __SOIL_SENSOR_H
#define __SOIL_SENSOR_H

#include <stdint.h>

#include "stm32f446xx.h"

#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_dma.h"
#include "stm32f4xx_hal_adc.h"

typedef struct 
{
    GPIO_TypeDef* port;
    uint32_t pin;
    GPIO_InitTypeDef GPIOX_params;
    ADC_HandleTypeDef adc_handle;
    uint32_t sensor_value;
} SOIL_Sensor;

void SOIL_Sensor_Init(SOIL_Sensor* sensor);
uint32_t SOIL_Sensor_GetValue(SOIL_Sensor* sensor);

#endif