#include <stm32f446xx.h>

#include "stm32f4xx_hal_gpio.h"

#include "goodisplay_driver/goodisplay_driver.h"
#include "soil_sensor/soil_sensor.h"

#define DELAY_MAX 200000
#define DRY_OUT_MAX 3500

volatile uint32_t value;

int main(void)
{
    RCC->AHB1ENR |= 1; // Enable GPIOA

    GPIO_InitTypeDef GPIOA_params;
    uint32_t delay = 0;

    GPIOA_params.Pin = GPIO_PIN_1;
    GPIOA_params.Mode = GPIO_MODE_OUTPUT_PP;
    GPIOA_params.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(GPIOA, &GPIOA_params);
    SOIL_Sensor sensor;
    SOIL_Sensor_Init(&sensor);
    while(1)
    {
        if(value > DRY_OUT_MAX)
        {
            HAL_GPIO_WritePin(GPIOA, GPIOA_params.Pin, GPIO_PIN_SET);
        }
        else
        {
            HAL_GPIO_WritePin(GPIOA, GPIOA_params.Pin, GPIO_PIN_RESET);
        }
        for(delay = 0; delay < DELAY_MAX; delay++);
        value = SOIL_Sensor_GetValue(&sensor);
    }
    return 0;
}
