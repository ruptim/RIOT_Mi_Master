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

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name    Set default configuration parameters
 * @{
 */
#ifndef REED_SENSOR_DRIVER_PARAM_NC_PIN
#define REED_SENSOR_DRIVER_PARAM_NC_PIN GPIO_PIN(0,8)
#endif
#ifndef REED_SENSOR_DRIVER_PARAM_NO_PIN
#define REED_SENSOR_DRIVER_PARAM_NO_PIN GPIO_PIN(0,6)
#endif
#ifndef REED_SENSOR_DRIVER_PARAM_NC_INT_FLANK 
#define REED_SENSOR_DRIVER_PARAM_NC_INT_FLANK (GPIO_BOTH)
#endif
#ifndef REED_SENSOR_DRIVER_PARAM_NO_INT_FLANK 
#define REED_SENSOR_DRIVER_PARAM_NO_INT_FLANK (GPIO_BOTH)
#endif
#ifndef REED_SENSOR_DRIVER_PARAM_NC_CALLBACK
#define REED_SENSOR_DRIVER_PARAM_NC_CALLBACK (NULL)
#endif
#ifndef REED_SENSOR_DRIVER_PARAM_NO_CALLBACK
#define REED_SENSOR_DRIVER_PARAM_NO_CALLBACK (NULL)
#endif
#ifndef REED_SENSOR_DRIVER_PARAM_NC_CALLBACK_ARGS
#define REED_SENSOR_DRIVER_PARAM_NC_CALLBACK_ARGS (NULL)
#endif
#ifndef REED_SENSOR_DRIVER_PARAM_NO_CALLBACK_ARGS
#define REED_SENSOR_DRIVER_PARAM_NO_CALLBACK_ARGS       (NULL)
#endif
#ifndef REED_SENSOR_DRIVER_PARAM_USE_EXTERNAL_PULLUP
#define REED_SENSOR_DRIVER_PARAM_USE_EXTERNAL_PULLUP    (false)
#endif


#ifndef REED_SENSOR_DRIVER_PARAMS
#define REED_SENSOR_DRIVER_PARAMS                       { .nc_pin = REED_SENSOR_DRIVER_PARAM_NC_PIN,                            \
                                                          .no_pin = REED_SENSOR_DRIVER_PARAM_NO_PIN,                            \
                                                          .nc_int_flank = REED_SENSOR_DRIVER_PARAM_NC_INT_FLANK,                \
                                                          .no_int_flank = REED_SENSOR_DRIVER_PARAM_NO_INT_FLANK,                \
                                                          .nc_callback = REED_SENSOR_DRIVER_PARAM_NC_CALLBACK,                  \
                                                          .no_callback = REED_SENSOR_DRIVER_PARAM_NO_CALLBACK,                  \
                                                          .nc_callback_args = REED_SENSOR_DRIVER_PARAM_NC_CALLBACK_ARGS,        \
                                                          .no_callback_args = REED_SENSOR_DRIVER_PARAM_NO_CALLBACK_ARGS,        \
                                                          .use_external_pullup = REED_SENSOR_DRIVER_PARAM_USE_EXTERNAL_PULLUP }
#endif
#ifndef REED_SENSOR_DRIVER_NC_INFO
#define REED_SENSOR_DRIVER_NC_INFO            { .name = "reed_sensor_nc" }
#endif
#ifndef REED_SENSOR_DRIVER_NO_INFO
#define REED_SENSOR_DRIVER_NO_INFO            { .name = "reed_sensor_no" }
#endif
/**@}*/

/**
 * @brief   Configuration struct
 */
static const reed_sensor_driver_params_t reed_sensor_driver_params[] =
{
    REED_SENSOR_DRIVER_PARAMS
};

/**
 * @brief   Additional meta information to keep in the SAUL registry
 */
static const saul_reg_info_t reed_sensor_driver_saul_info[] =
{
    REED_SENSOR_DRIVER_NC_INFO,
    REED_SENSOR_DRIVER_NO_INFO
};

#ifdef __cplusplus
}
#endif

#endif /* REED_SENSOR_DRIVER_PARAMS_H */
/** @} */
