/*
 * Copyright (C) 2025 HAW
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#pragma once

/**
  * @defgroup    drivers_dwas509 DWAS509
  * @ingroup     drivers_sensors
  * @brief       Driver for the inductive distance sensor dwas509 by Contrinex
  *
  * This driver supports the DWAS509 analog distance sensor with a 
  * measurement range of 0-10mm. Distance calculation uses a 3rd degree
  * polynomial regression (R² = 0.999) with fixed-point arithmetic.
  *
  * The response curve can be customized via callback function to support
  * different target materials.
  *
  * @{
  *
  * @file
  *
  * @author      Jan Thies <jan.thies@haw-hamburg.de>
  */

#include "periph/adc.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief   Response curve callback function
  *
  * Converts voltage (in fixed-point Q16.16 format) to distance in micrometers.
  *
  * @param[in]   voltage_fp      Voltage in fixed-point format (Q16.16)
  *
  * @return      Distance in micrometers (0-10000)
  */
typedef int32_t (*dwas509_response_curve_t)(int32_t voltage_fp);

/**
  * @brief   Device initialization parameters
  */
typedef struct {
    adc_t adc_line;                          /**< ADC line connected to sensor */
    adc_res_t resolution;                    /**< ADC resolution */
    dwas509_response_curve_t response_curve; /**< Response curve callback (NULL = default) */
} dwas509_params_t;

/**
  * @brief   Device descriptor for the driver
  */
typedef struct {
    dwas509_params_t params; /**< Device initialization parameters */
} dwas509_t;

/**
  * @brief   Default response curve for standard target material
  *
  * Uses 3rd degree polynomial regression with coefficients:
  * b0 = -0.9188, b1 = 1.8001, b2 = -0.2552, b3 = 0.0165
  *
  * @param[in]   voltage_fp      Voltage in fixed-point format (Q16.16)
  *
  * @return      Distance in micrometers
  */
int32_t dwas509_default_response_curve(int32_t voltage_fp);

/**
  * @brief   Initialize the given device
  *
  * @param[inout] dev        Device descriptor of the driver
  * @param[in]    params     Initialization parameters
  *
  * @retval      0           Success
  * @retval      -EINVAL     Invalid ADC resolution
  * @retval      -ENXIO      ADC initialization failed
  */
int dwas509_init(dwas509_t *dev, const dwas509_params_t *params);

/**
  * @brief   Read distance in micrometers
  *
  * @param[in]   dev         Device descriptor
  *
  * @return      Distance in micrometers (0-10000)
  * @retval      -EIO        ADC sampling failed
  */
int dwas509_read_um(const dwas509_t *dev);

/**
 * @brief   Read distance in micrometers with median filtering
 *
 * Takes multiple samples and returns the median value to reduce noise
 * and reject outliers.
 *
 * @param[in]   dev         Device descriptor
 * @param[in]   samples     Number of samples to take (must be > 0)
 * @param[in]   delay_us    Delay between samples in microseconds
 *
 * @return      Median distance in micrometers (0-10000)
 * @retval      -EINVAL     Invalid number of samples
 * @retval      -EIO        ADC sampling failed
 */
int dwas509_read_um_median(const dwas509_t *dev, uint8_t samples, uint32_t delay_us);

/**
  * @brief   Read distance in millimeters
  *
  * @param[in]   dev         Device descriptor
  *
  * @return      Distance in millimeters (0-10)
  * @retval      -EIO        ADC sampling failed
  */
int dwas509_read_mm(const dwas509_t *dev);

#ifdef __cplusplus
}
#endif

/** @} */
