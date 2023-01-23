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
 * @file      driver_tea5767.h
 * @brief     driver tea5767 header file
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

#ifndef DRIVER_TEA5767_H
#define DRIVER_TEA5767_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup tea5767_driver tea5767 driver function
 * @brief    tea5767 driver modules
 * @{
 */

/**
 * @addtogroup tea5767_base_driver
 * @{
 */

/**
 * @brief tea5767 bool enumeration definition
 */
typedef enum
{
    TEA5767_BOOL_FALSE = 0x00,        /**< disable */
    TEA5767_BOOL_TRUE  = 0x01,        /**< enable */
} tea5767_bool_t;

/**
 * @brief tea5767 level enumeration definition
 */
typedef enum
{
    TEA5767_LEVEL_LOW  = 0x00,        /**< low */
    TEA5767_LEVEL_HIGH = 0x01,        /**< high */
} tea5767_level_t;

/**
 * @brief tea5767 mode enumeration definition
 */
typedef enum
{
    TEA5767_MODE_NORMAL = 0x00,        /**< normal mode */
    TEA5767_MODE_SEARCH = 0x01,        /**< search mode */
} tea5767_mode_t;

/**
 * @brief tea5767 search mode enumeration definition
 */
typedef enum
{
    TEA5767_SEARCH_MODE_DOWN = 0x00,        /**< search down */
    TEA5767_SEARCH_MODE_UP   = 0x01,        /**< search up */
} tea5767_search_mode_t;

/**
 * @brief tea5767 side injection enumeration definition
 */
typedef enum
{
    TEA5767_SIDE_INJECTION_LOW  = 0x00,        /**< low side lo injection */
    TEA5767_SIDE_INJECTION_HIGH = 0x01,        /**< high side lo injection */
} tea5767_side_injection_t;

/**
 * @brief tea5767 channel enumeration definition
 */
typedef enum
{
    TEA5767_CHANNEL_STEREO = 0x00,        /**< stereo */
    TEA5767_CHANNEL_MONO   = 0x01,        /**< mono */
} tea5767_channel_t;

/**
 * @brief tea5767 search stop level enumeration definition
 */
typedef enum
{
    TEA5767_SEARCH_STOP_LEVEL_LOW  = 0x01,        /**< level adc output = 5 */
    TEA5767_SEARCH_STOP_LEVEL_MID  = 0x02,        /**< level adc output = 7 */
    TEA5767_SEARCH_STOP_LEVEL_HIGH = 0x03,        /**< level adc output = 10 */
} tea5767_search_stop_level_t;

/**
 * @brief tea5767 band enumeration definition
 */
typedef enum
{
    TEA5767_BAND_US_EUROPE = 0x00,        /**< US/Europe fm band */
    TEA5767_BAND_JAPANESE  = 0x01,        /**< Japanese fm band */
} tea5767_band_t;

/**
 * @brief tea5767 de-emphasis enumeration definition
 */
typedef enum
{
    TEA5767_DE_EMPHASIS_50US = 0x00,        /**< 50us */
    TEA5767_DE_EMPHASIS_75US = 0x01,        /**< 75us */
} tea5767_de_emphasis_t;

/**
 * @brief tea5767 clock enumeration definition
 */
typedef enum
{
    TEA5767_CLOCK_13_MHZ     = 0x00,        /**< 13MHz */
    TEA5767_CLOCK_32P768_KHZ = 0x01,        /**< 32.768KHz */
    TEA5767_CLOCK_6P5_MHZ    = 0x02,        /**< 6.5MHz */
} tea5767_clock_t;

/**
 * @brief tea5767 reception enumeration definition
 */
typedef enum
{
    TEA5767_RECEPTION_MONO   = 0x00,        /**< mono */
    TEA5767_RECEPTION_STEREO = 0x01,        /**< stereo */
} tea5767_reception_t;

/**
 * @brief tea5767 handle structure definition
 */
typedef struct tea5767_handle_s
{
    uint8_t (*iic_init)(void);                                                 /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                               /**< point to an iic_deinit function address */
    uint8_t (*iic_read_cmd)(uint8_t addr, uint8_t *buf, uint16_t len);         /**< point to an iic_read_cmd function address */
    uint8_t (*iic_write_cmd)(uint8_t addr, uint8_t *buf, uint16_t len);        /**< point to an iic_write_cmd function address */
    void (*delay_ms)(uint32_t ms);                                             /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                           /**< point to a debug_print function address */
    uint8_t inited;                                                            /**< inited flag */
    uint8_t conf_up[5];                                                        /**< chip conf up */
    uint8_t conf_down[5];                                                      /**< chip conf down */
} tea5767_handle_t;

/**
 * @brief tea5767 information structure definition
 */
typedef struct tea5767_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} tea5767_info_t;

