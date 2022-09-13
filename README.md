# Hello ESP32 Audiokit

## Hardware

Based on [ESP32-A1S-AudioKit](https://docs.ai-thinker.com/en/esp32-audio-kit)
In oreder to flash the device, connect the microusb UART port, not the power.
In device manager appear a COM7 connection, also visible inside the platformIO devices.
The connection is a bridge usb to uart.

## Dependencies

- https://github.com/pschatzmann/arduino-audio-tools/tree/v0.8.7
- https://github.com/pschatzmann/arduino-audiokit/tree/v0.6.0
- https://github.com/pschatzmann/arduino-libhelix/tree/v0.7 (mp3 decoder)
- https://github.com/pschatzmann/arduino-libmad/tree/v0.7 (mp3 decoder)


## Issue
The eartphone is not detected and at  the moment only the speaker connection works.