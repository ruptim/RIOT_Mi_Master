/*
 * Copyright (C) 2024 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     drivers_reed_sensor_driver
 *
 * @{
 * @file
 * @brief       Default configuration
 *
 * @author      Timon Rupelt <timon.rupelt@haw-hamburg.de>
 */

#ifndef REED_SENSOR_DRIVER_PARAMS_H
#define REED_SENSOR_DRIVER_PARAMS_H

#include "board.h"
#include "reed_sensor_driver.h"
#include "reed_sensor_driver_constants.h"
#include "saul_reg.h"

#  ifdef __cplusplus
extern "C" {
#endif

/**
 * @name    Default comfiguration parameters for reed sensor driver
 * @{
 */
#ifndef REED_SENSOR_DRIVER_PARAM_NC_PIN
#define REED_SENSOR_DRIVER_PARAM_NC_PIN GPIO_PIN(0, 8)          /**< default NC pin */
#endif
#ifndef REED_SENSOR_DRIVER_PARAM_NO_PIN
#define REED_SENSOR_DRIVER_PARAM_NO_PIN GPIO_PIN(0, 6)          /**< default NO pin */
#endif
#ifndef REED_SENSOR_DRIVER_PARAM_NC_INT_FLANK
#define REED_SENSOR_DRIVER_PARAM_NC_INT_FLANK (GPIO_BOTH)       /**< default NC flank */
#endif
#ifndef REED_SENSOR_DRIVER_PARAM_NO_INT_FLANK
#define REED_SENSOR_DRIVER_PARAM_NO_INT_FLANK (GPIO_BOTH)       /**< default NC flank */
#endif
#ifndef REED_SENSOR_DRIVER_PARAM_NC_CALLBACK
#define REED_SENSOR_DRIVER_PARAM_NC_CALLBACK (NULL)             /**< no NO callback by default */
#endif
#ifndef REED_SENSOR_DRIVER_PARAM_NO_CALLBACK
#define REED_SENSOR_DRIVER_PARAM_NO_CALLBACK (NULL)             /**< no NC callback by default */
#endif
#ifndef REED_SENSOR_DRIVER_PARAM_NC_CALLBACK_ARGS
#define REED_SENSOR_DRIVER_PARAM_NC_CALLBACK_ARGS (NULL)        /**< no NO callback args by default */
#endif
#ifndef REED_SENSOR_DRIVER_PARAM_NO_CALLBACK_ARGS
#define REED_SENSOR_DRIVER_PARAM_NO_CALLBACK_ARGS (NULL)        /**< no NO callback args by default */
#endif
#ifndef REED_SENSOR_DRIVER_PARAM_USE_EXTERNAL_PULLDOWN
#define REED_SENSOR_DRIVER_PARAM_USE_EXTERNAL_PULLDOWN (false)  /**< no external pulldown by default */
#endif
#ifndef REED_SENSOR_DRIVER_PARAM_DEBOUNCE_MS
#define REED_SENSOR_DRIVER_PARAM_DEBOUNCE_MS (20)               /**< 20 ms debounce delay by default */
#endif

#ifndef REED_SENSOR_DRIVER_PARAMS
#define REED_SENSOR_DRIVER_PARAMS                                                    \
        {                                                                            \
            .nc_pin = REED_SENSOR_DRIVER_PARAM_NC_PIN,                               \
            .no_pin = REED_SENSOR_DRIVER_PARAM_NO_PIN,                               \
            .nc_int_flank = REED_SENSOR_DRIVER_PARAM_NC_INT_FLANK,                   \
            .no_int_flank = REED_SENSOR_DRIVER_PARAM_NO_INT_FLANK,                   \
            .nc_callback = REED_SENSOR_DRIVER_PARAM_NC_CALLBACK,                     \
            .no_callback = REED_SENSOR_DRIVER_PARAM_NO_CALLBACK,                     \
            .nc_callback_args = REED_SENSOR_DRIVER_PARAM_NC_CALLBACK_ARGS,           \
            .no_callback_args = REED_SENSOR_DRIVER_PARAM_NO_CALLBACK_ARGS,           \
            .use_external_pulldown = REED_SENSOR_DRIVER_PARAM_USE_EXTERNAL_PULLDOWN, \
            .debounce_ms = REED_SENSOR_DRIVER_PARAM_DEBOUNCE_MS }   /**< default driver params */
#endif
#ifndef REED_SENSOR_DRIVER_NC_INFO
#define REED_SENSOR_DRIVER_NC_INFO { .name = "reed_sensor_nc" }     /**< saul device name for NO pin */
#endif

#ifndef REED_SENSOR_DRIVER_NO_INFO
#define REED_SENSOR_DRIVER_NO_INFO { .name = "reed_sensor_no" }     /**< saul device name for NC pin */
#endif
/**@}*/

/**
 * @brief   Configuration struct
 */
static const reed_sensor_driver_params_t reed_sensor_driver_params[] =
{ REED_SENSOR_DRIVER_PARAMS };

/**
 * @brief   Additional meta information to keep in the SAUL registry
 */
static const saul_reg_info_t reed_sensor_driver_saul_info[] = { REED_SENSOR_DRIVER_NC_INFO,
                                                                REED_SENSOR_DRIVER_NO_INFO };

#ifdef __cplusplus
}
#endif

#endif /* REED_SENSOR_DRIVER_PARAMS_H */
/** @} */
