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
 * @file      main.c
 * @brief     main source file
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
#include "driver_tea5767_radio_test.h"
#include "driver_tea5767_basic.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include "getopt.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];        /**< uart buffer */
volatile uint16_t g_len;   /**< uart buffer length */

/**
 * @brief     tea5767 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t tea5767(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"crystal", required_argument, NULL, 1},
        {"freq", required_argument, NULL, 2},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    tea5767_clock_t crystal = TEA5767_CLOCK_32P768_KHZ;
    float freq = 0.0f;
    uint8_t freq_flag = 0;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* crystal */
            case 1 :
            {
                /* set the crystal */
                if (strcmp("13MHz", optarg) == 0)
                {
                    crystal = TEA5767_CLOCK_13_MHZ;
                }
                else if (strcmp("32.768KHz", optarg) == 0)
                {
                    crystal = TEA5767_CLOCK_32P768_KHZ;
                }
                else if (strcmp("6.5MHz", optarg) == 0)
                {
                    crystal = TEA5767_CLOCK_6P5_MHZ;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* freq */
            case 2 :
            {
                /* set the freq */
                freq = (float)atof(optarg);
                freq_flag = 1;
                
                break;
            }
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_reg", type) == 0)
    {
        /* run reg test */
        if (tea5767_register_test() != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("t_radio", type) == 0)
    {
        /* run radio test */
        if (tea5767_radio_test(crystal) != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("e_init", type) == 0)
    {
        /* basic init */
        if (tea5767_basic_init() != 0)
        {
            return 1;
        }
        else
        {
            tea5767_interface_debug_print("tea5767: init successful.\n");
            
            return 0;
        }
    }
    else if (strcmp("e_deinit", type) == 0)
    {
        /* basic deinit */
        if (tea5767_basic_deinit() != 0)
        {
            return 1;
        }
        else
        {
            tea5767_interface_debug_print("tea5767: deinit successful.\n");
            
            return 0;
        }
    }
    else if (strcmp("e_up", type) == 0)
    {
        float mhz;
        
        /* basic up */
        if (tea5767_basic_search_up() != 0)
        {
            return 1;
        }
        else
        {
            /* get freq */
            if (tea5767_basic_get_frequency(&mhz) != 0)
            {
                return 1;
            }
            tea5767_interface_debug_print("tea5767: search up successful.\n");
            tea5767_interface_debug_print("tea5767: frequency is %0.2fMHz.\n", mhz);
            
            return 0;
        }
    }
    else if (strcmp("e_down", type) == 0)
    {
        float mhz;
        
        /* basic down */
        if (tea5767_basic_search_down() != 0)
        {
            return 1;
        }
        else
        {
            /* get freq */
            if (tea5767_basic_get_frequency(&mhz) != 0)
            {
                return 1;
            }
            tea5767_interface_debug_print("tea5767: search down successful.\n");
            tea5767_interface_debug_print("tea5767: frequency is %0.2fMHz.\n", mhz);
            
            return 0;
        }
    }
    else if (strcmp("e_mute", type) == 0)
    {
        /* mute */
        if (tea5767_basic_set_mute(TEA5767_BOOL_TRUE) != 0)
        {
            return 1;
        }
        else
        {
            tea5767_interface_debug_print("tea5767: mute successful.\n");
            
            return 0;
        }
    }
    else if (strcmp("e_no-mute", type) == 0)
    {
        /* not mute */
        if (tea5767_basic_set_mute(TEA5767_BOOL_FALSE) != 0)
        {
            return 1;
        }
        else
        {
            tea5767_interface_debug_print("tea5767: disable mute successful.\n");
            
            return 0;
        }
    }
    else if (strcmp("e_get", type) == 0)
    {
        float mhz;
        
        /* get freq */
        if (tea5767_basic_get_frequency(&mhz) != 0)
        {
            return 1;
        }
        else
        {
            tea5767_interface_debug_print("tea5767: frequency is %0.2fMHz.\n", mhz);
            
            return 0;
        }
    }
    else if (strcmp("e_set", type) == 0)
    {
        /* check the freq */
        if (freq_flag != 1)
        {
            return 5;
        }
        
        /* set freq */
        if (tea5767_basic_set_frequency(freq) != 0)
        {
            return 1;
        }
        else
        {
            tea5767_interface_debug_print("tea5767: set frequency %0.2fMHz.\n", freq);
            
            return 0;
        }
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        tea5767_interface_debug_print("Usage:\n");
        tea5767_interface_debug_print("  tea5767 (-i | --information)\n");
        tea5767_interface_debug_print("  tea5767 (-h | --help)\n");
        tea5767_interface_debug_print("  tea5767 (-p | --port)\n");
        tea5767_interface_debug_print("  tea5767 (-t reg | --test=reg)\n");
        tea5767_interface_debug_print("  tea5767 (-t radio | --test=radio) [--crystal=<13MHz | 6.5MHz | 32.768KHz>]\n");
        tea5767_interface_debug_print("  tea5767 (-e init | --example=init)\n");
        tea5767_interface_debug_print("  tea5767 (-e deinit | --example=deinit)\n");
        tea5767_interface_debug_print("  tea5767 (-e up | --example=up)\n");
        tea5767_interface_debug_print("  tea5767 (-e down | --example=down)\n");
        tea5767_interface_debug_print("  tea5767 (-e mute | --example=mute)\n");
        tea5767_interface_debug_print("  tea5767 (-e no-mute | --example=no-mute)\n");
        tea5767_interface_debug_print("  tea5767 (-e set | --example=set) --freq=<MHz>\n");
        tea5767_interface_debug_print("  tea5767 (-e get | --example=get)\n");
        tea5767_interface_debug_print("\n");
        tea5767_interface_debug_print("Options:\n");
        tea5767_interface_debug_print("      --crystal=<13MHz | 6.5MHz | 32.768KHz>\n");
        tea5767_interface_debug_print("                          Set the crystal frequence.([default: 32.768KHz])\n");
        tea5767_interface_debug_print("  -e <init | deinit | up | down | mute | no-mute | set | get>, --example=<init\n");
        tea5767_interface_debug_print("     | deinit | up | down | mute | no-mute | set | get>\n");
        tea5767_interface_debug_print("                          Run the driver example.\n");
        tea5767_interface_debug_print("      --freq=<MHz>        Set the frequence in MHz.\n");
        tea5767_interface_debug_print("  -h, --help              Show the help.\n");
        tea5767_interface_debug_print("  -i, --information       Show the chip information.\n");
        tea5767_interface_debug_print("  -p, --port              Display the pin connections of the current board.\n");
        tea5767_interface_debug_print("  -t <reg | radio>, --test=<reg | radio>\n");
        tea5767_interface_debug_print("                          Run the driver test.\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        tea5767_info_t info;
        
        /* print tea5767 info */
        tea5767_info(&info);
        tea5767_interface_debug_print("tea5767: chip is %s.\n", info.chip_name);
        tea5767_interface_debug_print("tea5767: manufacturer is %s.\n", info.manufacturer_name);
        tea5767_interface_debug_print("tea5767: interface is %s.\n", info.interface);
        tea5767_interface_debug_print("tea5767: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        tea5767_interface_debug_print("tea5767: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        tea5767_interface_debug_print("tea5767: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        tea5767_interface_debug_print("tea5767: max current is %0.2fmA.\n", info.max_current_ma);
        tea5767_interface_debug_print("tea5767: max temperature is %0.1fC.\n", info.temperature_max);
        tea5767_interface_debug_print("tea5767: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        tea5767_interface_debug_print("tea5767: SCL connected to GPIOB PIN8.\n");
        tea5767_interface_debug_print("tea5767: SDA connected to GPIOB PIN9.\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart init */
    uart_init(115200);
    
    /* shell init && register tea5767 function */
    shell_init();
    shell_register("tea5767", tea5767);
    uart_print("tea5767: welcome to libdriver tea5767.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart_print("tea5767: run failed.\n");
            }
            else if (res == 2)
            {
                uart_print("tea5767: unknown command.\n");
            }
            else if (res == 3)
            {
                uart_print("tea5767: length is too long.\n");
            }
            else if (res == 4)
            {
                uart_print("tea5767: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart_print("tea5767: param is invalid.\n");
            }
            else
            {
                uart_print("tea5767: unknown status code.\n");
            }
            uart_flush();
        }
        delay_ms(100);
    }
}
