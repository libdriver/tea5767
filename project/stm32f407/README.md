### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. TEA5767

#### 3.1 Command Instruction

1. Show tea5767 chip and driver information.

   ```shell
   tea5767 (-i | --information)
   ```

2. Show tea5767 help.

   ```shell
   tea5767 (-h | --help)
   ```

3. Show tea5767 pin connections of the current board.

   ```shell
   tea5767 (-p | --port)
   ```

4. Run tea5767 register test.

   ```shell
   tea5767 (-t reg | --test=reg)
   ```

5. Run tea5767 radio test.

   ```shell
   tea5767 (-t radio | --test=radio) [--crystal=<13MHz | 6.5MHz | 32.768KHz>]
   ```

6. Run tea5767 init function.

   ```shell
   tea5767 (-e init | --example=init)
   ```

7. Run tea5767 deinit function.

   ```shell
   tea5767 (-e deinit | --example=deinit)
   ```

8. Run tea5767 search up function.

   ```shell
   tea5767 (-e up | --example=up)
   ```

9. Run tea5767 search down function.

   ```shell
   tea5767 (-e down | --example=down)
   ```

10. Run tea5767 mute function.

    ```shell
    tea5767 (-e mute | --example=mute)
    ```

11. Run tea5767 disable mute function.

    ```shell
    tea5767 (-e no-mute | --example=no-mute)
    ```

12. Run tea5767 set the frequency function, MHz is the set frequency.

    ```shell
    tea5767 (-e set | --example=set) --freq=<MHz>
    ```

13. Run tea5767 get the current frequency function.

    ```shell
    tea5767 (-e get | --example=get)
    ```

#### 3.2 Command Example

```shell
tea5767 -i

tea5767: chip is NXP TEA5767.
tea5767: manufacturer is NXP.
tea5767: interface is IIC.
tea5767: driver version is 1.0.
tea5767: min supply voltage is 2.5V.
tea5767: max supply voltage is 5.0V.
tea5767: max current is 10.50mA.
tea5767: max temperature is 75.0C.
tea5767: min temperature is -10.0C.
```

```shell
tea5767 -p

tea5767: SCL connected to GPIOB PIN8.
tea5767: SDA connected to GPIOB PIN9.
```

```shell
tea5767 -t reg

tea5767: chip is NXP TEA5767.
tea5767: manufacturer is NXP.
tea5767: interface is IIC.
tea5767: driver version is 1.0.
tea5767: min supply voltage is 2.5V.
tea5767: max supply voltage is 5.0V.
tea5767: max current is 10.50mA.
tea5767: max temperature is 75.0C.
tea5767: min temperature is -10.0C.
tea5767: start register test.
tea5767: tea5767_set_mute/tea5767_get_mute test.
tea5767: enable mute.
tea5767: check mute ok.
tea5767: disable mute.
tea5767: check mute ok.
tea5767: tea5767_set_mode/tea5767_get_mode test.
tea5767: set search mode.
tea5767: check mode ok.
tea5767: set normal mode.
tea5767: check mode ok.
tea5767: tea5767_set_pll/tea5767_get_pll test.
tea5767: set pll 0x03FD.
tea5767: check pll ok.
tea5767: tea5767_set_search_mode/tea5767_get_search_mode test.
tea5767: set search mode down.
tea5767: check search mode ok.
tea5767: set search mode up.
tea5767: check search mode ok.
tea5767: tea5767_set_search_stop_level/tea5767_get_search_stop_level test.
tea5767: set search stop level low.
tea5767: check search stop level ok.
tea5767: set search stop level mid.
tea5767: check search stop level ok.
tea5767: set search stop level high.
tea5767: check search stop level ok.
tea5767: tea5767_set_side_injection/tea5767_get_side_injection test.
tea5767: set side injection low.
tea5767: check side injection ok.
tea5767: set side injection high.
tea5767: check side injection ok.
tea5767: tea5767_set_channel/tea5767_get_channel test.
tea5767: set channel mono.
tea5767: check channel ok.
tea5767: set channel stereo.
tea5767: check channel ok.
tea5767: tea5767_set_right_mute/tea5767_get_right_mute test.
tea5767: enable right mute.
tea5767: check right mute ok.
tea5767: disable right mute.
tea5767: check right mute ok.
tea5767: tea5767_set_left_mute/tea5767_get_left_mute test.
tea5767: enable left mute.
tea5767: check left mute ok.
tea5767: disable left mute.
tea5767: check left mute ok.
tea5767: tea5767_set_port1/tea5767_get_port1 test.
tea5767: set port1 high.
tea5767: check port1 ok.
tea5767: set port1 low.
tea5767: check port1 ok.
tea5767: tea5767_set_port2/tea5767_get_port2 test.
tea5767: set port2 high.
tea5767: check port2 ok.
tea5767: set port2 low.
tea5767: check port2 ok.
tea5767: tea5767_set_standby/tea5767_get_standby test.
tea5767: disable standby.
tea5767: check standby ok.
tea5767: enable standby.
tea5767: check standby ok.
tea5767: tea5767_set_band/tea5767_get_band test.
tea5767: set us/europe fm band.
tea5767: check band ok.
tea5767: set japanese fm band.
tea5767: check band ok.
tea5767: tea5767_set_soft_mute/tea5767_get_soft_mute test.
tea5767: enable soft mute.
tea5767: check soft mute ok.
tea5767: disable soft mute.
tea5767: check soft mute ok.
tea5767: tea5767_set_high_cut_control/tea5767_get_high_cut_control test.
tea5767: disable high cut control.
tea5767: check high cut control ok.
tea5767: enable high cut control.
tea5767: check high cut control ok.
tea5767: tea5767_set_stereo_noise_cancelling/tea5767_get_stereo_noise_cancelling test.
tea5767: disable stereo noise cancelling.
tea5767: check stereo noise cancelling ok.
tea5767: enable stereo noise cancelling.
tea5767: check stereo noise cancelling ok.
tea5767: tea5767_set_port1_as_search_indicator/tea5767_get_port1_as_search_indicator test.
tea5767: enable port1 as search indicator.
tea5767: check port1 as search indicator ok.
tea5767: disable port1 as search indicator.
tea5767: check port1 as search indicator ok.
tea5767: tea5767_set_de_emphasis/tea5767_get_de_emphasis test.
tea5767: set de emphasis 50us.
tea5767: check de emphasis ok.
tea5767: set de emphasis 75us.
tea5767: check de emphasis ok.
tea5767: tea5767_set_clock/tea5767_get_clock test.
tea5767: set clock 13MHz.
tea5767: check clock ok.
tea5767: set clock 6.5MHz.
tea5767: check clock ok.
tea5767: set clock 32.768KHz.
tea5767: check clock ok.
tea5767: tea5767_get_ready_flag test.
tea5767: flag is 0x00.
tea5767: tea5767_get_band_limit_flag test.
tea5767: flag is 0x00.
tea5767: tea5767_get_searched_pll test.
tea5767: pll is 0x3FF9.
tea5767: tea5767_get_if test.
tea5767: if is 0x00.
tea5767: tea5767_get_reception test.
tea5767: reception is 0x00.
tea5767: tea5767_get_level_adc_output test.
tea5767: level adc output is 0x0F.
tea5767: tea5767_frequency_convert_to_register/tea5767_frequency_convert_to_data test.
tea5767: frequency is 89.3.
tea5767: check frequency is 89.3.
tea5767: finish register test.
```

