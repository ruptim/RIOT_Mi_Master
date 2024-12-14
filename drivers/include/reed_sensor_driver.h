/*
 * Copyright (C) 2024 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    drivers_reed_sensor_driver Reed Sensor
 * @ingroup     drivers_sensors
 * @brief       A high-level driver for reed sensors.
 *
 * @{
 *
 * @file
 *
 * @author      Timon Rupelt <timon.rupelt@haw-hamburg.de>
 */

#ifndef REED_SENSOR_DRIVER_H
#  define REED_SENSOR_DRIVER_H

/* Add header includes here */
#  include "periph/gpio.h"
#  include <stdint.h>

#  ifdef __cplusplus
extern "C" {
#  endif

/**
 * @brief   Sensor value type of a reed sensor.
 */
typedef uint8_t reed_sensor_val_t;

/**
 * @brief   Device initialization parameters
 */
typedef struct {
    gpio_t nc_pin;                  /**< normaly-closed pin */
    gpio_t no_pin;                  /**< normaly-open pin */
    gpio_flank_t nc_int_flank;      /**< interrupt flank for nc pin */
    gpio_flank_t no_int_flank;      /**< interrupt flank for no pin */
    void (*nc_callback)(void *);    /**< interrupt callback for no */
    void (*no_callback)(void *);    /**< interrupt callback for nc */
    void *nc_callback_args;         /**< callback arguments for no */
    void *no_callback_args;         /**< interrupt callback for nc */
    bool use_external_pulldown;     /**< flag to disable use of internal pulldown */
    uint32_t debounce_ms;           /**< debounce delay in ms */

} reed_sensor_driver_params_t;

/**
 * @brief   Device descriptor for the reed sensor driver
 */
typedef struct {
    /** Device initialization parameters */
    reed_sensor_driver_params_t params;
} reed_sensor_driver_t;

/**
 * @brief   Initialize a the gpio for using a reed sensor.
 *
 *
 * @param[inout] dev        Device descriptor of the driver
 * @param[in]    params     Initialization parameters
 *
 * @return                  0 on success
 */
int reed_sensor_driver_init(reed_sensor_driver_t *dev, const reed_sensor_driver_params_t *params);

/**
 * @brief   Read value at the normaly-closed pin of the reed sensor.
 *
 *
 * @param[in]       dev     Device descriptor of the driver
 * @param[inout]    val     Value read at the pin
 *
 * @return                  0 on success
 */
int reed_sensor_driver_read_nc(const reed_sensor_driver_t *dev, reed_sensor_val_t *val);

/**
 * @brief   Read value at the normaly-open pin of the reed sensor.
 *
 *
 * @param[in]       dev      Device descriptor of the driver
 * @param[inout]    val     Value read at the pin
 *
 * @return                  0 on success
 */
int reed_sensor_driver_read_no(const reed_sensor_driver_t *dev, reed_sensor_val_t *val);

/**
 * @brief   Default callback function for normally-open pin for debouncing.
 *
 *
 * @param[in]       args    Arguments for callback function
 *
 * @return                  0 on success
 */
void reed_sensor_driver_read_no_defaul_callback(void *args);

/**
 * @brief   Default callback function for normally-closed pin for debouncing.
 *
 *
 * @param[in]       args    Arguments for callback function
 *
 * @return                  0 on success
 */
void reed_sensor_driver_read_nc_defaul_callback(void *args);

#  ifdef __cplusplus
}
#  endif

#endif /* REED_SENSOR_DRIVER_H */
/** @} */
