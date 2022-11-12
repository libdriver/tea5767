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
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];                              /**< uart buffer */
uint16_t g_len;                                  /**< uart buffer length */
static int gs_listen_fd, gs_conn_fd;             /**< network handle */
static struct sockaddr_in gs_server_addr;        /**< server address */

/**
 * @brief     tea5767 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t tea5767(uint8_t argc, char **argv)
{
    if (argc == 1)
    {
        goto help;
    }
    else if (argc == 2)
    {
        if (strcmp("-i", argv[1]) == 0)
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
        else if (strcmp("-p", argv[1]) == 0)
        {
            /* print pin connection */
            tea5767_interface_debug_print("tea5767: SCL connected to GPIO3(BCM).\n");
            tea5767_interface_debug_print("tea5767: SDA connected to GPIO2(BCM).\n");
            
            return 0;
        }
        else if (strcmp("-h", argv[1]) == 0)
        {
            /* show tea5767 help */
            
            help:
            tea5767_interface_debug_print("tea5767 -i\n\tshow tea5767 chip and driver information.\n");
            tea5767_interface_debug_print("tea5767 -h\n\tshow tea5767 help.\n");
            tea5767_interface_debug_print("tea5767 -p\n\tshow tea5767 pin connections of the current board.\n");
            tea5767_interface_debug_print("tea5767 -t reg\n\trun tea5767 register test.\n");
            tea5767_interface_debug_print("tea5767 -t radio -f (13MHz | 6.5MHz | 32.768KHz)\n\trun tea5767 radio test.\n");
            tea5767_interface_debug_print("tea5767 -c basic -init\n\ttea5767 init function.\n");
            tea5767_interface_debug_print("tea5767 -c basic -deinit\n\ttea5767 deinit function.\n");
            tea5767_interface_debug_print("tea5767 -c basic -up\n\ttea5767 search up function.\n");
            tea5767_interface_debug_print("tea5767 -c basic -down\n\ttea5767 search down function.\n");
            tea5767_interface_debug_print("tea5767 -c basic -mute\n\ttea5767 mute function.\n");
            tea5767_interface_debug_print("tea5767 -c basic -no-mute\n\ttea5767 disable mute function.\n");
            tea5767_interface_debug_print("tea5767 -c basic -set <freq>\n\ttea5767 set the frequency function.freq is the set frequency.\n");
            tea5767_interface_debug_print("tea5767 -c basic -get\n\ttea5767 get the current frequency function.\n");
            
            return 0;
        }
        else
        {
            return 5;
        }
    }
    else if (argc == 3)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
             /* reg test */
            if (strcmp("reg", argv[2]) == 0)
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
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 4)
    {
        /* run function */
        if (strcmp("-c", argv[1]) == 0)
        {
             /* basic function */
            if (strcmp("basic", argv[2]) == 0)
            {
                 /* init function */
                if (strcmp("-init", argv[3]) == 0)
                {
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
                /* deinit function */
                else if (strcmp("-deinit", argv[3]) == 0)
                {
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
                /* up function */
                else if (strcmp("-up", argv[3]) == 0)
                {
                    float mhz;
                    
                    if (tea5767_basic_search_up() != 0)
                    {
                        return 1;
                    }
                    else
                    {
                        if (tea5767_basic_get_frequency(&mhz) != 0)
                        {
                            return 1;
                        }
                        tea5767_interface_debug_print("tea5767: search up successful.\n");
                        tea5767_interface_debug_print("tea5767: frequency is %0.2fMHz.\n", mhz);
                        
                        return 0;
                    }
                }
                /* down function */
                else if (strcmp("-down", argv[3]) == 0)
                {
                    float mhz;
                    
                    if (tea5767_basic_search_down() != 0)
                    {
                        return 1;
                    }
                    else
                    {
                        if (tea5767_basic_get_frequency(&mhz) != 0)
                        {
                            return 1;
                        }
                        tea5767_interface_debug_print("tea5767: search down successful.\n");
                        tea5767_interface_debug_print("tea5767: frequency is %0.2fMHz.\n", mhz);
                        
                        return 0;
                    }
                }
                /* mute function */
                else if (strcmp("-mute", argv[3]) == 0)
                {
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
                /* no-mute function */
                else if (strcmp("-no-mute", argv[3]) == 0)
                {
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
                /* get */
                else if (strcmp("-get", argv[3]) == 0)
                {
                    float mhz;
                    
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
                else
                {
                    return 5;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 5)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
             /* radio test */
            if (strcmp("radio", argv[2]) == 0)
            {
                /* check -f */
                if (strcmp("-f", argv[3]) == 0)
                {
                    tea5767_clock_t clk;
                    
                    if (strcmp("13MHz", argv[4]) == 0)
                    {
                        clk = TEA5767_CLOCK_13_MHZ;
                    }
                    else if (strcmp("6.5MHz", argv[4]) == 0)
                    {
                        clk = TEA5767_CLOCK_6P5_MHZ;
                    }
                    else if (strcmp("32.768KHz", argv[4]) == 0)
                    {
                        clk = TEA5767_CLOCK_32P768_KHZ;
                    }
                    else
                    {
                        return 5;
                    }
                    
                    /* run radio test */
                    if (tea5767_radio_test(clk) != 0)
                    {
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
                /* param is invalid */
                else
                {
                    return 5;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* run function */
        else if (strcmp("-c", argv[1]) == 0)
        {
             /* basic function */
            if (strcmp("basic", argv[2]) == 0)
            {
                 /* set function */
                if (strcmp("-set", argv[3]) == 0)
                {
                    if (tea5767_basic_set_frequency((float)atof(argv[4])) != 0)
                    {
                        return 1;
                    }
                    else
                    {
                        tea5767_interface_debug_print("tea5767: set frequency %0.2fMHz.\n", atof(argv[4]));
                        
                        return 0;
                    }
                }
                else
                {
                    return 5;
                }
            }
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    /* param is invalid */
    else
    {
        return 5;
    }
}

/**
 * @brief  socket init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
static uint8_t a_socket_init(void)
{
    int optval;

    if ((gs_listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    {
        tea5767_interface_debug_print("tea5767: cread socket failed.\n");
        
        return 1;
    }

    memset(&gs_server_addr, 0, sizeof(gs_server_addr));
    gs_server_addr.sin_family = AF_INET;
    gs_server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    gs_server_addr.sin_port = htons(6666);

    optval = 1;
    if (setsockopt(gs_listen_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&optval, sizeof(optval)))
    {
        tea5767_interface_debug_print("tea5767: cread socket failed.\n");
        
        return 1;
    }
    if (bind(gs_listen_fd, (struct sockaddr*)&gs_server_addr, sizeof(gs_server_addr)) < 0) 
    {
        tea5767_interface_debug_print("tea5767: bind failed.\n");

        return 1;
    }

    if (listen(gs_listen_fd, 10) < -1) 
    {
        tea5767_interface_debug_print("tea5767: listen failed.\n");

        return 1;
    }

    return 0;
}

/**
 * @brief     socket read
 * @param[in] *buf points to a buffer address
 * @param[in] len is the buffer length
 * @return    status code
 *             - 0 success
 *             - 1 read failed
 * @note      none
 */
static uint16_t a_socket_read(uint8_t *buf, uint16_t len)
{
    int n;

    if ((gs_conn_fd = accept(gs_listen_fd, (struct sockaddr *)NULL, NULL))  == -1) 
    {
        tea5767_interface_debug_print("tea5767: accept failed.\n");
            
        return 1;
    }

    n = recv(gs_conn_fd, buf, len, 0);

    close(gs_conn_fd);

    return n;
}

/**
 * @brief     signal handler
 * @param[in] signum is the signal number
 * @note      none
 */
static void a_sig_handler(int signum)
{
    if (SIGINT == signum)
    {
        tea5767_interface_debug_print("tea5767: close the server.\n");
        close(gs_listen_fd);
        exit(0);
    }

    return;
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* socket init*/
    res = a_socket_init();
    if (res)
    {
        tea5767_interface_debug_print("tea5767: socket init failed.\n");

        return 1;
    }

    /* shell init && register tea5767 fuction */
    shell_init();
    shell_register("tea5767", tea5767);
    tea5767_interface_debug_print("tea5767: welcome to libdriver tea5767.\n");
    signal(SIGINT, a_sig_handler);

    while (1)
    {
        /* read uart */
        g_len = a_socket_read(g_buf, 256);
        if (g_len)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                tea5767_interface_debug_print("tea5767: run failed.\n");
            }
            else if (res == 2)
            {
                tea5767_interface_debug_print("tea5767: unknow command.\n");
            }
            else if (res == 3)
            {
                tea5767_interface_debug_print("tea5767: length is too long.\n");
            }
            else if (res == 4)
            {
                tea5767_interface_debug_print("tea5767: pretreat failed.\n");
            }
            else if (res == 5)
            {
                tea5767_interface_debug_print("tea5767: param is invalid.\n");
            }
            else
            {
                tea5767_interface_debug_print("tea5767: unknow status code.\n");
            }
        }
    }
}
