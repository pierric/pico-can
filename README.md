An example of how to build a app on Pico that uses [can2040](https://github.com/KevinOConnor/can2040).

Note on some hard-coded numbers:
- bitrate = 25000
- gpio_rx = 20, Pico GPIO 20 <--> CRX of the canbus transceiver module
- gpio_tx = 21, Pico GPIO 21 <--> CTX of the canbus transceiver module
