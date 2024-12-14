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

#include <string.h>

#include "saul.h"
#include "reed_sensor_driver.h"


static int read_nc(const void *dev, phydat_t *res)
{
    const reed_sensor_driver_t *d = (const reed_sensor_driver_t *)dev;
    reed_sensor_val_t val;
    reed_sensor_driver_read_nc(d,&val);

    res->val[0] = val;
    res->unit = UNIT_NONE;
    res->scale = 0;
    return 1;
}

static int read_no(const void *dev, phydat_t *res)
{
    const reed_sensor_driver_t *d = (const reed_sensor_driver_t *)dev;
    reed_sensor_val_t val;
    reed_sensor_driver_read_no(d,&val);

    res->val[0] = val;
    res->unit = UNIT_NONE;
    res->scale = 0;
    return 1;
}


const saul_driver_t reed_sensor_nc_saul_driver = {
    .read = read_nc,
    .write = saul_write_notsup,
    .type = SAUL_SENSE_BTN,
};

const saul_driver_t reed_sensor_no_saul_driver = {
    .read = read_no,
    .write = saul_write_notsup,
    .type = SAUL_SENSE_BTN,
};
