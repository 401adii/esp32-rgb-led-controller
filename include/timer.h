/**
 * @file timer_init.h
 * @brief General Purpose Timer (GPT) Management
 * 
 * Provides initialization and control functions for ESP32's General Purpose Timer (GPT)
 * with fixed 10 kHz resolution. Includes time conversion and elapsed time checking utilities.
 * 
 * @note Timer resolution is fixed at 10 kHz (RESOLUTION = 10000)
 */

#ifndef TIMER_INIT_H
#define TIMER_INIT_H

#include "driver/gptimer.h"

/// Timer resolution in Hz (fixed at 10 kHz)
#define RESOLUTION 10000

/**
 * @brief Initialize and configure a new GPTimer
 * @return Handle to the created timer (NULL on failure)
 * 
 * Creates a new GPTimer instance with:
 *  - Clock source: Default (typically APB clock)
 *  - Direction: Count up
 *  - Resolution: 10 kHz (10000 Hz)
 * 
 * @note Timer is created but not enabled/started by this function
 */
gptimer_handle_t timer_init(void);

/**
 * @brief Deinitialize and delete a timer
 * @param timer Timer handle to delete
 * @return 
 *      - ESP_OK: Success
 *      - ESP_ERR_INVALID_ARG: Invalid timer handle
 *      - Other ESP errors from GPTimer API
 * 
 * Disabled and deletes the timer.
 */
esp_err_t timer_deinit(gptimer_handle_t timer);

/**
 * @brief Start a timer
 * @param timer Timer handle to start
 * @return 
 *      - ESP_OK: Success
 *      - ESP_ERR_INVALID_ARG: Invalid timer handle
 *      - Other ESP errors from GPTimer API
 * 
 * Enables and starts the timer
 */
esp_err_t timer_start(gptimer_handle_t timer);

esp_err_t timer_stop(gptimer_handle_t timer);

/**
 * @brief Reset timer counter to zero
 * @param timer Timer handle to reset
 * @return 
 *      - ESP_OK: Success
 *      - ESP_ERR_INVALID_ARG: Invalid timer handle
 *      - Other ESP errors from GPTimer API
 */
esp_err_t timer_reset(gptimer_handle_t timer);

/**
 * @brief Check if timer has reached specified time
 * @param timer Timer handle to check
 * @param time_ms Time threshold in milliseconds
 * @return 
 *      - true: Current count ≥ threshold time
 *      - false: Current count < threshold time
 * 
 * @note Uses raw count value for comparison
 * @warning Function may return incorrect results if timer was reset after starting
 */
bool timer_passed(gptimer_handle_t timer, uint32_t time_ms);

/**
 * @brief Convert milliseconds to timer ticks
 * @param time_ms Time in milliseconds
 * @return Equivalent number of timer ticks
 * 
 * Conversion formula: 
 *   ticks = milliseconds × (RESOLUTION / 1000)
 * 
 * For RESOLUTION = 10000 Hz:
 *   1 ms = 10 ticks
 *   100 ms = 1000 ticks
 */
uint64_t timer_ms_to_ticks(uint32_t time_ms);

#endif