```shell
tea5767 -t radio --crystal=32.768KHz

tea5767: chip is NXP TEA5767.
tea5767: manufacturer is NXP.
tea5767: interface is IIC.
tea5767: driver version is 1.0.
tea5767: min supply voltage is 2.5V.
tea5767: max supply voltage is 5.0V.
tea5767: max current is 10.50mA.
tea5767: max temperature is 75.0C.
tea5767: min temperature is -10.0C.
tea5767: start radio test.
tea5767: band found.
tea5767: searched pll is 0x2A30.
tea5767: searched frequency is 88.73MHz.
tea5767: if is 0x3A.
tea5767: reception is mono.
tea5767: adc output level is 0x08.
tea5767: play 20s.
tea5767: finish radio test.
```

```shell
tea5767 -e init

tea5767: init successful.
```

```shell
tea5767 -e deinit

tea5767: deinit successful.
```

```shell
tea5767 -e up

tea5767: search up successful.
tea5767: frequency is 81.76MHz.
```

```shell
tea5767 -e down

tea5767: search down successful.
tea5767: frequency is 81.76MHz.
```

```shell
tea5767 -e mute

tea5767: mute successful.
```

```shell
tea5767 -e no-mute

tea5767: disable mute successful.
```

```shell
tea5767 -e get

tea5767: frequency is 83.56MHz.
```

```shell
tea5767 -e set --freq=88.73

tea5767: set frequency 88.73MHz.
```

```shell
tea5767 -h

Usage:
  tea5767 (-i | --information)
  tea5767 (-h | --help)
  tea5767 (-p | --port)
  tea5767 (-t reg | --test=reg)
  tea5767 (-t radio | --test=radio) [--crystal=<13MHz | 6.5MHz | 32.768KHz>]
  tea5767 (-e init | --example=init)
  tea5767 (-e deinit | --example=deinit)
  tea5767 (-e up | --example=up)
  tea5767 (-e down | --example=down)
  tea5767 (-e mute | --example=mute)
  tea5767 (-e no-mute | --example=no-mute)
  tea5767 (-e set | --example=set) --freq=<MHz>
  tea5767 (-e get | --example=get)

Options:
      --crystal=<13MHz | 6.5MHz | 32.768KHz>
                          Set the crystal frequence.([default: 32.768KHz])
  -e <init | deinit | up | down | mute | no-mute | set | get>, --example=<init
     | deinit | up | down | mute | no-mute | set | get>
                          Run the driver example.
      --freq=<MHz>        Set the frequence in MHz.
  -h, --help              Show the help.
  -i, --information       Show the chip information.
  -p, --port              Display the pin connections of the current board.
  -t <reg | radio>, --test=<reg | radio>
                          Run the driver test.
```

