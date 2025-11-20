/*
 * Copyright (C) 2025 HAW
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#pragma once

/**
  * @ingroup     drivers_dwas509
  *
  * @{
  * @file
  * @brief       Default configuration
  *
  * @author      Jan Thies <jan.thies@haw-hamburg.de>
  */

#include "board.h"
#include "dwas509.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @name    Set default configuration parameters
  * @{
  */
#ifndef DWAS509_PARAM_ADC
#  define DWAS509_PARAM_ADC (ADC_LINE(0))
#endif

#ifndef DWAS509_PARAM_RES
#  define DWAS509_PARAM_RES (ADC_RES_12BIT)
#endif

#ifndef DWAS509_PARAM_CURVE
#  define DWAS509_PARAM_CURVE (NULL) /* Use default curve */
#endif

#ifndef DWAS509_PARAMS
#  define DWAS509_PARAMS                 \
      { .adc_line = DWAS509_PARAM_ADC,   \
        .resolution = DWAS509_PARAM_RES, \
        .response_curve = DWAS509_PARAM_CURVE }
#endif
/**@}*/

/**
  * @brief   Configuration struct
  */
static const dwas509_params_t dwas509_params[] = { DWAS509_PARAMS };

#ifdef __cplusplus
}
#endif

/** @} */
