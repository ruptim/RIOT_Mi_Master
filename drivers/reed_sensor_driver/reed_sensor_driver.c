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

int reed_sensor_driver_init(reed_sensor_driver_t *dev, const reed_sensor_driver_params_t *params)
{
    assert(dev && params);

    gpio_mode_t mode = params->use_external_pullup ? GPIO_IN : GPIO_IN_PU;

    if (params->nc_callback != NULL) {
        gpio_init_int(params->nc_pin, mode, params->nc_int_flank, params->nc_callback,
                      params->nc_callback_args);
    }else{
        gpio_init(params->nc_pin, GPIO_IN);
    }

    if (params->no_callback != NULL) {
        gpio_init_int(params->no_pin, mode, params->no_int_flank, params->no_callback,
                      params->no_callback_args);
    }else{
        gpio_init(params->no_pin, GPIO_IN);
    }

    return 0;
}

int reed_sensor_driver_read_nc(const reed_sensor_driver_t *dev, reed_sensor_val_t *val){

    *val = (reed_sensor_val_t) gpio_read(dev->params.nc_pin);

    return 0;
}
int reed_sensor_driver_read_no(const reed_sensor_driver_t *dev, reed_sensor_val_t *val){

    *val = (reed_sensor_val_t) gpio_read(dev->params.nc_pin);
    
    return 0;
}