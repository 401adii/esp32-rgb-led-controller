/**
 * @file led_controller.h
 * @brief LED Controller driver using ESP32's LEDC peripheral
 * 
 * Provides initialization and control functions for PWM-driven LEDs
 * using ESP-IDF's LED Control (LEDC) module. This implementation is
 * hardcoded to use:
 *   - Low Speed Mode only
 *   - 8-bit PWM resolution (0-255 duty cycle range)
 * 
 * @note The configuration uses fixed parameters:
 *  - PWM frequency: 156.25 kHz
 *  - Speed mode: LEDC_LOW_SPEED_MODE
 *  - Duty resolution: 8 bits (256 levels)
 */

#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include"driver/ledc.h"
#include"driver/gpio.h"
#include"esp_check.h"

/// Default speed mode for LEDC (Low Speed Mode)
#define SPEED_MODE LEDC_LOW_SPEED_MODE
/// Default PWM frequency (156.25 kHz) for 8 bit resolution
#define PWM_FREQ 156250

/**
 * @brief Initialize LEDC timer configuration
 * @param timer LEDC timer unit (0-3)
 * 
 * Configures timer with predefined PWM frequency and default resolution.
 * Timer must be initialized before channels using it can be configured.
 */
esp_err_t ledc_timer_init(ledc_timer_t timer);

/**
 * @brief Initialize LEDC channel
 * @param channel LEDC channel (0-7)
 * @param timer Timer source for this channel
 * @param pin GPIO pin number to output PWM signal
 * 
 * Binds specified channel to a timer and GPIO pin with default configuration.
 * Channel will be initialized with 0% duty cycle.
 */
esp_err_t ledc_channel_init(ledc_channel_t channel, ledc_timer_t timer, gpio_num_t pin);

/**
 * @brief Deinitialize LEDC timer
 * @param timer LEDC timer unit (0-3)
 * 
 * Releases resources associated with the timer. All channels using this timer
 * should be deinitialized first.
 */
esp_err_t ledc_timer_deinit(ledc_timer_t timer);

/**
 * @brief Deinitialize LEDC channel
 * @param channel LEDC channel (0-7)
 * 
 * Stops PWM output and releases channel resources. Does not change GPIO state.
 */
esp_err_t ledc_channel_deinit(ledc_channel_t channel);


/**
 * @brief Set PWM duty cycle for channel
 * @param channel LEDC channel (0-7)
 * @param duty PWM duty value (0 = 0%, 255 = 100%)
 * 
 * Duty range depends on timer resolution. For 8-bit resolution:
 * - 0% duty = 0
 * - 100% duty = 255
 * 
 * Enables the channel if not already active.
 */
esp_err_t ledc_channel_set(ledc_channel_t channel, uint8_t duty);

/**
 * @brief Disable PWM output on channel
 * @param channel LEDC channel (0-7)
 * 
 * Stops PWM generation but maintains channel configuration.
 * GPIO output will remain at its last state.
 */
esp_err_t ledc_channel_disable(ledc_channel_t channel);

#endif