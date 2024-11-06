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
#define REED_SENSOR_DRIVER_H

/* Add header includes here */
#include "periph/gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Declare the API of the driver */


typedef uint16_t reed_sensor_val_t;


/**
 * @brief   Device initialization parameters
 */
typedef struct {
    /* add initialization params here */
    gpio_t nc_pin;
    gpio_t no_pin;
    gpio_flank_t nc_int_flank;
    gpio_flank_t no_int_flank;
    void* nc_callback;
    void* no_callback;
    void* nc_callback_args;
    void* no_callback_args;
    bool use_external_pulldown;

} reed_sensor_driver_params_t;

/**
 * @brief   Device descriptor for the driver
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

#ifdef __cplusplus
}
#endif

#endif /* REED_SENSOR_DRIVER_H */
/** @} */
