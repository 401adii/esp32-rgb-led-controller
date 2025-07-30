/**
 * @file gpio_init.h
 * @brief GPIO Pin Management with State Tracking
 * 
 * Provides initialization and deinitialization functions for GPIO pins
 * with internal state tracking to prevent redundant operations.
 * 
 * @note Maintains an internal usage tracker to avoid re-initializing
 *       already configured pins and prevent deinitialization of unused pins.
 */

#ifndef GPIO_INIT_H
#define GPIO_INIT_H

#include "driver/gpio.h"
#include "esp_check.h"

/**
 * @brief Initialize a GPIO pin as output
 * @param pin GPIO pin number to initialize
 * @return 
 *      - ESP_OK: Successfully initialized or already initialized
 *      - ESP_ERR_INVALID_ARG: Parameter error
 *      - Other ESP errors from underlying gpio_config()
 * 
 * Configures the pin as a digital output with:
 *   - Disabled pull-up/pull-down
 *   - Disabled interrupts
 * 
 * @note If pin is already initialized, returns ESP_OK without reconfiguration
 */
esp_err_t gpio_init(gpio_num_t pin);

/**
 * @brief Deinitialize a GPIO pin
 * @param pin GPIO pin number to deinitialize
 * @return 
 *      - ESP_OK: Successfully deinitialized
 *      - ESP_ERR_INVALID_ARG: Parameter error
 *      - Other ESP errors from gpio_reset_pin()
 * 
 * Performs:
 *   1. Sets pin direction to output (pre-reset step)
 *   2. Resets pin configuration to default state
 *   3. Marks pin as unused in internal tracker
 * 
 * @warning Will return an error if pin wasn't previously initialized
 */
esp_err_t gpio_deinit(gpio_num_t pin);

#endif