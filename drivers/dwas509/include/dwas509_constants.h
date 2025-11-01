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
  * @{
  *
  * @file
  * @brief       Internal addresses, registers and constants
  *
  * @author      Jan Thies <jan.thies@haw-hamburg.de>
  */

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief   Reference voltage of the ADC (in Volts)
  * 
  * This is the voltage range of the ADC input, typically 3.3V for most
  * microcontrollers. Adjust if your board uses a different reference voltage.
  */
#ifndef DWAS509_VREF
#  define DWAS509_VREF (3.3f)
#endif

/**
  * @brief   Voltage divider ratio (Vsensor / Vadc)
  * 
  * The DWAS509 sensor outputs 0.4-11.4V, which must be scaled down to the
  * ADC input range (0-3.3V) via a voltage divider.
  * 
  * Ratio = (R1 + R2) / R2, where:
  * - R1 is the resistor to ground
  * - R2 is the resistor to the sensor output
  * 
  * Example: R1=8.2kΩ, R2=3.3kΩ → Ratio = 11.5/3.3 = 3.48
  * 
  * Adjust this value according to your actual voltage divider circuit.
  */
#ifndef DWAS509_VOLTAGE_DIVIDER_RATIO
#  define DWAS509_VOLTAGE_DIVIDER_RATIO (3.45f)
#endif

/**
  * @brief   Maximum measurable distance in millimeters
  */
#define DWAS509_MAX_DISTANCE_MM (10)

/**
  * @brief   Maximum measurable distance in micrometers
  */
#define DWAS509_MAX_DISTANCE_UM (10000)

#ifdef __cplusplus
}
#endif

/** @} */
