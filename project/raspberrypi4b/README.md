### 1. Chip

#### 1.1 Chip Info

chip name : Raspberry Pi 4B.

iic pin: SCL/SDA GPIO3/GPIO2.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
# open another terminal
./tea5767_server 

# use the CMake terminal
make test
```

Find the compiled library in CMake. 

```cmake
find_package(tea5767 REQUIRED)
```

#### 2.4 How to run

```shell
# open one terminal and run the server
./tea5767_server 
```
```shell
# open another terminal and sent the command
./tea5767 xxx xxx xxx ...
```


### 3. TEA5767

#### 3.1 Command Instruction

​           tea5767 is a basic command which can test all tea5767 driver function:

​           -i        show tea5767 chip and driver information.

​           -h       show tea5767 help.

​           -p       show tea5767 pin connections of the current board.

​           -t  (reg | radio -f (13MHz | 6.5MHz | 32.768KHz))

​           -t reg       run tea5767 register test. 

​           -t radio -f (13MHz | 6.5MHz | 32.768KHz)        run tea5767 radio test.

​           -c basic (-init | -deinit | -up | -down | -mute | -no-mute | -get | -set <freq>)

​           -c basic -init         tea5767 init function.

​           -c basic -deinit         tea5767 deinit function.

​           -c basic -up         tea5767 search up function.

​           -c basic -down         tea5767 search down function.

​           -c basic -mute         tea5767 mute function.

​           -c basic -no-mute         tea5767 disable mute function.

​           -c basic -set <freq>         tea5767 set the frequency function.freq is the set frequency.

​           -c basic -get         tea5767 get the current frequency function.

#### 3.2 Command Example

```shell
./tea5767 -i

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
./tea5767 -p

tea5767: SCL connected to GPIO3(BCM).
tea5767: SDA connected to GPIO2(BCM).
```

```shell
./tea5767 -t reg

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
tea5767: pll is 0x2A00.
tea5767: tea5767_get_if test.
tea5767: if is 0x39.
tea5767: tea5767_get_reception test.
tea5767: reception is 0x00.
tea5767: tea5767_get_level_adc_output test.
tea5767: level adc output is 0x01.
tea5767: tea5767_frequency_convert_to_register/tea5767_frequency_convert_to_data test.
tea5767: frequency is 89.3.
tea5767: check frequency is 89.3.
tea5767: finish register test.
```

```shell
./tea5767 -t radio -f 32.768KHz

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
tea5767: if is 0x3B.
tea5767: reception is stereo.
tea5767: adc output level is 0x0A.
tea5767: play 20s.
tea5767: finish radio test.
```

```shell
./tea5767 -c basic -init

tea5767: init successful.
```

```shell
./tea5767 -c basic -deinit

tea5767: deinit successful.
```

```shell
./tea5767 -c basic -up

tea5767: search up successful.
tea5767: frequency is 88.66MHz.
```

```shell
./tea5767 -c basic -down

tea5767: search down successful.
tea5767: frequency is 87.56MHz.
```

```shell
./tea5767 -c basic -mute

tea5767: mute successful.
```

```shell
./tea5767 -c basic -no-mute

tea5767: disable mute successful.
```

```shell
./tea5767 -c basic -get

tea5767: frequency is 90.56MHz.
```

```shell
./tea5767 -c basic -set 88.73

tea5767: set frequency 88.73MHz.
```

```shell
./tea5767 -h

tea5767 -i
	show tea5767 chip and driver information.
tea5767 -h
	show tea5767 help.
tea5767 -p
	show tea5767 pin connections of the current board.
tea5767 -t reg
	run tea5767 register test.
tea5767 -t radio -f (13MHz | 6.5MHz | 32.768KHz)
	run tea5767 radio test.
tea5767 -c basic -init
	tea5767 init function.
tea5767 -c basic -deinit
	tea5767 deinit function.
tea5767 -c basic -up
	tea5767 search up function.
tea5767 -c basic -down
	tea5767 search down function.
tea5767 -c basic -mute
	tea5767 mute function.
tea5767 -c basic -no-mute
	tea5767 disable mute function.
tea5767 -c basic -set <freq>
	tea5767 set the frequency function.freq is the set frequency.
tea5767 -c basic -get
	tea5767 get the current frequency function.
```

