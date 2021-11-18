# wbb-uinput

Creates a uinput controller with the inputs of the Wii Balance Board. No drivers or other programs needed. Works on Raspberry Pis too.

# Prerequisites
Connect the Wii Balance Board via Bluetooth. If the blue light stays on the Board is connected. Use `ls /dev/input` to find out which one the board is. It should be the /dev/input/event* with the highest number e.g. `/dev/input/event23`. Compile (e.g. `c99 wbb-uinput.c -o c99 wbb-uinput`) or use a binary from the release.

# Usage
Run it with the path specified in stdin e.g. `./wbb-uinput /dev/input/event23`. It works correctly if the values of the x and y axis get output to the terminal. Use AntiMicroX or other programs to configure the inputs to be seen as joystick, mouse or keyboard inputs.


# Permission error
See https://wiki.archlinux.org/title/Wiimote#Unable_to_open_uinput (or running as root might do?)

Modified code from https://github.com/keldu/WiiWeight
and https://github.com/GrantEdwards/uinput-joystick-demo
