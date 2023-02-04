/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_tea5767_basic.h
 * @brief     driver tea5767 basic include file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2022-11-15
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2022/11/15  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_TEA5767_BASIC_H
#define DRIVER_TEA5767_BASIC_H

#include "driver_tea5767_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup tea5767_example_driver tea5767 example driver function
 * @brief    tea5767 example driver modules
 * @ingroup  tea5767_driver
 * @{
 */

/**
 * @brief tea5767 basic example default definition
 */
#define TEA57671_BASIC_DEFAULT_MUTE                             TEA5767_BOOL_FALSE                   /**< disable mute */
#define TEA57671_BASIC_DEFAULT_MODE                             TEA5767_MODE_NORMAL                  /**< normal mode */
#define TEA57671_BASIC_DEFAULT_MHZ                              88.0f                                /**< 88.0MHz */
#define TEA57671_BASIC_DEFAULT_SEARCH_MODE                      TEA5767_SEARCH_MODE_UP               /**< search mode up */
#define TEA57671_BASIC_DEFAULT_SEARCH_STOP_LEVEL                TEA5767_SEARCH_STOP_LEVEL_MID        /**< search stop level mid */
#define TEA57671_BASIC_DEFAULT_SIDE_INJECTION                   TEA5767_SIDE_INJECTION_HIGH          /**< side injection high */
#define TEA57671_BASIC_DEFAULT_CHANNEL                          TEA5767_CHANNEL_STEREO               /**< stereo */
#define TEA57671_BASIC_DEFAULT_RIGHT_MUTE                       TEA5767_BOOL_FALSE                   /**< disable right mute */
#define TEA57671_BASIC_DEFAULT_LEFT_MUTE                        TEA5767_BOOL_FALSE                   /**< disable left mute */
#define TEA57671_BASIC_DEFAULT_PORT1                            TEA5767_LEVEL_LOW                    /**< port1 low */
#define TEA57671_BASIC_DEFAULT_PORT2                            TEA5767_LEVEL_LOW                    /**< port2 low */
#define TEA57671_BASIC_DEFAULT_BAND                             TEA5767_BAND_JAPANESE                /**< Japanese band */
#define TEA57671_BASIC_DEFAULT_SOFT_MUTE                        TEA5767_BOOL_FALSE                   /**< disable soft mute */
#define TEA57671_BASIC_DEFAULT_HIGH_CUT_CONTROL                 TEA5767_BOOL_TRUE                    /**< enable high cut control */
#define TEA57671_BASIC_DEFAULT_STEREO_NOISE_CANCELING           TEA5767_BOOL_TRUE                    /**< enable stereo noise cancelling */
#define TEA57671_BASIC_DEFAULT_PORT1_AS_SEARCH_INDICATOR        TEA5767_BOOL_TRUE                    /**< enable port1 as search indicator */
#define TEA57671_BASIC_DEFAULT_DE_EMPHASIS                      TEA5767_DE_EMPHASIS_50US             /**< 50us */
#define TEA57671_BASIC_DEFAULT_CLOCK                            TEA5767_CLOCK_32P768_KHZ             /**< 32.768KHz */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t tea5767_basic_init(void);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t tea5767_basic_deinit(void);

/**
 * @brief  basic example search up
 * @return status code
 *         - 0 success
 *         - 1 search up failed
 *         - 2 reach band limit
 * @note   none
 */
uint8_t tea5767_basic_search_up(void);

/**
 * @brief  basic example search down
 * @return status code
 *         - 0 success
 *         - 1 search down failed
 *         - 2 reach band limit
 * @note   none
 */
uint8_t tea5767_basic_search_down(void);

/**
 * @brief     basic example set frequency
 * @param[in] mhz is the set frequency
 * @return    status code
 *            - 0 success
 *            - 1 set frequency failed
 * @note      none
 */
uint8_t tea5767_basic_set_frequency(float mhz);

/**
 * @brief      basic example get frequency
 * @param[out] *mhz points to a frequency buffer
 * @return     status code
 *             - 0 success
 *             - 1 get frequency failed
 * @note       none
 */
uint8_t tea5767_basic_get_frequency(float *mhz);

/**
 * @brief     basic example enable or disable mute
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set mute failed
 * @note      none
 */
uint8_t tea5767_basic_set_mute(tea5767_bool_t enable);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
