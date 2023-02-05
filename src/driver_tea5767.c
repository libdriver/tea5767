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
 * @file      driver_tea5767.c
 * @brief     driver tea5767 source file
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

#include "driver_tea5767.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "NXP TEA5767"        /**< chip name */
#define MANUFACTURER_NAME         "NXP"                /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.5f                 /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.0f                 /**< chip max supply voltage */
#define MAX_CURRENT               10.5f                /**< chip max current */
#define TEMPERATURE_MIN           -10.0f               /**< chip min operating temperature */
#define TEMPERATURE_MAX           75.0f                /**< chip max operating temperature */
#define DRIVER_VERSION            1000                 /**< driver version */

/**
 * @brief chip address definition
 */
#define TEA5767_ADDRESS             0xC0        /**< iic device address */

/**
 * @brief      read bytes
 * @param[in]  *handle points to a tea5767 handle structure
 * @param[out] *data points to a data buffer
 * @param[in]  len is the data length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_tea5767_iic_read(tea5767_handle_t *handle, uint8_t *data, uint16_t len)
{
    if (handle->iic_read_cmd(TEA5767_ADDRESS, data, len) != 0)        /* read the register */
    {
        return 1;                                                     /* return error */
    }
    else
    {
        return 0;                                                     /* success return 0 */
    }
}

