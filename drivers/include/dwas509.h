/*
 * Copyright (C) 2025 HAW
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#pragma once

/**
 * @defgroup    drivers_dwas509 dwas509
 * @ingroup     drivers_sensors
 * @brief       Driver for the inductive distance sensor dwas509 by Contrinex
 *
 * @{
 *
 * @file
 *
 * @author      Jan Thies <jan.thies@haw-hamburg.de>
 */

/* Add header includes here */

#ifdef __cplusplus
extern "C" {
#endif

/* Declare the API of the driver */

/**
 * @brief   Device initialization parameters
 */
typedef struct {
    /* add initialization params here */
} dwas509_params_t;

/**
 * @brief   Device descriptor for the driver
 */
typedef struct {
    /** Device initialization parameters */
    dwas509_params_t params;
} dwas509_t;

/**
 * @brief   Initialize the given device
 *
 * @param[inout] dev        Device descriptor of the driver
 * @param[in]    params     Initialization parameters
 *
 * @return                  0 on success
 */
int dwas509_init(dwas509_t *dev, const dwas509_params_t *params);

#ifdef __cplusplus
}
#endif

/** @} */
