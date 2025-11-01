/*
 * Copyright (C) 2025 HAW
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     drivers_dwas509
 * @{
 *
 * @file
 * @brief       Device driver implementation for the dwas509
 *
 * @author      Jan Thies <jan.thies@haw-hamburg.de>
 *
 * @}
 */

#include <assert.h>
#include <errno.h>
#include <stdint.h>

#include "dwas509.h"
#include "dwas509_constants.h"

/* Fixed-point shift (Q16.16 format) */
#define FP_SHIFT 16
#define FP_ONE   (1 << FP_SHIFT)
#define TO_FP(x) ((int32_t)((x) * FP_ONE))

/* Default polynomial coefficients: f(U) = b3*U³ + b2*U² + b1*U + b0 */
static const int32_t B0 = TO_FP(-0.9188);
static const int32_t B1 = TO_FP(1.8001);
static const int32_t B2 = TO_FP(-0.2552);
static const int32_t B3 = TO_FP(0.0165);

static int _adc_resolution(adc_res_t res)
{
    switch (res) {
    case ADC_RES_6BIT:
        return (1 << 6);
    case ADC_RES_8BIT:
        return (1 << 8);
    case ADC_RES_10BIT:
        return (1 << 10);
    case ADC_RES_12BIT:
        return (1 << 12);
    case ADC_RES_14BIT:
        return (1 << 14);
    case ADC_RES_16BIT:
        return (1 << 16);
    default:
        return -EINVAL;
    }
}

static int32_t _voltage_fp(int32_t adc_val, int32_t adc_max)
{
    /* ADC value to voltage after divider (0-3.3V) */
    int32_t vref_fp = TO_FP(DWAS509_VREF);
    int32_t voltage_after_divider_fp = (int32_t)(((int64_t)adc_val * vref_fp) / (adc_max - 1));

    /* Scale back to original sensor voltage (0.4-11.4V) */
    int32_t divider_ratio_fp = TO_FP(DWAS509_VOLTAGE_DIVIDER_RATIO);
    int32_t sensor_voltage_fp =
        (int32_t)(((int64_t)voltage_after_divider_fp * divider_ratio_fp) >> FP_SHIFT);

    return sensor_voltage_fp;
}

int32_t dwas509_default_response_curve(int32_t v_fp)
{
    int64_t v = v_fp;
    int64_t v2 = (v * v) >> FP_SHIFT;
    int64_t v3 = (v2 * v) >> FP_SHIFT;

    int64_t dist_fp =
        ((B3 * v3) >> FP_SHIFT) + ((B2 * v2) >> FP_SHIFT) + ((B1 * v) >> FP_SHIFT) + B0;

    int32_t dist_um = (int32_t)((dist_fp * 1000) >> FP_SHIFT);

    if (dist_um < 0) {
        return 0;
    }
    if (dist_um > 10000) {
        return 10000;
    }

    return dist_um;
}

int dwas509_init(dwas509_t *dev, const dwas509_params_t *params)
{
    assert(dev);
    assert(params);

    if (_adc_resolution(params->resolution) < 0) {
        return -EINVAL;
    }

    if (adc_init(params->adc_line) < 0) {
        return -ENXIO;
    }

    dev->params = *params;

    /* Use default response curve if none provided */
    if (dev->params.response_curve == NULL) {
        dev->params.response_curve = dwas509_default_response_curve;
    }

    return 0;
}

int dwas509_read_um(const dwas509_t *dev)
{
    assert(dev);

    int32_t adc_val = adc_sample(dev->params.adc_line, dev->params.resolution);
    if (adc_val < 0) {
        return -EIO;
    }

    int32_t adc_max = _adc_resolution(dev->params.resolution);
    int32_t v_fp = _voltage_fp(adc_val, adc_max);

    /* Call the response curve function */
    return dev->params.response_curve(v_fp);
}

int dwas509_read_mm(const dwas509_t *dev)
{
    assert(dev);

    int32_t um = dwas509_read_um(dev);
    if (um < 0) {
        return um;
    }

    return um / 1000;
}
