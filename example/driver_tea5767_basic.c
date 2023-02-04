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
 * @file      driver_tea5767_basic.c
 * @brief     driver tea5767 basic source file
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

#include "driver_tea5767_basic.h"

static tea5767_handle_t gs_handle;        /**< tea5767 handle */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t tea5767_basic_init(void)
{
    uint8_t res;
    uint16_t pll;

    /* link functions */
    DRIVER_TEA5767_LINK_INIT(&gs_handle, tea5767_handle_t);
    DRIVER_TEA5767_LINK_IIC_INIT(&gs_handle, tea5767_interface_iic_init);
    DRIVER_TEA5767_LINK_IIC_DEINIT(&gs_handle, tea5767_interface_iic_deinit);
    DRIVER_TEA5767_LINK_IIC_READ_COMMAND(&gs_handle, tea5767_interface_iic_read_cmd);
    DRIVER_TEA5767_LINK_IIC_WRITE_COMMAND(&gs_handle, tea5767_interface_iic_write_cmd);
    DRIVER_TEA5767_LINK_DELAY_MS(&gs_handle, tea5767_interface_delay_ms);
    DRIVER_TEA5767_LINK_DEBUG_PRINT(&gs_handle, tea5767_interface_debug_print);
    
    /* tea5767 init */
    res = tea5767_init(&gs_handle);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: init failed.\n");
       
        return 1;
    }
    
    /* set default mute */
    res = tea5767_set_mute(&gs_handle, TEA57671_BASIC_DEFAULT_MUTE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set mute failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set default mode */
    res = tea5767_set_mode(&gs_handle, TEA57671_BASIC_DEFAULT_MODE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set mode failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* default frequency convert to register */
    res = tea5767_frequency_convert_to_register(&gs_handle, TEA57671_BASIC_DEFAULT_MHZ, &pll);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: frequency convert to register failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set default pll */
    res = tea5767_set_pll(&gs_handle, pll);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set pll failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set default search mode */
    res = tea5767_set_search_mode(&gs_handle, TEA57671_BASIC_DEFAULT_SEARCH_MODE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set search mode failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set default search stop level */
    res = tea5767_set_search_stop_level(&gs_handle, TEA57671_BASIC_DEFAULT_SEARCH_STOP_LEVEL);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set search stop level failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set default side injection */
    res = tea5767_set_side_injection(&gs_handle, TEA57671_BASIC_DEFAULT_SIDE_INJECTION);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set side injection failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set default channel */
    res = tea5767_set_channel(&gs_handle, TEA57671_BASIC_DEFAULT_CHANNEL);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set channel failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set default right mute */
    res = tea5767_set_right_mute(&gs_handle, TEA57671_BASIC_DEFAULT_RIGHT_MUTE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set right mute failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set default left mute */
    res = tea5767_set_left_mute(&gs_handle,TEA57671_BASIC_DEFAULT_LEFT_MUTE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set left mute failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set default port1 */
    res = tea5767_set_port1(&gs_handle, TEA57671_BASIC_DEFAULT_PORT1);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set port1 failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set default port2 */
    res = tea5767_set_port2(&gs_handle, TEA57671_BASIC_DEFAULT_PORT2);
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
    
    /* set default band */
    res = tea5767_set_band(&gs_handle, TEA57671_BASIC_DEFAULT_BAND);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set band failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set default soft mute */
    res = tea5767_set_soft_mute(&gs_handle, TEA57671_BASIC_DEFAULT_SOFT_MUTE);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set soft mute failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set default high cut control */
    res = tea5767_set_high_cut_control(&gs_handle, TEA57671_BASIC_DEFAULT_HIGH_CUT_CONTROL);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set high cut control failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set default stereo noise cancelling */
    res = tea5767_set_stereo_noise_cancelling(&gs_handle, TEA57671_BASIC_DEFAULT_STEREO_NOISE_CANCELING);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set stereo noise cancelling failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set default port1 as search indicator */
    res = tea5767_set_port1_as_search_indicator(&gs_handle, TEA57671_BASIC_DEFAULT_PORT1_AS_SEARCH_INDICATOR);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set port1 as search indicator failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set default de emphasis */
    res = tea5767_set_de_emphasis(&gs_handle, TEA57671_BASIC_DEFAULT_DE_EMPHASIS);
    if (res != 0)
    {
        tea5767_interface_debug_print("tea5767: set de emphasis failed.\n");
        (void)tea5767_deinit(&gs_handle);
       
        return 1;
    }
    
    /* set default clock */
    res = tea5767_set_clock(&gs_handle, TEA57671_BASIC_DEFAULT_CLOCK);
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
    
    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t tea5767_basic_deinit(void)
{
    /* close tea5767 */
    if (tea5767_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief  basic example search up
 * @return status code
 *         - 0 success
 *         - 1 search up failed
 *         - 2 reach band limit
 * @note   none
 */
uint8_t tea5767_basic_search_up(void)
{
    uint8_t res;
    uint16_t pll;
    tea5767_bool_t ready_flag;
    tea5767_bool_t limit_flag;
    
    /* set search mode up */
    res = tea5767_set_search_mode(&gs_handle, TEA5767_SEARCH_MODE_UP);
    if (res != 0)
    {
        return 1;
    }
    
    /* search mode */
    res = tea5767_set_mode(&gs_handle, TEA5767_MODE_SEARCH);
    if (res != 0)
    {
        return 1;
    }
    
    /* write conf */
    res = tea5767_write_conf(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    /* wait searched */
    while (1)
    {
        /* read conf */
        res = tea5767_read_conf(&gs_handle);
        if (res != 0)
        {
            return 1;
        }
        
        /* read ready flag */
        res = tea5767_get_ready_flag(&gs_handle, &ready_flag);
        if (res != 0)
        {
            return 1;
        }
        
        /* get band limit flag */
        res = tea5767_get_band_limit_flag(&gs_handle, &limit_flag);
        if (res != 0)
        {
            return 1;
        }
        
        /* check teh ready flag */
        if (ready_flag == TEA5767_BOOL_TRUE)
        {
            break;
        }
        
        /* delay 200ms */
        tea5767_interface_delay_ms(200);
    }
    
    if (limit_flag == TEA5767_BOOL_TRUE)
    {
        return 2;
    }
    else
    {
        /* get the searched pll */
        res = tea5767_get_searched_pll(&gs_handle, &pll);
        if (res != 0)
        {
            return 1;
        }
        
        /* save the pll */
        res = tea5767_set_pll(&gs_handle, pll);
        if (res != 0)
        {
            return 1;
        }
        
        return 0;
    }
}

/**
 * @brief  basic example search down
 * @return status code
 *         - 0 success
 *         - 1 search down failed
 *         - 2 reach band limit
 * @note   none
 */
uint8_t tea5767_basic_search_down(void)
{
    uint8_t res;
    uint16_t pll;
    tea5767_bool_t ready_flag;
    tea5767_bool_t limit_flag;
    
    /* set search mode down */
    res = tea5767_set_search_mode(&gs_handle, TEA5767_SEARCH_MODE_DOWN);
    if (res != 0)
    {
        return 1;
    }
    
    /* search mode */
    res = tea5767_set_mode(&gs_handle, TEA5767_MODE_SEARCH);
    if (res != 0)
    {
        return 1;
    }
    
    /* write conf */
    res = tea5767_write_conf(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    /* wait searched */
    while (1)
    {
        /* read conf */
        res = tea5767_read_conf(&gs_handle);
        if (res != 0)
        {
            return 1;
        }
        
        /* read ready flag */
        res = tea5767_get_ready_flag(&gs_handle, &ready_flag);
        if (res != 0)
        {
            return 1;
        }
        
        /* get band limit flag */
        res = tea5767_get_band_limit_flag(&gs_handle, &limit_flag);
        if (res != 0)
        {
            return 1;
        }
        
        /* check teh ready flag */
        if (ready_flag == TEA5767_BOOL_TRUE)
        {
            break;
        }
        
        /* delay 200ms */
        tea5767_interface_delay_ms(200);
    }
    
    if (limit_flag == TEA5767_BOOL_TRUE)
    {
        return 2;
    }
    else
    {
        /* get the searched pll */
        res = tea5767_get_searched_pll(&gs_handle, &pll);
        if (res != 0)
        {
            return 1;
        }
        
        /* save the pll */
        res = tea5767_set_pll(&gs_handle, pll);
        if (res != 0)
        {
            return 1;
        }
        
        return 0;
    }
}

/**
 * @brief     basic example set frequency
 * @param[in] mhz is the set frequency
 * @return    status code
 *            - 0 success
 *            - 1 set frequency failed
 * @note      none
 */
uint8_t tea5767_basic_set_frequency(float mhz)
{
    uint8_t res;
    uint16_t pll;
    
    /* convert to register */
    res = tea5767_frequency_convert_to_register(&gs_handle, mhz, &pll);
    if (res != 0)
    {
        return 1;
    }
    
    /* set pll */
    res = tea5767_set_pll(&gs_handle, pll);
    if (res != 0)
    {
        return 1;
    }
    
    /* write conf */
    res = tea5767_write_conf(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example get frequency
 * @param[out] *mhz points to a frequency buffer
 * @return     status code
 *             - 0 success
 *             - 1 get frequency failed
 * @note       none
 */
uint8_t tea5767_basic_get_frequency(float *mhz)
{
    uint8_t res;
    uint16_t pll;
    
    /* read conf */
    res = tea5767_read_conf(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    /* get searched pll */
    res = tea5767_get_searched_pll(&gs_handle, &pll);
    if (res != 0)
    {
        return 1;
    }
    
    /* convert */
    res = tea5767_frequency_convert_to_data(&gs_handle, pll, mhz);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example enable or disable mute
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set mute failed
 * @note      none
 */
uint8_t tea5767_basic_set_mute(tea5767_bool_t enable)
{
    uint8_t res;
    
    /* set mute */
    res = tea5767_set_mute(&gs_handle, enable);
    if (res != 0)
    {
        return 1;
    }
    
    /* set right mute */
    res = tea5767_set_right_mute(&gs_handle, enable);
    if (res != 0)
    {
        return 1;
    }
    
    /* set left mute */
    res = tea5767_set_left_mute(&gs_handle, enable);
    if (res != 0)
    {
        return 1;
    }
    
    /* set soft mute */
    res = tea5767_set_soft_mute(&gs_handle, enable);
    if (res != 0)
    {
        return 1;
    }
    
    /* write conf */
    res = tea5767_write_conf(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}
