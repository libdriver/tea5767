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
 * @file      driver_tea5767_register_test.c
 * @brief     driver tea5767 register test source file
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

#include "driver_tea5767_register_test.h"
#include <stdlib.h>

static tea5767_handle_t gs_handle;        /**< tea5767 handle */

/**
 * @brief  register test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t tea5767_register_test(void)
{
    uint8_t res;
    uint8_t output;
    uint16_t pll;
    uint16_t pll_check;
    float mhz;
    float mhz_check;
    tea5767_info_t info;
    tea5767_bool_t enable;
    tea5767_mode_t mode;
    tea5767_search_mode_t search_mode;
    tea5767_search_stop_level_t stop_level;
    tea5767_side_injection_t side;
    tea5767_channel_t channel;
    tea5767_level_t level;
    tea5767_band_t band;
    tea5767_de_emphasis_t emphasis;
    tea5767_clock_t clk;
    tea5767_reception_t reception;
    
    /* link functions */
    DRIVER_TEA5767_LINK_INIT(&gs_handle, tea5767_handle_t);
    DRIVER_TEA5767_LINK_IIC_INIT(&gs_handle, tea5767_interface_iic_init);
    DRIVER_TEA5767_LINK_IIC_DEINIT(&gs_handle, tea5767_interface_iic_deinit);
    DRIVER_TEA5767_LINK_IIC_READ_COMMAND(&gs_handle, tea5767_interface_iic_read_cmd);
    DRIVER_TEA5767_LINK_IIC_WRITE_COMMAND(&gs_handle, tea5767_interface_iic_write_cmd);
    DRIVER_TEA5767_LINK_DELAY_MS(&gs_handle, tea5767_interface_delay_ms);
    DRIVER_TEA5767_LINK_DEBUG_PRINT(&gs_handle, tea5767_interface_debug_print);
    
    /* tea5767 info */
    res = tea5767_info(&info);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip information */
        tea5767_interface_debug_print("tea5767: chip is %s.\n", info.chip_name);
        tea5767_interface_debug_print("tea5767: manufacturer is %s.\n", info.manufacturer_name);
        tea5767_interface_debug_print("tea5767: interface is %s.\n", info.interface);
        tea5767_interface_debug_print("tea5767: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        tea5767_interface_debug_print("tea5767: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        tea5767_interface_debug_print("tea5767: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        tea5767_interface_debug_print("tea5767: max current is %0.2fmA.\n", info.max_current_ma);
        tea5767_interface_debug_print("tea5767: max temperature is %0.1fC.\n", info.temperature_max);
        tea5767_interface_debug_print("tea5767: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start register test */
    tea5767_interface_debug_print("tea5767: start register test.\n");
    
    /* tea5767 init */
    res = tea5767_init(&gs_handle);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: init failed.\n");
       
        return 1;
    }
    
    /* tea5767_set_mute/tea5767_get_mute test */
    tea5767_interface_debug_print("tea5767: tea5767_set_mute/tea5767_get_mute test.\n");
    
    /* set mute */
    res = tea5767_set_mute(&gs_handle, TEA5767_BOOL_TRUE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set mute failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* enable mute */
    tea5767_interface_debug_print("tea5767: enable mute.\n");
    
    /* get mute */
    res = tea5767_get_mute(&gs_handle, &enable);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get mute failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check mute %s.\n", (enable == TEA5767_BOOL_TRUE) ? "ok" : "error");
    
    /* set mute */
    res = tea5767_set_mute(&gs_handle, TEA5767_BOOL_FALSE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set mute failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* disable mute */
    tea5767_interface_debug_print("tea5767: disable mute.\n");
    
    /* get mute */
    res = tea5767_get_mute(&gs_handle, &enable);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get mute failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check mute %s.\n", (enable == TEA5767_BOOL_FALSE) ? "ok" : "error");
    
    /* tea5767_set_mode/tea5767_get_mode test */
    tea5767_interface_debug_print("tea5767: tea5767_set_mode/tea5767_get_mode test.\n");
    
    /* set mode */
    res = tea5767_set_mode(&gs_handle, TEA5767_MODE_SEARCH);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set mode failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set search mode */
    tea5767_interface_debug_print("tea5767: set search mode.\n");
    
    /* get mode */
    res = tea5767_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get mode failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check mode %s.\n", (mode == TEA5767_MODE_SEARCH) ? "ok" : "error");
    
    /* set mode */
    res = tea5767_set_mode(&gs_handle, TEA5767_MODE_NORMAL);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set mode failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set normal mode */
    tea5767_interface_debug_print("tea5767: set normal mode.\n");
    
    /* get mode */
    res = tea5767_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get mode failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check mode %s.\n", (mode == TEA5767_MODE_NORMAL) ? "ok" : "error");
    
    /* tea5767_set_pll/tea5767_get_pll test */
    tea5767_interface_debug_print("tea5767: tea5767_set_pll/tea5767_get_pll test.\n");
    
    /* set pll */
    pll = rand() % 0x3FF;
    res = tea5767_set_pll(&gs_handle, pll);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set pll failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    tea5767_interface_debug_print("tea5767: set pll 0x%04X.\n", pll);
    
    /* get pll */
    res = tea5767_get_pll(&gs_handle, &pll_check);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get pll failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check pll %s.\n", (pll == pll_check) ? "ok" : "error");
    
    /* tea5767_set_search_mode/tea5767_get_search_mode test */
    tea5767_interface_debug_print("tea5767: tea5767_set_search_mode/tea5767_get_search_mode test.\n");
    
    /* set search mode */
    res = tea5767_set_search_mode(&gs_handle, TEA5767_SEARCH_MODE_DOWN);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set search mode failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set search mode down */
    tea5767_interface_debug_print("tea5767: set search mode down.\n");
    
    /* get search mode */
    res = tea5767_get_search_mode(&gs_handle, &search_mode);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get search mode failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check search mode %s.\n", (search_mode == TEA5767_SEARCH_MODE_DOWN) ? "ok" : "error");
    
    /* set search mode */
    res = tea5767_set_search_mode(&gs_handle, TEA5767_SEARCH_MODE_UP);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set search mode failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set search mode up */
    tea5767_interface_debug_print("tea5767: set search mode up.\n");
    
    /* get search mode */
    res = tea5767_get_search_mode(&gs_handle, &search_mode);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get search mode failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check search mode %s.\n", (search_mode == TEA5767_SEARCH_MODE_UP) ? "ok" : "error");
    
    /* tea5767_set_search_stop_level/tea5767_get_search_stop_level test */
    tea5767_interface_debug_print("tea5767: tea5767_set_search_stop_level/tea5767_get_search_stop_level test.\n");
    
    /* set search stop level */
    res = tea5767_set_search_stop_level(&gs_handle, TEA5767_SEARCH_STOP_LEVEL_LOW);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set search stop level failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set search stop level low */
    tea5767_interface_debug_print("tea5767: set search stop level low.\n");
    
    /* get search stop level */
    res = tea5767_get_search_stop_level(&gs_handle, &stop_level);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get search stop level failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check search stop level %s.\n", (stop_level == TEA5767_SEARCH_STOP_LEVEL_LOW) ? "ok" : "error");
    
    /* set search stop level */
    res = tea5767_set_search_stop_level(&gs_handle, TEA5767_SEARCH_STOP_LEVEL_MID);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set search stop level failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set search stop level mid */
    tea5767_interface_debug_print("tea5767: set search stop level mid.\n");
    
    /* get search stop level */
    res = tea5767_get_search_stop_level(&gs_handle, &stop_level);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get search stop level failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check search stop level %s.\n", (stop_level == TEA5767_SEARCH_STOP_LEVEL_MID) ? "ok" : "error");
    
    /* set search stop level */
    res = tea5767_set_search_stop_level(&gs_handle, TEA5767_SEARCH_STOP_LEVEL_HIGH);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set search stop level failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set search stop level high */
    tea5767_interface_debug_print("tea5767: set search stop level high.\n");
    
    /* get search stop level */
    res = tea5767_get_search_stop_level(&gs_handle, &stop_level);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get search stop level failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check search stop level %s.\n", (stop_level == TEA5767_SEARCH_STOP_LEVEL_HIGH) ? "ok" : "error");
    
    /* tea5767_set_side_injection/tea5767_get_side_injection test */
    tea5767_interface_debug_print("tea5767: tea5767_set_side_injection/tea5767_get_side_injection test.\n");
    
    /* set side injection */
    res = tea5767_set_side_injection(&gs_handle, TEA5767_SIDE_INJECTION_LOW);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set side injection failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set side injection low */
    tea5767_interface_debug_print("tea5767: set side injection low.\n");
    
    /* get side injection */
    res = tea5767_get_side_injection(&gs_handle, &side);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get side injection failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check side injection %s.\n", (side == TEA5767_SIDE_INJECTION_LOW) ? "ok" : "error");
    
    /* set side injection */
    res = tea5767_set_side_injection(&gs_handle, TEA5767_SIDE_INJECTION_HIGH);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set side injection failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set side injection high */
    tea5767_interface_debug_print("tea5767: set side injection high.\n");
    
    /* get side injection */
    res = tea5767_get_side_injection(&gs_handle, &side);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get side injection failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check side injection %s.\n", (side == TEA5767_SIDE_INJECTION_HIGH) ? "ok" : "error");
    
    /* tea5767_set_channel/tea5767_get_channel test */
    tea5767_interface_debug_print("tea5767: tea5767_set_channel/tea5767_get_channel test.\n");
    
    /* set channel */
    res = tea5767_set_channel(&gs_handle, TEA5767_CHANNEL_MONO);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set channel failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set channel mono */
    tea5767_interface_debug_print("tea5767: set channel mono.\n");
    
    /* get channel */
    res = tea5767_get_channel(&gs_handle, &channel);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get channel failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check channel %s.\n", (channel == TEA5767_CHANNEL_MONO) ? "ok" : "error");
    
    /* set channel */
    res = tea5767_set_channel(&gs_handle, TEA5767_CHANNEL_STEREO);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set channel failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set channel stereo */
    tea5767_interface_debug_print("tea5767: set channel stereo.\n");
    
    /* get channel */
    res = tea5767_get_channel(&gs_handle, &channel);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get channel failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check channel %s.\n", (channel == TEA5767_CHANNEL_STEREO) ? "ok" : "error");
    
    /* tea5767_set_right_mute/tea5767_get_right_mute test */
    tea5767_interface_debug_print("tea5767: tea5767_set_right_mute/tea5767_get_right_mute test.\n");
    
    /* set right mute */
    res = tea5767_set_right_mute(&gs_handle, TEA5767_BOOL_TRUE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set right mute failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* enable right mute */
    tea5767_interface_debug_print("tea5767: enable right mute.\n");
    
    /* get right mute */
    res = tea5767_get_right_mute(&gs_handle, &enable);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get right mute failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check right mute %s.\n", (enable == TEA5767_BOOL_TRUE) ? "ok" : "error");
    
    /* set right mute */
    res = tea5767_set_right_mute(&gs_handle, TEA5767_BOOL_FALSE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set right mute failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* disable right mute */
    tea5767_interface_debug_print("tea5767: disable right mute.\n");
    
    /* get right mute */
    res = tea5767_get_right_mute(&gs_handle, &enable);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get right mute failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check right mute %s.\n", (enable == TEA5767_BOOL_FALSE) ? "ok" : "error");
    
    /* tea5767_set_left_mute/tea5767_get_left_mute test */
    tea5767_interface_debug_print("tea5767: tea5767_set_left_mute/tea5767_get_left_mute test.\n");
    
    /* set left mute */
    res = tea5767_set_left_mute(&gs_handle, TEA5767_BOOL_TRUE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set left mute failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* enable left mute */
    tea5767_interface_debug_print("tea5767: enable left mute.\n");
    
    /* get left mute */
    res = tea5767_get_left_mute(&gs_handle, &enable);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get left mute failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check left mute %s.\n", (enable == TEA5767_BOOL_TRUE) ? "ok" : "error");
    
    /* set left mute */
    res = tea5767_set_left_mute(&gs_handle, TEA5767_BOOL_FALSE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set left mute failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* disable left mute */
    tea5767_interface_debug_print("tea5767: disable left mute.\n");
    
    /* get left mute */
    res = tea5767_get_left_mute(&gs_handle, &enable);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get left mute failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check left mute %s.\n", (enable == TEA5767_BOOL_FALSE) ? "ok" : "error");
    
    /* tea5767_set_port1/tea5767_get_port1 test */
    tea5767_interface_debug_print("tea5767: tea5767_set_port1/tea5767_get_port1 test.\n");
    
    /* set port1 */
    res = tea5767_set_port1(&gs_handle, TEA5767_LEVEL_HIGH);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set port1 failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set port1 high */
    tea5767_interface_debug_print("tea5767: set port1 high.\n");
    
    /* get port1 */
    res = tea5767_get_port1(&gs_handle, &level);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get port1 failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check port1 %s.\n", (level == TEA5767_LEVEL_HIGH) ? "ok" : "error");
    
    /* set port1 */
    res = tea5767_set_port1(&gs_handle, TEA5767_LEVEL_LOW);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set port1 failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set port1 low */
    tea5767_interface_debug_print("tea5767: set port1 low.\n");
    
    /* get port1 */
    res = tea5767_get_port1(&gs_handle, &level);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get port1 failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check port1 %s.\n", (level == TEA5767_LEVEL_LOW) ? "ok" : "error");
    
    /* tea5767_set_port2/tea5767_get_port2 test */
    tea5767_interface_debug_print("tea5767: tea5767_set_port2/tea5767_get_port2 test.\n");
    
    /* set port2 */
    res = tea5767_set_port2(&gs_handle, TEA5767_LEVEL_HIGH);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set port2 failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set port2 high */
    tea5767_interface_debug_print("tea5767: set port2 high.\n");
    
    /* get port2 */
    res = tea5767_get_port2(&gs_handle, &level);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get port2 failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check port2 %s.\n", (level == TEA5767_LEVEL_HIGH) ? "ok" : "error");
    
    /* set port2 */
    res = tea5767_set_port2(&gs_handle, TEA5767_LEVEL_LOW);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set port2 failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set port2 low */
    tea5767_interface_debug_print("tea5767: set port2 low.\n");
    
    /* get port2 */
    res = tea5767_get_port2(&gs_handle, &level);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get port2 failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check port2 %s.\n", (level == TEA5767_LEVEL_LOW) ? "ok" : "error");
    
    /* tea5767_set_standby/tea5767_get_standby test */
    tea5767_interface_debug_print("tea5767: tea5767_set_standby/tea5767_get_standby test.\n");
    
    /* set standby */
    res = tea5767_set_standby(&gs_handle, TEA5767_BOOL_FALSE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set standby failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* disable standby */
    tea5767_interface_debug_print("tea5767: disable standby.\n");
    
    /* get standby */
    res = tea5767_get_standby(&gs_handle, &enable);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get standby failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check standby %s.\n", (enable == TEA5767_BOOL_FALSE) ? "ok" : "error");
    
    /* set standby */
    res = tea5767_set_standby(&gs_handle, TEA5767_BOOL_TRUE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set standby failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* enable standby */
    tea5767_interface_debug_print("tea5767: enable standby.\n");
    
    /* get standby */
    res = tea5767_get_standby(&gs_handle, &enable);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get standby failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check standby %s.\n", (enable == TEA5767_BOOL_TRUE) ? "ok" : "error");
    
    /* tea5767_set_band/tea5767_get_band test */
    tea5767_interface_debug_print("tea5767: tea5767_set_band/tea5767_get_band test.\n");
    
    /* set band */
    res = tea5767_set_band(&gs_handle, TEA5767_BAND_US_EUROPE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set band failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set us/europe fm band */
    tea5767_interface_debug_print("tea5767: set us/europe fm band.\n");
    
    /* get band */
    res = tea5767_get_band(&gs_handle, &band);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get band failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check band %s.\n", (band == TEA5767_BAND_US_EUROPE) ? "ok" : "error");
    
    /* set band */
    res = tea5767_set_band(&gs_handle, TEA5767_BAND_JAPANESE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set band failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set japanese fm band */
    tea5767_interface_debug_print("tea5767: set japanese fm band.\n");
    
    /* get band */
    res = tea5767_get_band(&gs_handle, &band);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get band failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check band %s.\n", (band == TEA5767_BAND_JAPANESE) ? "ok" : "error");
    
    /* tea5767_set_soft_mute/tea5767_get_soft_mute test */
    tea5767_interface_debug_print("tea5767: tea5767_set_soft_mute/tea5767_get_soft_mute test.\n");
    
    /* set soft mute */
    res = tea5767_set_soft_mute(&gs_handle, TEA5767_BOOL_TRUE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set soft mute failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* enable soft mute */
    tea5767_interface_debug_print("tea5767: enable soft mute.\n");
    
    /* get soft mute */
    res = tea5767_get_soft_mute(&gs_handle, &enable);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get soft mute failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check soft mute %s.\n", (enable == TEA5767_BOOL_TRUE) ? "ok" : "error");
    
    /* set soft mute */
    res = tea5767_set_soft_mute(&gs_handle, TEA5767_BOOL_FALSE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set soft mute failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* disable soft mute */
    tea5767_interface_debug_print("tea5767: disable soft mute.\n");
    
    /* get soft mute */
    res = tea5767_get_soft_mute(&gs_handle, &enable);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get soft mute failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check soft mute %s.\n", (enable == TEA5767_BOOL_FALSE) ? "ok" : "error");
    
    /* tea5767_set_high_cut_control/tea5767_get_high_cut_control test */
    tea5767_interface_debug_print("tea5767: tea5767_set_high_cut_control/tea5767_get_high_cut_control test.\n");
    
    /* set high cut control */
    res = tea5767_set_high_cut_control(&gs_handle, TEA5767_BOOL_FALSE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set high cut control failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* disable high cut control */
    tea5767_interface_debug_print("tea5767: disable high cut control.\n");
    
    /* get high cut control */
    res = tea5767_get_high_cut_control(&gs_handle, &enable);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get high cut control failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check high cut control %s.\n", (enable == TEA5767_BOOL_FALSE) ? "ok" : "error");
    
    /* set high cut control */
    res = tea5767_set_high_cut_control(&gs_handle, TEA5767_BOOL_TRUE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set high cut control failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* enable high cut control */
    tea5767_interface_debug_print("tea5767: enable high cut control.\n");
    
    /* get high cut control */
    res = tea5767_get_high_cut_control(&gs_handle, &enable);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get high cut control failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check high cut control %s.\n", (enable == TEA5767_BOOL_TRUE) ? "ok" : "error");
    
    /* tea5767_set_stereo_noise_cancelling/tea5767_get_stereo_noise_cancelling test */
    tea5767_interface_debug_print("tea5767: tea5767_set_stereo_noise_cancelling/tea5767_get_stereo_noise_cancelling test.\n");
    
    /* set stereo noise cancelling */
    res = tea5767_set_stereo_noise_cancelling(&gs_handle, TEA5767_BOOL_FALSE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set stereo noise cancelling failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* disable stereo noise cancelling */
    tea5767_interface_debug_print("tea5767: disable stereo noise cancelling.\n");
    
    /* get stereo noise cancelling */
    res = tea5767_get_stereo_noise_cancelling(&gs_handle, &enable);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get stereo noise cancelling failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check stereo noise cancelling %s.\n", (enable == TEA5767_BOOL_FALSE) ? "ok" : "error");
    
    /* set stereo noise cancelling */
    res = tea5767_set_stereo_noise_cancelling(&gs_handle, TEA5767_BOOL_TRUE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set stereo noise cancelling failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* enable stereo noise cancelling */
    tea5767_interface_debug_print("tea5767: enable stereo noise cancelling.\n");
    
    /* get stereo noise cancelling */
    res = tea5767_get_stereo_noise_cancelling(&gs_handle, &enable);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get stereo noise cancelling failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check stereo noise cancelling %s.\n", (enable == TEA5767_BOOL_TRUE) ? "ok" : "error");
    
    /* tea5767_set_port1_as_search_indicator/tea5767_get_port1_as_search_indicator test */
    tea5767_interface_debug_print("tea5767: tea5767_set_port1_as_search_indicator/tea5767_get_port1_as_search_indicator test.\n");
    
    /* set port1 as search indicator */
    res = tea5767_set_port1_as_search_indicator(&gs_handle, TEA5767_BOOL_TRUE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set port1 as search indicator failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* enable port1 as search indicator */
    tea5767_interface_debug_print("tea5767: enable port1 as search indicator.\n");
    
    /* get port1 as search indicator */
    res = tea5767_get_port1_as_search_indicator(&gs_handle, &enable);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get port1 as search indicator failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check port1 as search indicator %s.\n", (enable == TEA5767_BOOL_TRUE) ? "ok" : "error");
    
    /* set port1 as search indicator */
    res = tea5767_set_port1_as_search_indicator(&gs_handle, TEA5767_BOOL_FALSE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set port1 as search indicator failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* disable port1 as search indicator */
    tea5767_interface_debug_print("tea5767: disable port1 as search indicator.\n");
    
    /* get port1 as search indicator */
    res = tea5767_get_port1_as_search_indicator(&gs_handle, &enable);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get port1 as search indicator failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check port1 as search indicator %s.\n", (enable == TEA5767_BOOL_FALSE) ? "ok" : "error");
    
    /* tea5767_set_de_emphasis/tea5767_get_de_emphasis test */
    tea5767_interface_debug_print("tea5767: tea5767_set_de_emphasis/tea5767_get_de_emphasis test.\n");
    
    /* set de emphasis */
    res = tea5767_set_de_emphasis(&gs_handle, TEA5767_DE_EMPHASIS_50US);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set de emphasis failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set de emphasis 50us */
    tea5767_interface_debug_print("tea5767: set de emphasis 50us.\n");
    
    /* get de emphasis */
    res = tea5767_get_de_emphasis(&gs_handle, &emphasis);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get de emphasis failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check de emphasis %s.\n", (emphasis == TEA5767_DE_EMPHASIS_50US) ? "ok" : "error");
    
    /* set de emphasis */
    res = tea5767_set_de_emphasis(&gs_handle, TEA5767_DE_EMPHASIS_75US);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set de emphasis failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set de emphasis 75us */
    tea5767_interface_debug_print("tea5767: set de emphasis 75us.\n");
    
    /* get de emphasis */
    res = tea5767_get_de_emphasis(&gs_handle, &emphasis);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get de emphasis failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check de emphasis %s.\n", (emphasis == TEA5767_DE_EMPHASIS_75US) ? "ok" : "error");
    
    /* tea5767_set_clock/tea5767_get_clock test */
    tea5767_interface_debug_print("tea5767: tea5767_set_clock/tea5767_get_clock test.\n");
    
    /* set clock */
    res = tea5767_set_clock(&gs_handle, TEA5767_CLOCK_13_MHZ);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set clock failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set clock 13MHz */
    tea5767_interface_debug_print("tea5767: set clock 13MHz.\n");
    
    /* get clock */
    res = tea5767_get_clock(&gs_handle, &clk);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get clock failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check clock %s.\n", (clk == TEA5767_CLOCK_13_MHZ) ? "ok" : "error");
    
    /* set clock */
    res = tea5767_set_clock(&gs_handle, TEA5767_CLOCK_6P5_MHZ);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set clock failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set clock 6.5MHz */
    tea5767_interface_debug_print("tea5767: set clock 6.5MHz.\n");
    
    /* get clock */
    res = tea5767_get_clock(&gs_handle, &clk);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get clock failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check clock %s.\n", (clk == TEA5767_CLOCK_6P5_MHZ) ? "ok" : "error");
    
    /* set clock */
    res = tea5767_set_clock(&gs_handle, TEA5767_CLOCK_32P768_KHZ);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set clock failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set clock 32.768KHz */
    tea5767_interface_debug_print("tea5767: set clock 32.768KHz.\n");
    
    /* get clock */
    res = tea5767_get_clock(&gs_handle, &clk);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get clock failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    tea5767_interface_debug_print("tea5767: check clock %s.\n", (clk == TEA5767_CLOCK_32P768_KHZ) ? "ok" : "error");
    
    /* write conf */
    res = tea5767_write_conf(&gs_handle);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: write conf failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* read conf */
    res = tea5767_read_conf(&gs_handle);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: read conf failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* tea5767_get_ready_flag test */
    tea5767_interface_debug_print("tea5767: tea5767_get_ready_flag test.\n");
    
    /* get read flag */
    res = tea5767_get_ready_flag(&gs_handle, &enable);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get read flag failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    tea5767_interface_debug_print("tea5767: flag is 0x%02X.\n", enable);
    
    /* tea5767_get_band_limit_flag test */
    tea5767_interface_debug_print("tea5767: tea5767_get_band_limit_flag test.\n");
    
    /* get band limit flag */
    res = tea5767_get_band_limit_flag(&gs_handle, &enable);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get band limit flag failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    tea5767_interface_debug_print("tea5767: flag is 0x%02X.\n", enable);
    
    /* tea5767_get_searched_pll test */
    tea5767_interface_debug_print("tea5767: tea5767_get_searched_pll test.\n");
    
    /* get searched pll */
    res = tea5767_get_searched_pll(&gs_handle, &pll_check);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get searched pll failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    tea5767_interface_debug_print("tea5767: pll is 0x%04X.\n", pll_check);
    
    /* tea5767_get_if test */
    tea5767_interface_debug_print("tea5767: tea5767_get_if test.\n");
    
    /* get if */
    res = tea5767_get_if(&gs_handle, &output);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get if failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    tea5767_interface_debug_print("tea5767: if is 0x%02X.\n", output);
    
    /* tea5767_get_reception test */
    tea5767_interface_debug_print("tea5767: tea5767_get_reception test.\n");
    
    /* get reception */
    res = tea5767_get_reception(&gs_handle, &reception);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get reception failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    tea5767_interface_debug_print("tea5767: reception is 0x%02X.\n", reception);
    
    /* tea5767_get_level_adc_output test */
    tea5767_interface_debug_print("tea5767: tea5767_get_level_adc_output test.\n");
    
    /* get level adc output */
    res = tea5767_get_level_adc_output(&gs_handle, &output);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get level adc output failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    tea5767_interface_debug_print("tea5767: level adc output is 0x%02X.\n", output);
    
    /* tea5767_frequency_convert_to_register/tea5767_frequency_convert_to_data test */
    tea5767_interface_debug_print("tea5767: tea5767_frequency_convert_to_register/tea5767_frequency_convert_to_data test.\n");
    
    mhz = 88.0f + ((float)(rand() % 100) / 50.0f);
    
    /* frequency convert to register */
    res = tea5767_frequency_convert_to_register(&gs_handle, mhz, &pll);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: frequency convert to register failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    tea5767_interface_debug_print("tea5767: frequency is %0.1f.\n", mhz);
    
    /* frequency convert to data */
    res = tea5767_frequency_convert_to_data(&gs_handle, pll, &mhz_check);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: frequency convert to data failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    tea5767_interface_debug_print("tea5767: check frequency is %0.1f.\n", mhz_check);
    
    /* finish register test */
    tea5767_interface_debug_print("tea5767: finish register test.\n");
    (void)tea5767_deinit(&gs_handle);
    
    return 0;
}
