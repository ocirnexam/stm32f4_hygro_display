#include "soil_sensor.h"

void SOIL_Sensor_Init(SOIL_Sensor *sensor)
{
    GPIO_InitTypeDef GPIOX_params;
    ADC_ChannelConfTypeDef adc_channel;

    // enable clocks for adc1 and gpioa
    RCC->APB2ENR |= 1 << 8; // ADC1 CLK ENABLE
    RCC->AHB1ENR |= 1 << 0; // GPIOA CLK ENABLE

    // GPIO configuration of port a pin 0 with analog mode
    GPIOX_params.Pin = GPIO_PIN_0;
    GPIOX_params.Mode = GPIO_MODE_ANALOG;
    GPIOX_params.Speed = GPIO_SPEED_MEDIUM;
    sensor->port = GPIOA;
    sensor->pin = GPIO_PIN_0;
    HAL_GPIO_Init(sensor->port, &GPIOX_params);

    // ADC 1 configuration with continuous conversion and swstart
    sensor->adc_handle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2; // Example prescaler
    sensor->adc_handle.Init.Resolution = ADC_RESOLUTION_12B; // 12-bit resolution
    sensor->adc_handle.Init.ScanConvMode = DISABLE; // Single channel mode
    sensor->adc_handle.Init.ContinuousConvMode = ENABLE; // Continuous conversion mode
    sensor->adc_handle.Init.DiscontinuousConvMode = DISABLE;
    sensor->adc_handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    sensor->adc_handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    sensor->adc_handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    sensor->adc_handle.Init.NbrOfConversion = 1; // Single conversion
    sensor->adc_handle.Init.DMAContinuousRequests = DISABLE;
    sensor->adc_handle.Init.EOCSelection = ADC_EOC_SEQ_CONV; // End of single conversion
    adc_channel.Channel = ADC_CHANNEL_0;
    adc_channel.SamplingTime = LL_ADC_SAMPLINGTIME_15CYCLES;
    adc_channel.Rank = 1;
    sensor->adc_handle.Instance = ADC1;

    HAL_ADC_Init(&sensor->adc_handle);
    HAL_ADC_ConfigChannel(&sensor->adc_handle, &adc_channel);
    HAL_ADC_Start(&sensor->adc_handle); // Start ADC
    // HAL_ADC_PollForConversion(&sensor->adc_handle, HAL_MAX_DELAY); // Poll for conversion 
}

uint32_t SOIL_Sensor_GetValue(SOIL_Sensor* sensor)
{
    return HAL_ADC_GetValue(&sensor->adc_handle);
}