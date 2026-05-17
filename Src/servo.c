/**
 * @file servo.c
 * @brief Simple STM32 HAL servo motor control library implementation.
 */

#include "servo.h"

void Servo_Init(Servo_t *servo, TIM_HandleTypeDef *htim, uint32_t channel)
{
    if ((servo == NULL) || (htim == NULL))
    {
        return;
    }

    servo->htim = htim;
    servo->channel = channel;

    servo->min_period = SERVO_MIN_PERIOD;
    servo->max_period = SERVO_MAX_PERIOD;
}

HAL_StatusTypeDef Servo_Start(Servo_t *servo)
{
    if ((servo == NULL) || (servo->htim == NULL))
    {
        return HAL_ERROR;
    }

    return HAL_TIM_PWM_Start(servo->htim, servo->channel);
}

HAL_StatusTypeDef Servo_Stop(Servo_t *servo)
{
    if ((servo == NULL) || (servo->htim == NULL))
    {
        return HAL_ERROR;
    }

    return HAL_TIM_PWM_Stop(servo->htim, servo->channel);
}

void Servo_SetAngle(Servo_t *servo, uint8_t angle)
{
    uint16_t compare_value;
    uint16_t range;

    if ((servo == NULL) || (servo->htim == NULL))
    {
        return;
    }

    if (angle > SERVO_MAX_ANGLE)
    {
        angle = SERVO_MAX_ANGLE;
    }

    range = servo->max_period - servo->min_period;

    compare_value = servo->min_period +
                    (uint16_t)(((uint32_t)angle * range) / SERVO_MAX_ANGLE);

    __HAL_TIM_SET_COMPARE(servo->htim, servo->channel, compare_value);
}
