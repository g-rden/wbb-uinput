Modified code from [WiiWeight](https://github.com/keldu/WiiWeight) and [uinput-joystick-demo](https://github.com/GrantEdwards/uinput-joystick-demo)

# wbb-uinput
Creates a uinput controller with the inputs of the Wii Balance Board. No other drivers needed. Also runs on Raspberry Pi.

# Prerequisites
Connect the Wii Balance Board via Bluetooth. If the blue light stays on the Board is connected. Use `ls /dev/input` or tab compleation later to find out which one the board is. It should be the /dev/input/event* with the highest number e.g. `/dev/input/event23`. Compile (e.g. `tcc wbb-uinput.c -o wbb-uinput`) or use a binary from the release.

# Usage
Run it with the path specified in stdin e.g. `./wbb-uinput /dev/input/event23`. It works correctly if the values of the x and y axis get output to the terminal. Use AntiMicroX or other programs to configure the inputs to be seen as joystick, mouse or keyboard inputs.

# Permission error
See https://wiki.archlinux.org/title/Wiimote#Unable_to_open_uinput
