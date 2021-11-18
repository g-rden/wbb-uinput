# wbb-uinput

Creates a controller with the inputs of the Wii Balance Board. No drivers or other programs needed!!!

# Usage
Connect the Wii Balance Board via Bluetooth. If the blue light stays on the Board is connected. Use `ls /dev/input` to find out which one the board is. It should be the /dev/input/event* with the highest number e.g. `/dev/input/event23`. Compile or use the binary and run it with the path specified in stdin e.g. `./wbb-uinput /dev/input/event23` Use AntiMicroX or other programs to configure the inputs to be seen as joystick, mouse or keyboard inputs.

Modified code from https://github.com/keldu/WiiWeight
and https://github.com/GrantEdwards/uinput-joystick-demo
