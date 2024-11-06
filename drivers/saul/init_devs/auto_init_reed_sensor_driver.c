/*
 * Copyright (C) 2024 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     reed_sensor_driver
 * @{
 * @ingroup     sys_auto_init_saul
 * @brief       Auto initialization of reed sensor driver
 * @author      Timon Rupelt <timon.rupelt@haw-hamburg.de>
 * @file
 * @}
 */


#include "assert.h"
#include "log.h"
#include "saul_reg.h"
#include "reed_sensor_driver.h"
#include "reed_sensor_driver_params.h"

/**
 * @brief   Define the number of configured sensors
 */
#define RSD_NUM     ARRAY_SIZE(reed_sensor_driver_params)

/**
 * @brief   Allocate memory for the device descriptors
 */
static reed_sensor_driver_t rsd_devs[RSD_NUM];

/**
 * @brief   Memory for the SAUL registry entries
 */
static saul_reg_t saul_entries[RSD_NUM * 2];

/**
 * @brief   Define the number of saul info
 */
#define RSD_INFO_NUM ARRAY_SIZE(reed_sensor_driver_saul_info)

/**
 * @name    Import SAUL endpoints
 * @{
 */
extern saul_driver_t reed_sensor_nc_saul_driver;
extern saul_driver_t reed_sensor_no_saul_driver;

/** @} */


#define ENABLE_DEBUG 1
#include "debug.h"

void auto_init_reed_sensor_driver(void)
{

    for (unsigned int i = 0; i < RSD_NUM; i++) {
        LOG_DEBUG("[auto_init_saul] initializing rsd #%u\n", i);

        if (reed_sensor_driver_init(&rsd_devs[i], &reed_sensor_driver_params[i]) != 0) {
            LOG_ERROR("[auto_init_saul] error initializing rsd #%u\n", i);
            continue;
        }
        LOG_DEBUG("SUCCESS\n");
        saul_entries[(i * 2)].dev = &(rsd_devs[i]);
        saul_entries[(i * 2)].name = reed_sensor_driver_saul_info[i].name;
        saul_entries[(i * 2)].driver = &reed_sensor_nc_saul_driver;
        saul_reg_add(&(saul_entries[(i * 2)]));

        saul_entries[(i * 2) + 1].dev = &(rsd_devs[i]);
        saul_entries[(i * 2) + 1].name = reed_sensor_driver_saul_info[i+1].name;
        saul_entries[(i * 2) + 1].driver = &reed_sensor_no_saul_driver;
        saul_reg_add(&(saul_entries[(i * 2) + 1]));
    }
}