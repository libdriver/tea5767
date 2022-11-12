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
 * @file      driver_tea5767_radio_test.c
 * @brief     driver tea5767 radio test source file
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
 
#include "driver_tea5767_radio_test.h"
#include <stdlib.h>

static tea5767_handle_t gs_handle;        /**< tea5767 handle */

/**
 * @brief     radio test
 * @param[in] clk is the chip crystal frequency
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t tea5767_radio_test(tea5767_clock_t clk)
{
    uint8_t res;
    uint8_t output;
    uint16_t pll;
    float mhz;
    tea5767_reception_t reception;
    tea5767_info_t info;
    tea5767_bool_t ready_flag;
    tea5767_bool_t limit_flag;
    
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
    
    /* start radio test */
    tea5767_interface_debug_print("tea5767: start radio test.\n");
    
    /* tea5767 init */
    res = tea5767_init(&gs_handle);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: init failed.\n");
       
        return 1;
    }
    
    /* disable mute */
    res = tea5767_set_mute(&gs_handle, TEA5767_BOOL_FALSE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set mute failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* search mode */
    res = tea5767_set_mode(&gs_handle, TEA5767_MODE_SEARCH);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set mode failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set pll */
    res = tea5767_set_pll(&gs_handle, 0x2A00);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set pll failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set search mode up */
    res = tea5767_set_search_mode(&gs_handle, TEA5767_SEARCH_MODE_UP);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set search mode failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set search stop level mid*/
    res = tea5767_set_search_stop_level(&gs_handle, TEA5767_SEARCH_STOP_LEVEL_MID);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set search stop level failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set side injection low */
    res = tea5767_set_side_injection(&gs_handle, TEA5767_SIDE_INJECTION_LOW);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set side injection failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set channel stereo */
    res = tea5767_set_channel(&gs_handle, TEA5767_CHANNEL_STEREO);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set channel failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* disable right mute */
    res = tea5767_set_right_mute(&gs_handle, TEA5767_BOOL_FALSE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set right mute failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* disable left mute */
    res = tea5767_set_left_mute(&gs_handle,TEA5767_BOOL_FALSE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set left mute failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set port1 low */
    res = tea5767_set_port1(&gs_handle, TEA5767_LEVEL_LOW);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set port1 failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set port2 low */
    res = tea5767_set_port2(&gs_handle, TEA5767_LEVEL_LOW);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set port2 failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* disable standby */
    res = tea5767_set_standby(&gs_handle, TEA5767_BOOL_FALSE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set standby failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set band Japanese */
    res = tea5767_set_band(&gs_handle, TEA5767_BAND_JAPANESE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set band failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* disable soft mute */
    res = tea5767_set_soft_mute(&gs_handle, TEA5767_BOOL_FALSE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set soft mute failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* enable high cut control */
    res = tea5767_set_high_cut_control(&gs_handle, TEA5767_BOOL_TRUE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set high cut control failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* enable stereo noise cancelling */
    res = tea5767_set_stereo_noise_cancelling(&gs_handle, TEA5767_BOOL_TRUE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set stereo noise cancelling failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* enable port1 as search indicator */
    res = tea5767_set_port1_as_search_indicator(&gs_handle, TEA5767_BOOL_TRUE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set port1 as search indicator failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set de emphasis 50us */
    res = tea5767_set_de_emphasis(&gs_handle, TEA5767_DE_EMPHASIS_50US);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set de emphasis failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set clock */
    res = tea5767_set_clock(&gs_handle, clk);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set clock failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* write conf */
    res = tea5767_write_conf(&gs_handle);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: write conf failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* wait searched */
    while (1)
    {
        /* read conf */
        res = tea5767_read_conf(&gs_handle);
        if (res != 0)
        {
            tea5767_interface_debug_print("tea5767: read conf failed.\n");
            (void)tea5767_deinit(&gs_handle);
           
            return 1;
        }
        
        /* read ready flag */
        res = tea5767_get_ready_flag(&gs_handle, &ready_flag);
        if (res != 0)
        {
            tea5767_interface_debug_print("tea5767: get ready flag failed.\n");
            (void)tea5767_deinit(&gs_handle);
           
            return 1;
        }
        
        /* get band limit flag */
        res = tea5767_get_band_limit_flag(&gs_handle, &limit_flag);
        if (res != 0)
        {
            tea5767_interface_debug_print("tea5767: get band limit flag failed.\n");
            (void)tea5767_deinit(&gs_handle);
           
            return 1;
        }
        
        /* check teh ready flag */
        if (ready_flag == TEA5767_BOOL_TRUE)
        {
            break;
        }
        
        /* delay 500ms */
        tea5767_interface_delay_ms(500);
    }
    if (limit_flag == TEA5767_BOOL_TRUE)
    {
        tea5767_interface_debug_print("tea5767: band limit.\n");
    }
    else
    {
        tea5767_interface_debug_print("tea5767: band found.\n");
    }
    
    /* get searched pll */
    res = tea5767_get_searched_pll(&gs_handle, &pll);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get searched pll failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    tea5767_interface_debug_print("tea5767: searched pll is 0x%04X.\n", pll); 
    
    /* frequency convert to data */
    res = tea5767_frequency_convert_to_data(&gs_handle, pll, &mhz);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: frequency convert to data failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    tea5767_interface_debug_print("tea5767: searched frequency is %0.2fMHz.\n", mhz);
    
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
    
    /* get reception */
    res = tea5767_get_reception(&gs_handle, &reception);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get reception failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    tea5767_interface_debug_print("tea5767: reception is %s.\n", (reception == TEA5767_RECEPTION_MONO) ? "mono" : "stereo"); 
    
    /* get level adc output */
    res = tea5767_get_level_adc_output(&gs_handle, &output);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: get level adc output failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    tea5767_interface_debug_print("tea5767: adc output level is 0x%02X.\n", output); 
    
    /* play 20s */
    tea5767_interface_debug_print("tea5767: play 20s.\n");
    tea5767_interface_delay_ms(20000);
    
    /* finish radio test */
    tea5767_interface_debug_print("tea5767: finish radio test.\n");  
    (void)tea5767_deinit(&gs_handle);
    
    return 0;
}