/**
 * @}
 */

/**
 * @defgroup tea5767_link_driver tea5767 link driver function
 * @brief    tea5767 link driver modules
 * @ingroup  tea5767_driver
 * @{
 */

/**
 * @brief     initialize tea5767_handle_t structure
 * @param[in] HANDLE points to a tea5767 handle structure
 * @param[in] STRUCTURE is tea5767_handle_t
 * @note      none
 */
#define DRIVER_TEA5767_LINK_INIT(HANDLE, STRUCTURE)          memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE points to a tea5767 handle structure
 * @param[in] FUC points to an iic_init function address
 * @note      none
 */
#define DRIVER_TEA5767_LINK_IIC_INIT(HANDLE, FUC)            (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE points to a tea5767 handle structure
 * @param[in] FUC points to an iic_deinit function address
 * @note      none
 */
#define DRIVER_TEA5767_LINK_IIC_DEINIT(HANDLE, FUC)          (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read_cmd function
 * @param[in] HANDLE points to a tea5767 handle structure
 * @param[in] FUC points to an iic_read_cmd function address
 * @note      none
 */
#define DRIVER_TEA5767_LINK_IIC_READ_COMMAND(HANDLE, FUC)    (HANDLE)->iic_read_cmd = FUC

/**
 * @brief     link iic_write_cmd function
 * @param[in] HANDLE points to a tea5767 handle structure
 * @param[in] FUC points to an iic_write_cmd function address
 * @note      none
 */
