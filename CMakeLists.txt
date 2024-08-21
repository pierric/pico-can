cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(canbus)

pico_sdk_init()

add_executable(canbus
    src/can2040.c
    src/main.cpp
)
target_include_directories(canbus PRIVATE include/)
pico_enable_stdio_usb(canbus 1)
pico_enable_stdio_uart(canbus 0)

target_link_libraries(canbus pico_stdlib cmsis_core hardware_pio hardware_irq)
pico_add_extra_outputs(canbus)