/**
 * @brief     write bytes
 * @param[in] *handle points to a tea5767 handle structure
 * @param[in] *data points to a data buffer
 * @param[in] len is the data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_tea5767_iic_write(tea5767_handle_t *handle, uint8_t *data, uint16_t len)
{
    if (handle->iic_write_cmd(TEA5767_ADDRESS, data, len) != 0)        /* write the register */
    {
        return 1;                                                      /* return error */
    }
    else
    {
        return 0;                                                      /* success return 0 */
    }
}

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
uint8_t tea5767_init(tea5767_handle_t *handle)
{
    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->debug_print == NULL)                                     /* check debug_print */
    {
        return 3;                                                        /* return error */
    }
    if (handle->iic_init == NULL)                                        /* check iic_init */
    {
        handle->debug_print("tea5767: iic_init is null.\n");             /* iic_init is null */
       
        return 3;                                                        /* return error */
    }
    if (handle->iic_deinit == NULL)                                      /* check iic_deinit */
    {
        handle->debug_print("tea5767: iic_deinit is null.\n");           /* iic_deinit is null */
       
        return 3;                                                        /* return error */
    }
    if (handle->iic_read_cmd == NULL)                                    /* check iic_read_cmd */
    {
        handle->debug_print("tea5767: iic_read_cmd is null.\n");         /* iic_read_cmd is null */
       
        return 3;                                                        /* return error */
    }
    if (handle->iic_write_cmd == NULL)                                   /* check iic_write_cmd */
    {
        handle->debug_print("tea5767: iic_write_cmd is null.\n");        /* iic_write_cmd is null */
       
        return 3;                                                        /* return error */
    }
    if (handle->delay_ms == NULL)                                        /* check delay_ms */
    {
        handle->debug_print("tea5767: delay_ms is null.\n");             /* delay_ms is null */
       
        return 3;                                                        /* return error */
    }
    
    if (handle->iic_init() != 0)                                         /* iic init */
    {
        handle->debug_print("tea5767: iic init failed.\n");              /* iic init failed */
       
        return 1;                                                        /* return error */
    }
    handle->inited = 1;                                                  /* flag finish initialization */
    
    return 0;                                                            /* success return 0 */
}

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
uint8_t tea5767_deinit(tea5767_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    handle->conf_up[3] |= 1 << 6;                                    /* set power down */
    res = a_tea5767_iic_write(handle, handle->conf_up, 5);           /* write conf */
    if (res != 0)                                                    /* check result */
    {
        handle->debug_print("tea5767: write conf failed.\n");        /* write conf failed */
       
        return 4;                                                    /* return error */
    }
    res = handle->iic_deinit();                                      /* iic deinit */
    if (res != 0)                                                    /* check error */
    {
        handle->debug_print("tea5767: iic deinit failed.\n");        /* iic deinit failed */
       
        return 1;                                                    /* return error */
    }
    handle->inited = 0;                                              /* flag closed */
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t tea5767_write_conf(tea5767_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    res = a_tea5767_iic_write(handle, handle->conf_up, 5);           /* write conf */
    if (res != 0)                                                    /* check result */
    {
        handle->debug_print("tea5767: write conf failed.\n");        /* write conf failed */
       
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t tea5767_read_conf(tea5767_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                             /* check handle */
    {
        return 2;                                                   /* return error */
    }
    if (handle->inited != 1)                                        /* check handle initialization */
    {
        return 3;                                                   /* return error */
    }
    
    res = a_tea5767_iic_read(handle, handle->conf_down, 5);         /* read conf */
    if (res != 0)                                                   /* check result */
    {
        handle->debug_print("tea5767: read conf failed.\n");        /* read conf failed */
       
        return 1;                                                   /* return error */
    }
    
    return 0;                                                       /* success return 0 */
}

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
uint8_t tea5767_update_conf(tea5767_handle_t *handle, uint8_t conf[5])
{
    if (handle == NULL)                      /* check handle */
    {
        return 2;                            /* return error */
    }
    if (handle->inited != 1)                 /* check handle initialization */
    {
        return 3;                            /* return error */
    }
    
    memcpy(handle->conf_up, conf, 5);        /* copy the conf */
    
    return 0;                                /* success return 0 */
}

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
uint8_t tea5767_set_mute(tea5767_handle_t *handle, tea5767_bool_t enable)
{
    if (handle == NULL)                       /* check handle */
    {
        return 2;                             /* return error */
    }
    if (handle->inited != 1)                  /* check handle initialization */
    {
        return 3;                             /* return error */
    }
    
    handle->conf_up[0] &= ~(1 << 7);          /* clear settings */
    handle->conf_up[0] |= enable << 7;        /* set settings */
    
    return 0;                                 /* success return 0 */
}

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
uint8_t tea5767_get_mute(tea5767_handle_t *handle, tea5767_bool_t *enable)
{
    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->inited != 1)                                             /* check handle initialization */
    {
        return 3;                                                        /* return error */
    }
    
    *enable = (tea5767_bool_t)((handle->conf_up[0] >> 7) & 0x01);        /* get the settings */
    
    return 0;                                                            /* success return 0 */
}

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
uint8_t tea5767_set_mode(tea5767_handle_t *handle, tea5767_mode_t mode)
{
    if (handle == NULL)                       /* check handle */
    {
        return 2;                             /* return error */
    }
    if (handle->inited != 1)                  /* check handle initialization */
    {
        return 3;                             /* return error */
    }
    
    handle->conf_up[0] &= ~(1 << 6);          /* clear settings */
    handle->conf_up[0] |= mode << 6;          /* set settings */
    
    return 0;                                 /* success return 0 */
}

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
uint8_t tea5767_get_mode(tea5767_handle_t *handle, tea5767_mode_t *mode)
{
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->inited != 1)                                           /* check handle initialization */
    {
        return 3;                                                      /* return error */
    }
    
    *mode = (tea5767_mode_t)((handle->conf_up[0] >> 6) & 0x01);        /* get settings */
    
    return 0;                                                          /* success return 0 */
}

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
uint8_t tea5767_set_pll(tea5767_handle_t *handle, uint16_t pll)
{
    uint8_t buf[2];
    
    if (handle == NULL)                                         /* check handle */
    {
        return 2;                                               /* return error */
    }
    if (handle->inited != 1)                                    /* check handle initialization */
    {
        return 3;                                               /* return error */
    }
    if (pll > 0x3FFF)                                           /* check the pll */
    {
        handle->debug_print("tea5767: pll > 0x3FFF.\n");        /* pll > 0x3FFF */
       
        return 4;                                               /* return error */
    }
    
    buf[0] = (pll >> 8) & 0x3F;                                 /* get the pll */
    buf[1] = pll & 0xFF;                                        /* get the pll */
    handle->conf_up[0] &= ~0x3F;                                /* clear settings */
    handle->conf_up[0] |= buf[0];                               /* set settings */
    handle->conf_up[1] = buf[1];                                /* set settings */
    
    return 0;                                                   /* success return 0 */
}

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
uint8_t tea5767_get_pll(tea5767_handle_t *handle, uint16_t *pll)
{
    uint8_t buf[2];
    
    if (handle == NULL)                                        /* check handle */
    {
        return 2;                                              /* return error */
    }
    if (handle->inited != 1)                                   /* check handle initialization */
    {
        return 3;                                              /* return error */
    }
    
    buf[0] = handle->conf_up[0];                               /* get settings */
    buf[1] = handle->conf_up[1];                               /* get settings */
    *pll = (((uint16_t)(buf[0] & 0x3F)) << 8) | buf[1];        /* get the pll */
    
    return 0;                                                  /* success return 0 */
}

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
uint8_t tea5767_set_search_mode(tea5767_handle_t *handle, tea5767_search_mode_t mode)
{
    if (handle == NULL)                     /* check handle */
    {
        return 2;                           /* return error */
    }
    if (handle->inited != 1)                /* check handle initialization */
    {
        return 3;                           /* return error */
    }
    
    handle->conf_up[2] &= ~(1 << 7);        /* clear settings */
    handle->conf_up[2] |= mode << 7;        /* set settings */
    
    return 0;                               /* success return 0 */
}

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
uint8_t tea5767_get_search_mode(tea5767_handle_t *handle, tea5767_search_mode_t *mode)
{
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    *mode = (tea5767_search_mode_t)((handle->conf_up[2] >> 7) & 0x01);        /* get the settings */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t tea5767_set_search_stop_level(tea5767_handle_t *handle, tea5767_search_stop_level_t level)
{
    if (handle == NULL)                     /* check handle */
    {
        return 2;                           /* return error */
    }
    if (handle->inited != 1)                /* check handle initialization */
    {
        return 3;                           /* return error */
    }
    
    handle->conf_up[2] &= ~(3 << 5);        /* clear settings */
    handle->conf_up[2] |= level << 5;       /* set settings */
    
    return 0;                               /* success return 0 */
}

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
uint8_t tea5767_get_search_stop_level(tea5767_handle_t *handle, tea5767_search_stop_level_t *level)
{
    if (handle == NULL)                                                              /* check handle */
    {
        return 2;                                                                    /* return error */
    }
    if (handle->inited != 1)                                                         /* check handle initialization */
    {
        return 3;                                                                    /* return error */
    }
    
    *level = (tea5767_search_stop_level_t)((handle->conf_up[2] >> 5) & 0x03);        /* get the settings */
    
    return 0;                                                                        /* success return 0 */
}

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
uint8_t tea5767_set_side_injection(tea5767_handle_t *handle, tea5767_side_injection_t side)
{
    if (handle == NULL)                    /* check handle */
    {
        return 2;                          /* return error */
    }
    if (handle->inited != 1)               /* check handle initialization */
    {
        return 3;                          /* return error */
    }
    
    handle->conf_up[2] &= ~(1 << 4);       /* clear settings */
    handle->conf_up[2] |= side << 4;       /* set settings */
    
    return 0;                              /* success return 0 */
}

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
uint8_t tea5767_get_side_injection(tea5767_handle_t *handle, tea5767_side_injection_t *side)
{
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    *side = (tea5767_side_injection_t)((handle->conf_up[2] >> 4) & 0x01);        /* get the settings */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t tea5767_set_channel(tea5767_handle_t *handle, tea5767_channel_t channel)
{
    if (handle == NULL)                     /* check handle */
    {
        return 2;                           /* return error */
    }
    if (handle->inited != 1)                /* check handle initialization */
    {
        return 3;                           /* return error */
    }
    
    handle->conf_up[2] &= ~(1 << 3);        /* clear settings */
    handle->conf_up[2] |= channel << 3;       /* set settings */
    
    return 0;                               /* success return 0 */
}

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
uint8_t tea5767_get_channel(tea5767_handle_t *handle, tea5767_channel_t *channel)
{
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    *channel = (tea5767_channel_t)((handle->conf_up[2] >> 3) & 0x01);        /* get the settings */
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t tea5767_set_right_mute(tea5767_handle_t *handle, tea5767_bool_t enable)
{
    if (handle == NULL)                     /* check handle */
    {
        return 2;                           /* return error */
    }
    if (handle->inited != 1)                /* check handle initialization */
    {
        return 3;                           /* return error */
    }
    
    handle->conf_up[2] &= ~(1 << 2);        /* clear settings */
    handle->conf_up[2] |= enable << 2;      /* set settings */
    
    return 0;                               /* success return 0 */
}

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
uint8_t tea5767_get_right_mute(tea5767_handle_t *handle, tea5767_bool_t *enable)
{
    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->inited != 1)                                             /* check handle initialization */
    {
        return 3;                                                        /* return error */
    }
    
    *enable = (tea5767_bool_t)((handle->conf_up[2] >> 2) & 0x01);        /* get the settings */
    
    return 0;                                                            /* success return 0 */
}

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
uint8_t tea5767_set_left_mute(tea5767_handle_t *handle, tea5767_bool_t enable)
{
    if (handle == NULL)                     /* check handle */
    {
        return 2;                           /* return error */
    }
    if (handle->inited != 1)                /* check handle initialization */
    {
        return 3;                           /* return error */
    }
    
    handle->conf_up[2] &= ~(1 << 1);        /* clear settings */
    handle->conf_up[2] |= enable << 1;      /* set settings */
    
    return 0;                               /* success return 0 */
}

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
uint8_t tea5767_get_left_mute(tea5767_handle_t *handle, tea5767_bool_t *enable)
{
    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->inited != 1)                                             /* check handle initialization */
    {
        return 3;                                                        /* return error */
    }
    
    *enable = (tea5767_bool_t)((handle->conf_up[2] >> 1) & 0x01);        /* get the settings */
    
    return 0;                                                            /* success return 0 */
}

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
uint8_t tea5767_set_port1(tea5767_handle_t *handle, tea5767_level_t level)
{
    if (handle == NULL)                    /* check handle */
    {
        return 2;                          /* return error */
    }
    if (handle->inited != 1)               /* check handle initialization */
    {
        return 3;                          /* return error */
    }
    
    handle->conf_up[2] &= ~(1 << 0);       /* clear settings */
    handle->conf_up[2] |= level << 0;      /* set settings */
    
    return 0;                              /* success return 0 */
}

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
uint8_t tea5767_get_port1(tea5767_handle_t *handle, tea5767_level_t *level)
{
    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->inited != 1)                                             /* check handle initialization */
    {
        return 3;                                                        /* return error */
    }
    
    *level = (tea5767_level_t)((handle->conf_up[2] >> 0) & 0x01);        /* get the settings */
    
    return 0;                                                            /* success return 0 */
}

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
uint8_t tea5767_set_port2(tea5767_handle_t *handle, tea5767_level_t level)
{
    if (handle == NULL)                    /* check handle */
    {
        return 2;                          /* return error */
    }
    if (handle->inited != 1)               /* check handle initialization */
    {
        return 3;                          /* return error */
    }
    
    handle->conf_up[3] &= ~(1 << 7);       /* clear settings */
    handle->conf_up[3] |= level << 7;      /* set settings */
    
    return 0;                              /* success return 0 */
}

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
uint8_t tea5767_get_port2(tea5767_handle_t *handle, tea5767_level_t *level)
{
    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->inited != 1)                                             /* check handle initialization */
    {
        return 3;                                                        /* return error */
    }
    
    *level = (tea5767_level_t)((handle->conf_up[3] >> 7) & 0x01);        /* get the settings */
    
    return 0;                                                            /* success return 0 */
}

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
uint8_t tea5767_set_standby(tea5767_handle_t *handle, tea5767_bool_t enable)
{
    if (handle == NULL)                       /* check handle */
    {
        return 2;                             /* return error */
    }
    if (handle->inited != 1)                  /* check handle initialization */
    {
        return 3;                             /* return error */
    }
    
    handle->conf_up[3] &= ~(1 << 6);          /* clear settings */
    handle->conf_up[3] |= enable << 6;        /* set settings */
    
    return 0;                                 /* success return 0 */
}

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
uint8_t tea5767_get_standby(tea5767_handle_t *handle, tea5767_bool_t *enable)
{
    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->inited != 1)                                             /* check handle initialization */
    {
        return 3;                                                        /* return error */
    }
    
    *enable = (tea5767_bool_t)((handle->conf_up[3] >> 6) & 0x01);        /* get the settings */
    
    return 0;                                                            /* success return 0 */
}

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
uint8_t tea5767_set_band(tea5767_handle_t *handle, tea5767_band_t band)
{
    if (handle == NULL)                     /* check handle */
    {
        return 2;                           /* return error */
    }
    if (handle->inited != 1)                /* check handle initialization */
    {
        return 3;                           /* return error */
    }
    
    handle->conf_up[3] &= ~(1 << 5);        /* clear settings */
    handle->conf_up[3] |= band << 5;        /* set settings */
    
    return 0;                               /* success return 0 */
}

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
uint8_t tea5767_get_band(tea5767_handle_t *handle, tea5767_band_t *band)
{
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->inited != 1)                                           /* check handle initialization */
    {
        return 3;                                                      /* return error */
    }
    
    *band = (tea5767_band_t)((handle->conf_up[3] >> 5) & 0x01);        /* get the settings */
    
    return 0;                                                          /* success return 0 */
}

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
uint8_t tea5767_set_soft_mute(tea5767_handle_t *handle, tea5767_bool_t enable)
{
    if (handle == NULL)                       /* check handle */
    {
        return 2;                             /* return error */
    }
    if (handle->inited != 1)                  /* check handle initialization */
    {
        return 3;                             /* return error */
    }
    
    handle->conf_up[3] &= ~(1 << 3);          /* clear settings */
    handle->conf_up[3] |= enable << 3;        /* set settings */
    
    return 0;                                 /* success return 0 */
}

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
uint8_t tea5767_get_soft_mute(tea5767_handle_t *handle, tea5767_bool_t *enable)
{
    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->inited != 1)                                             /* check handle initialization */
    {
        return 3;                                                        /* return error */
    }
    
    *enable = (tea5767_bool_t)((handle->conf_up[3] >> 3) & 0x01);        /* get the settings */
    
    return 0;                                                            /* success return 0 */
}

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
uint8_t tea5767_set_high_cut_control(tea5767_handle_t *handle, tea5767_bool_t enable)
{
    if (handle == NULL)                       /* check handle */
    {
        return 2;                             /* return error */
    }
    if (handle->inited != 1)                  /* check handle initialization */
    {
        return 3;                             /* return error */
    }
    
    handle->conf_up[3] &= ~(1 << 2);          /* clear settings */
    handle->conf_up[3] |= enable << 2;        /* set settings */
    
    return 0;                                 /* success return 0 */
}

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
uint8_t tea5767_get_high_cut_control(tea5767_handle_t *handle, tea5767_bool_t *enable)
{
    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->inited != 1)                                             /* check handle initialization */
    {
        return 3;                                                        /* return error */
    }
    
    *enable = (tea5767_bool_t)((handle->conf_up[3] >> 2) & 0x01);        /* get the settings */
    
    return 0;                                                            /* success return 0 */
}

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
uint8_t tea5767_set_stereo_noise_cancelling(tea5767_handle_t *handle, tea5767_bool_t enable)
{
    if (handle == NULL)                       /* check handle */
    {
        return 2;                             /* return error */
    }
    if (handle->inited != 1)                  /* check handle initialization */
    {
        return 3;                             /* return error */
    }
    
    handle->conf_up[3] &= ~(1 << 1);          /* clear settings */
    handle->conf_up[3] |= enable << 1;        /* set settings */
    
    return 0;                                 /* success return 0 */
}

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
uint8_t tea5767_get_stereo_noise_cancelling(tea5767_handle_t *handle, tea5767_bool_t *enable)
{
    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->inited != 1)                                             /* check handle initialization */
    {
        return 3;                                                        /* return error */
    }
    
    *enable = (tea5767_bool_t)((handle->conf_up[3] >> 1) & 0x01);        /* get the settings */
    
    return 0;                                                            /* success return 0 */
}

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
uint8_t tea5767_set_port1_as_search_indicator(tea5767_handle_t *handle, tea5767_bool_t enable)
{
    if (handle == NULL)                       /* check handle */
    {
        return 2;                             /* return error */
    }
    if (handle->inited != 1)                  /* check handle initialization */
    {
        return 3;                             /* return error */
    }
    
    handle->conf_up[3] &= ~(1 << 0);          /* clear settings */
    handle->conf_up[3] |= enable << 0;        /* set settings */
    
    return 0;                                 /* success return 0 */
}

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
uint8_t tea5767_get_port1_as_search_indicator(tea5767_handle_t *handle, tea5767_bool_t *enable)
{
    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->inited != 1)                                             /* check handle initialization */
    {
        return 3;                                                        /* return error */
    }
    
    *enable = (tea5767_bool_t)((handle->conf_up[3] >> 0) & 0x01);        /* get the settings */
    
    return 0;                                                            /* success return 0 */
}

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
uint8_t tea5767_set_de_emphasis(tea5767_handle_t *handle, tea5767_de_emphasis_t emphasis)
{
    if (handle == NULL)                         /* check handle */
    {
        return 2;                               /* return error */
    }
    if (handle->inited != 1)                    /* check handle initialization */
    {
        return 3;                               /* return error */
    }
    
    handle->conf_up[4] &= ~(1 << 6);            /* clear settings */
    handle->conf_up[4] |= emphasis << 6;        /* set settings */
    
    return 0;                                   /* success return 0 */
}

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
uint8_t tea5767_get_de_emphasis(tea5767_handle_t *handle, tea5767_de_emphasis_t *emphasis)
{
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    
    *emphasis = (tea5767_de_emphasis_t)((handle->conf_up[4] >> 6) & 0x01);        /* get the settings */
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t tea5767_set_clock(tea5767_handle_t *handle, tea5767_clock_t clk)
{
    if (handle == NULL)                                   /* check handle */
    {
        return 2;                                         /* return error */
    }
    if (handle->inited != 1)                              /* check handle initialization */
    {
        return 3;                                         /* return error */
    }
    
    handle->conf_up[3] &= ~(1 << 4);                      /* clear settings */
    handle->conf_up[4] &= ~(1 << 7);                      /* clear settings */
    handle->conf_up[3] |= ((clk >> 0)& 0x01) << 4;        /* set settings */
    handle->conf_up[4] |= ((clk >> 1)& 0x01) << 7;        /* set settings */
    
    return 0;                                             /* success return 0 */
}

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
uint8_t tea5767_get_clock(tea5767_handle_t *handle, tea5767_clock_t *clk)
{
    if (handle == NULL)                                                                                            /* check handle */
    {
        return 2;                                                                                                  /* return error */
    }
    if (handle->inited != 1)                                                                                       /* check handle initialization */
    {
        return 3;                                                                                                  /* return error */
    }
    
    *clk = (tea5767_clock_t)(((handle->conf_up[4] >> 7) & 0x01) << 1 | ((handle->conf_up[3] >> 4) & 0x01));        /* get the settings */
    
    return 0;                                                                                                      /* success return 0 */
}

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
uint8_t tea5767_get_ready_flag(tea5767_handle_t *handle, tea5767_bool_t *enable)
{
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }
    
    *enable = (tea5767_bool_t)((handle->conf_down[0] >> 7) & 0x01);        /* get the settings */
    
    return 0;                                                              /* success return 0 */
}

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
uint8_t tea5767_get_band_limit_flag(tea5767_handle_t *handle, tea5767_bool_t *enable)
{
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }
    
    *enable = (tea5767_bool_t)((handle->conf_down[0] >> 6) & 0x01);        /* get the settings */
    
    return 0;                                                              /* success return 0 */
}

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
uint8_t tea5767_get_searched_pll(tea5767_handle_t *handle, uint16_t *pll)
{
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }
    
    *pll = ((uint16_t)(handle->conf_down[0] & 0x3F) << 8) | handle->conf_down[1];        /* get the settings */
    
    return 0;                                                                            /* success return 0 */
}

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
uint8_t tea5767_get_if(tea5767_handle_t *handle, uint8_t *if_out)
{
    if (handle == NULL)                           /* check handle */
    {
        return 2;                                 /* return error */
    }
    if (handle->inited != 1)                      /* check handle initialization */
    {
        return 3;                                 /* return error */
    }
    
    *if_out = handle->conf_down[2] & 0x7F;        /* get the settings */
    
    return 0;                                     /* success return 0 */
}

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
uint8_t tea5767_get_reception(tea5767_handle_t *handle, tea5767_reception_t *reception)
{
    if (handle == NULL)                                                            /* check handle */
    {
        return 2;                                                                  /* return error */
    }
    if (handle->inited != 1)                                                       /* check handle initialization */
    {
        return 3;                                                                  /* return error */
    }
    
    *reception = (tea5767_reception_t)((handle->conf_down[2] >> 7) & 0x01);        /* get the settings */
    
    return 0;                                                                      /* success return 0 */
}

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
uint8_t tea5767_get_level_adc_output(tea5767_handle_t *handle, uint8_t *output)
{
    if (handle == NULL)                                 /* check handle */
    {
        return 2;                                       /* return error */
    }
    if (handle->inited != 1)                            /* check handle initialization */
    {
        return 3;                                       /* return error */
    }
    
    *output = (handle->conf_down[3] >> 4) & 0xF;        /* get the settings */
    
    return 0;                                           /* success return 0 */
}

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
uint8_t tea5767_frequency_convert_to_register(tea5767_handle_t *handle, float mhz, uint16_t *pll)
{
    uint8_t hlsi;
    uint8_t clk;
    float f;
    
    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->inited != 1)                                             /* check handle initialization */
    {
        return 3;                                                        /* return error */
    }
    
    hlsi = (handle->conf_up[2] >> 4) & 0x01;                             /* get hte hlsi */
    clk = ((handle->conf_up[4] >> 7) & 0x01) << 1 
             | ((handle->conf_up[3] >> 4) & 0x01);                       /* get the clock */
    if (clk == 0x00)                                                     /* 13MHz */
    {
        f = 13000.0f;                                                    /* 13MHz */
    }
    else if (clk == 0x01)                                                /* 32.768KHz */
    {
        f = 32.768f;                                                     /* 32.768KHz */
    }
    else if (clk == 0x02)                                                /* 6.5MHz */
    {
        f = 6500.0f;                                                     /* 6.5MHz */
    }
    else
    {
        handle->debug_print("tea5767: clock is invalid.\n");             /* clock is invalid */
       
        return 4;                                                        /* return error */
    }
    
    if (hlsi != 0)                                                       /* high side lo injection */
    {
        *pll = (uint16_t)((4.0f * (mhz * 1000.0f + 225.0f)) / f);        /* convert real data to raw data */
    }                                                                    /* low side lo injection */
    else
    {
        *pll = (uint16_t)((4.0f * (mhz * 1000.0f - 225.0f)) / f);        /* convert real data to raw data */
    }
    
    return 0;                                                            /* success return 0 */
}

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
uint8_t tea5767_frequency_convert_to_data(tea5767_handle_t *handle, uint16_t pll, float *mhz)
{
    uint8_t hlsi;
    uint8_t clk;
    float f;
    
    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->inited != 1)                                             /* check handle initialization */
    {
        return 3;                                                        /* return error */
    }
    
    hlsi = (handle->conf_up[2] >> 4) & 0x01;                             /* get hte hlsi */
    clk = ((handle->conf_up[4] >> 7) & 0x01) << 1 
             | ((handle->conf_up[3] >> 4) & 0x01);                       /* get the clock */
    if (clk == 0x00)                                                     /* 13MHz */
    {
        f = 13000.0f;                                                    /* 13MHz */
    }
    else if (clk == 0x01)                                                /* 32.768KHz */
    {
        f = 32.768f;                                                     /* 32.768KHz */
    }
    else if (clk == 0x02)                                                /* 6.5MHz */
    {
        f = 6500.0f;                                                     /* 6.5MHz */
    }
    else
    {
        handle->debug_print("tea5767: clock is invalid.\n");             /* clock is invalid */
       
        return 4;                                                        /* return error */
    }
    
    if (hlsi != 0)                                                       /* high side lo injection */
    {
        *mhz = (pll * f / 4.0f - 255.0f) / 1000.0f;                      /* convert raw data to real data */
    }                                                                    /* low side lo injection */
    else
    {
        *mhz = (pll * f / 4.0f + 255.0f) / 1000.0f;                      /* convert raw data to real data */
    }
    
    return 0;                                                            /* success return 0 */
}

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
uint8_t tea5767_set_reg(tea5767_handle_t *handle, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                  /* check handle */
    {
        return 2;                                        /* return error */
    }
    if (handle->inited != 1)                             /* check handle initialization */
    {
        return 3;                                        /* return error */
    }
    
    return a_tea5767_iic_write(handle, buf, len);        /* write command */
}

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
uint8_t tea5767_get_reg(tea5767_handle_t *handle, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                 /* check handle */
    {
        return 2;                                       /* return error */
    }
    if (handle->inited != 1)                            /* check handle initialization */
    {
        return 3;                                       /* return error */
    }
    
    return a_tea5767_iic_read(handle, buf, len);        /* read command */
}

/**
 * @brief      get chip's information
 * @param[out] *info points to a tea5767 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t tea5767_info(tea5767_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(tea5767_info_t));                        /* initialize tea5767 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