#define DRIVER_TEA5767_LINK_IIC_WRITE_COMMAND(HANDLE, FUC)   (HANDLE)->iic_write_cmd = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to a tea5767 handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_TEA5767_LINK_DELAY_MS(HANDLE, FUC)            (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to a tea5767 handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_TEA5767_LINK_DEBUG_PRINT(HANDLE, FUC)         (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup tea5767_base_driver tea5767 base driver function
 * @brief    tea5767 base driver modules
 * @ingroup  tea5767_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to a tea5767 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t tea5767_info(tea5767_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to a tea5767 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t tea5767_init(tea5767_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to a tea5767 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 power down failed
 * @note      none
 */
uint8_t tea5767_deinit(tea5767_handle_t *handle);

/**
 * @brief     write the conf
 * @param[in] *handle points to a tea5767 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 write conf failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tea5767_write_conf(tea5767_handle_t *handle);

/**
 * @brief     update the conf
 * @param[in] *handle points to a tea5767 handle structure
 * @param[in] *conf points to a conf buffer
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tea5767_update_conf(tea5767_handle_t *handle, uint8_t conf[5]);

/**
 * @brief     read the conf
 * @param[in] *handle points to a tea5767 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 read conf failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tea5767_read_conf(tea5767_handle_t *handle);

/**
 * @brief     enable or disable the mute
 * @param[in] *handle points to a tea5767 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      update config by tea5767_write_conf
 */
uint8_t tea5767_set_mute(tea5767_handle_t *handle, tea5767_bool_t enable);

/**
 * @brief      get the mute status
 * @param[in]  *handle points to a tea5767 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       get config in local
 */
uint8_t tea5767_get_mute(tea5767_handle_t *handle, tea5767_bool_t *enable);

/**
 * @brief     set the chip mode
 * @param[in] *handle points to a tea5767 handle structure
 * @param[in] mode is the set mode
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      update config by tea5767_write_conf
 */
uint8_t tea5767_set_mode(tea5767_handle_t *handle, tea5767_mode_t mode);

/**
 * @brief      get the chip mode
 * @param[in]  *handle points to a tea5767 handle structure
 * @param[out] *mode points to a mode buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       get config in local
 */
uint8_t tea5767_get_mode(tea5767_handle_t *handle, tea5767_mode_t *mode);

/**
 * @brief     set the pll
 * @param[in] *handle points to a tea5767 handle structure
 * @param[in] pll is the set pll
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 pll > 0x3FFF
 * @note      update config by tea5767_write_conf
 *            pll <= 0x3FFF
 */
uint8_t tea5767_set_pll(tea5767_handle_t *handle, uint16_t pll);

/**
 * @brief      get the pll
 * @param[in]  *handle points to a tea5767 handle structure
 * @param[out] *pll points to a pll buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       get config in local
 */
uint8_t tea5767_get_pll(tea5767_handle_t *handle, uint16_t *pll);

/**
 * @brief     set the search mode
 * @param[in] *handle points to a tea5767 handle structure
 * @param[in] mode is the search mode
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      update config by tea5767_write_conf
 */
uint8_t tea5767_set_search_mode(tea5767_handle_t *handle, tea5767_search_mode_t mode);

/**
 * @brief      get the search mode
 * @param[in]  *handle points to a tea5767 handle structure
 * @param[out] *mode points to a mode buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       get config in local
 */
uint8_t tea5767_get_search_mode(tea5767_handle_t *handle, tea5767_search_mode_t *mode);

/**
 * @brief     set the search stop level
 * @param[in] *handle points to a tea5767 handle structure
 * @param[in] level is the search stop level
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      update config by tea5767_write_conf
 */
uint8_t tea5767_set_search_stop_level(tea5767_handle_t *handle, tea5767_search_stop_level_t level);

/**
 * @brief      get the search stop level
 * @param[in]  *handle points to a tea5767 handle structure
 * @param[out] *level points to a search stop level buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       get config in local
 */
uint8_t tea5767_get_search_stop_level(tea5767_handle_t *handle, tea5767_search_stop_level_t *level);

/**
 * @brief     set the side injection
 * @param[in] *handle points to a tea5767 handle structure
 * @param[in] side is the injection side
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      update config by tea5767_write_conf
 */
uint8_t tea5767_set_side_injection(tea5767_handle_t *handle, tea5767_side_injection_t side);

/**
 * @brief      get the side injection
 * @param[in]  *handle points to a tea5767 handle structure
 * @param[out] *side points to an injection side buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       get config in local
 */
uint8_t tea5767_get_side_injection(tea5767_handle_t *handle, tea5767_side_injection_t *side);

/**
 * @brief     set the sound channel
 * @param[in] *handle points to a tea5767 handle structure
 * @param[in] channel is the sound channel
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      update config by tea5767_write_conf
 */
uint8_t tea5767_set_channel(tea5767_handle_t *handle, tea5767_channel_t channel);

/**
 * @brief      get the sound channel
 * @param[in]  *handle points to a tea5767 handle structure
 * @param[out] *channel points to a sound channel buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       get config in local
 */
uint8_t tea5767_get_channel(tea5767_handle_t *handle, tea5767_channel_t *channel);

/**
 * @brief     enable or disable right mute
 * @param[in] *handle points to a tea5767 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      update config by tea5767_write_conf
 */
uint8_t tea5767_set_right_mute(tea5767_handle_t *handle, tea5767_bool_t enable);

/**
 * @brief      get the right mute status
 * @param[in]  *handle points to a tea5767 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       get config in local
 */
uint8_t tea5767_get_right_mute(tea5767_handle_t *handle, tea5767_bool_t *enable);

/**
 * @brief     enable or disable left mute
 * @param[in] *handle points to a tea5767 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      update config by tea5767_write_conf
 */
uint8_t tea5767_set_left_mute(tea5767_handle_t *handle, tea5767_bool_t enable);

/**
 * @brief      get the left mute status
 * @param[in]  *handle points to a tea5767 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       get config in local
 */
uint8_t tea5767_get_left_mute(tea5767_handle_t *handle, tea5767_bool_t *enable);

/**
 * @brief     set the port1 level
 * @param[in] *handle points to a tea5767 handle structure
 * @param[in] level is the set level
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      update config by tea5767_write_conf
 */
uint8_t tea5767_set_port1(tea5767_handle_t *handle, tea5767_level_t level);

/**
 * @brief      get the port1 level
 * @param[in]  *handle points to a tea5767 handle structure
 * @param[out] *level points to a level buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       get config in local
 */
uint8_t tea5767_get_port1(tea5767_handle_t *handle, tea5767_level_t *level);

/**
 * @brief     set the port2 level
 * @param[in] *handle points to a tea5767 handle structure
 * @param[in] level is the set level
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      update config by tea5767_write_conf
 */
uint8_t tea5767_set_port2(tea5767_handle_t *handle, tea5767_level_t level);

/**
 * @brief      get the port2 level
 * @param[in]  *handle points to a tea5767 handle structure
 * @param[out] *level points to a level buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       get config in local
 */
uint8_t tea5767_get_port2(tea5767_handle_t *handle, tea5767_level_t *level);

/**
 * @brief     enable or disable standby
 * @param[in] *handle points to a tea5767 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      update config by tea5767_write_conf
 */
uint8_t tea5767_set_standby(tea5767_handle_t *handle, tea5767_bool_t enable);

/**
 * @brief      get the standby status
 * @param[in]  *handle points to a tea5767 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       get config in local
 */
uint8_t tea5767_get_standby(tea5767_handle_t *handle, tea5767_bool_t *enable);

/**
 * @brief     set the band
 * @param[in] *handle points to a tea5767 handle structure
 * @param[in] band is the set band
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      update config by tea5767_write_conf
 */
uint8_t tea5767_set_band(tea5767_handle_t *handle, tea5767_band_t band);

/**
 * @brief      get the band
 * @param[in]  *handle points to a tea5767 handle structure
 * @param[out] *band points to a band buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       get config in local
 */
uint8_t tea5767_get_band(tea5767_handle_t *handle, tea5767_band_t *band);

/**
 * @brief     enable or disable soft mute
 * @param[in] *handle points to a tea5767 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      update config by tea5767_write_conf
 */
uint8_t tea5767_set_soft_mute(tea5767_handle_t *handle, tea5767_bool_t enable);

/**
 * @brief      get the soft mute status
 * @param[in]  *handle points to a tea5767 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       get config in local
 */
uint8_t tea5767_get_soft_mute(tea5767_handle_t *handle, tea5767_bool_t *enable);

/**
 * @brief     enable or disable high cut control
 * @param[in] *handle points to a tea5767 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      update config by tea5767_write_conf
 */
uint8_t tea5767_set_high_cut_control(tea5767_handle_t *handle, tea5767_bool_t enable);

/**
 * @brief      get the high cut control status
 * @param[in]  *handle points to a tea5767 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       get config in local
 */
uint8_t tea5767_get_high_cut_control(tea5767_handle_t *handle, tea5767_bool_t *enable);

/**
 * @brief     enable or disable stereo noise cancelling
 * @param[in] *handle points to a tea5767 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      update config by tea5767_write_conf
 */
uint8_t tea5767_set_stereo_noise_cancelling(tea5767_handle_t *handle, tea5767_bool_t enable);

/**
 * @brief      get the stereo noise cancelling status
 * @param[in]  *handle points to a tea5767 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       get config in local
 */
uint8_t tea5767_get_stereo_noise_cancelling(tea5767_handle_t *handle, tea5767_bool_t *enable);

/**
 * @brief     enable or disable port1 as search indicator
 * @param[in] *handle points to a tea5767 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      update config by tea5767_write_conf
 */
uint8_t tea5767_set_port1_as_search_indicator(tea5767_handle_t *handle, tea5767_bool_t enable);

/**
 * @brief      get the port1 as search indicator status
 * @param[in]  *handle points to a tea5767 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       get config in local
 */
uint8_t tea5767_get_port1_as_search_indicator(tea5767_handle_t *handle, tea5767_bool_t *enable);

/**
 * @brief     set the de emphasis
 * @param[in] *handle points to a tea5767 handle structure
 * @param[in] emphasis is the set emphasis
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      update config by tea5767_write_conf
 */
uint8_t tea5767_set_de_emphasis(tea5767_handle_t *handle, tea5767_de_emphasis_t emphasis);

/**
 * @brief      get the de emphasis status
 * @param[in]  *handle points to a tea5767 handle structure
 * @param[out] *emphasis points to an emphasis buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       get config in local
 */
uint8_t tea5767_get_de_emphasis(tea5767_handle_t *handle, tea5767_de_emphasis_t *emphasis);

/**
 * @brief     set the clock
 * @param[in] *handle points to a tea5767 handle structure
 * @param[in] clk is the set clock
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      update config by tea5767_write_conf
 */
uint8_t tea5767_set_clock(tea5767_handle_t *handle, tea5767_clock_t clk);

/**
 * @brief      get the clock
 * @param[in]  *handle points to a tea5767 handle structure
 * @param[out] *clk points to a clock buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       get config in local
 */
uint8_t tea5767_get_clock(tea5767_handle_t *handle, tea5767_clock_t *clk);

/**
 * @brief      get the ready flag
 * @param[in]  *handle points to a tea5767 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       update config by tea5767_read_conf
 */
uint8_t tea5767_get_ready_flag(tea5767_handle_t *handle, tea5767_bool_t *enable);

/**
 * @brief      get the band limit flag
 * @param[in]  *handle points to a tea5767 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       update config by tea5767_read_conf
 */
uint8_t tea5767_get_band_limit_flag(tea5767_handle_t *handle, tea5767_bool_t *enable);

/**
 * @brief      get the searched pll
 * @param[in]  *handle points to a tea5767 handle structure
 * @param[out] *pll points to a pll buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       update config by tea5767_read_conf
 */
uint8_t tea5767_get_searched_pll(tea5767_handle_t *handle, uint16_t *pll);

/**
 * @brief      get the if
 * @param[in]  *handle points to a tea5767 handle structure
 * @param[out] *if_out points to an if out buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       update config by tea5767_read_conf
 */
uint8_t tea5767_get_if(tea5767_handle_t *handle, uint8_t *if_out);

/**
 * @brief      get the reception
 * @param[in]  *handle points to a tea5767 handle structure
 * @param[out] *reception points to a reception buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       update config by tea5767_read_conf
 */
uint8_t tea5767_get_reception(tea5767_handle_t *handle, tea5767_reception_t *reception);

/**
 * @brief      get the level adc output
 * @param[in]  *handle points to a tea5767 handle structure
 * @param[out] *output points to an output buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       update config by tea5767_read_conf
 */
uint8_t tea5767_get_level_adc_output(tea5767_handle_t *handle, uint8_t *output);

/**
 * @brief      convert the frequency to the register raw data
 * @param[in]  *handle points to a tea5767 handle structure
 * @param[in]  mhz is the radio frequency in MHz
 * @param[out] *pll points to a pll buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 clock is invalid
 * @note       none
 */
uint8_t tea5767_frequency_convert_to_register(tea5767_handle_t *handle, float mhz, uint16_t *pll);

/**
 * @brief      convert the register raw data to the frequency
 * @param[in]  *handle points to a tea5767 handle structure
 * @param[in]  pll is the register raw data
 * @param[out] *mhz points to a frequency buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 clock is invalid
 * @note       none
 */
uint8_t tea5767_frequency_convert_to_data(tea5767_handle_t *handle, uint16_t pll, float *mhz);

/**
 * @}
 */

/**
 * @defgroup tea5767_extern_driver tea5767 extern driver function
 * @brief    tea5767 extern driver modules
 * @ingroup  tea5767_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle points to a tea5767 handle structure
 * @param[in] *buf points to a data buffer.
 * @param[in] len is the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tea5767_set_reg(tea5767_handle_t *handle, uint8_t *buf, uint16_t len);

/**
 * @brief      get the chip register
 * @param[in]  *handle points to a tea5767 handle structure
 * @param[out] *buf points to a data buffer.
 * @param[in]  len is the data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t tea5767_get_reg(tea5767_handle_t *handle, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
