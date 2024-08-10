[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver TEA5767

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/tea5767/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

The TEA5767 is a single-chip electronically tuned FM stereo radio for low-voltage applications with fully integrated Intermediate Frequency (IF) selectivity and demodulation. The radio is completely adjustment-free and only requires a minimum of small and low cost external components. The radio can be tuned to the European, US, and Japanese FM bands.

LibDriver TEA5767 is the full function driver of TEA5767 launched by LibDriver.It provides FM searching, FM playing and other functions. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver TEA5767 source files.

/interface includes LibDriver TEA5767 IIC platform independent template.

/test includes LibDriver TEA5767 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver TEA5767 sample code.

/doc includes LibDriver TEA5767 offline document.

/datasheet includes TEA5767 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface IIC platform independent template and finish your platform IIC driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_tea5767_basic.h"

uint8_t res;
float mhz;

/* init */
res = tea5767_basic_init();
if (res != 0)
{
    return 1;
}

...

/* search up */
res = tea5767_basic_search_up()；
if (res != 0)
{
    (void)tea5767_basic_deinit();
    
    return 1;
}

res = tea5767_basic_get_frequency(&mhz);
if (res != 0)
{
    (void)tea5767_basic_deinit();
    
    return 1;
}
tea5767_interface_debug_print("tea5767: frequency is %0.2fMHz.\n", mhz);

...

/* search down */
res = tea5767_basic_search_down()；
if (res != 0)
{
    (void)tea5767_basic_deinit();
    
    return 1;
}

res = tea5767_basic_get_frequency(&mhz);
if (res != 0)
{
    (void)tea5767_basic_deinit();
    
    return 1;
}
tea5767_interface_debug_print("tea5767: frequency is %0.2fMHz.\n", mhz);

...

/* enable mute */
res = tea5767_basic_set_mute(TEA5767_BOOL_TRUE);
if (res != 0)
{
    (void)tea5767_basic_deinit();
    
    return 1;
}

...

/* disable mute */
res = tea5767_basic_set_mute(TEA5767_BOOL_FALSE);
if (res != 0)
{
    (void)tea5767_basic_deinit();
    
    return 1;
}

...

/* set the frequency */
res = tea5767_basic_set_frequency(88.67f);
if (res != 0)
{
    (void)tea5767_basic_deinit();
    
    return 1;
}

...

/* deinit */
(void)tea5767_basic_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/tea5767/index.html](https://www.libdriver.com/docs/tea5767/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.