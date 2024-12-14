/*
 * Copyright (C) 2024 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     drivers_reed_sensor_driver
 * @{
 *
 * @file
 * @brief       Device driver implementation for the Reed Sensor
 *
 * @author      Timon Rupelt <timon.rupelt@haw-hamburg.de>
 *
 * @}
 */

#include "reed_sensor_driver.h"
#include "reed_sensor_driver_constants.h"
#include "reed_sensor_driver_params.h"
#include "ztimer.h"


int reed_sensor_driver_init(reed_sensor_driver_t *dev, const reed_sensor_driver_params_t *params)
{
    assert(dev && params);

    dev->params = *params;

    gpio_mode_t mode = params->use_external_pulldown ? GPIO_IN : GPIO_IN_PD;

    /* Init normally-closed pin */
    if (params->nc_callback != NULL) {
        gpio_init_int(params->nc_pin, mode, params->nc_int_flank, reed_sensor_driver_read_nc_defaul_callback,
                      (void*) params);
    }
    else {
        gpio_init(params->nc_pin, GPIO_IN);
    }

    /* Init normally-open pin */
    if (params->no_callback != NULL) {
        gpio_init_int(params->no_pin, mode, params->no_int_flank, reed_sensor_driver_read_no_defaul_callback,
                      (void *)params);
    }
    else {
        gpio_init(params->no_pin, GPIO_IN);
    }

    return 0;
}

int reed_sensor_driver_read_nc(const reed_sensor_driver_t *dev, reed_sensor_val_t *val)
{
    *val = (reed_sensor_val_t)gpio_read(dev->params.nc_pin);

    return 0;
}
int reed_sensor_driver_read_no(const reed_sensor_driver_t *dev, reed_sensor_val_t *val)
{
    *val = (reed_sensor_val_t)gpio_read(dev->params.no_pin);

    return 0;
}

void reed_sensor_driver_read_no_defaul_callback(void *args)
{
    reed_sensor_driver_params_t* params = (reed_sensor_driver_params_t*) args;

    static ztimer_now_t no_debounce_ts = 0;

    ztimer_acquire(ZTIMER_MSEC);
    ztimer_now_t cur_ts = ztimer_now(ZTIMER_MSEC);
    ztimer_release(ZTIMER_MSEC);

    if (cur_ts - no_debounce_ts >= params->debounce_ms){
        no_debounce_ts = cur_ts;
        (params->no_callback)(params->no_callback_args);
    }
}

void reed_sensor_driver_read_nc_defaul_callback(void *args)
{
    reed_sensor_driver_params_t* params = (reed_sensor_driver_params_t*) args;

    static ztimer_now_t nc_debounce_ts = 0;

    ztimer_acquire(ZTIMER_MSEC);
    ztimer_now_t cur_ts = ztimer_now(ZTIMER_MSEC);
    ztimer_release(ZTIMER_MSEC);

    if (cur_ts - nc_debounce_ts >= params->debounce_ms){
        nc_debounce_ts = cur_ts;
        (params->nc_callback)(params->nc_callback_args);
    }
}
