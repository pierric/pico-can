#include <stdio.h>
#include <pico/stdlib.h>

extern "C" {
 #include "can2040.h"
}

static struct can2040 cbus;

static void PIOx_IRQHandler(void)
{
    can2040_pio_irq_handler(&cbus);
}

static void can2040_cb(struct can2040 *cd, uint32_t notify, struct can2040_msg *msg)
{
    // Add message processing code here...
    printf("msg: %x [%x]", msg->id, msg->dlc);
    for (int i=0; i<8; i++) {
        printf(" %02x", msg->data[i]);
    }
    printf("\n");
}

void canbus_setup(void)
{
    uint32_t pio_num = 0;
    uint32_t sys_clock = 125000000, bitrate = 25000;
    uint32_t gpio_rx = 20, gpio_tx = 21;

    // Setup canbus
    can2040_setup(&cbus, pio_num);
    can2040_callback_config(&cbus, can2040_cb);

    // Enable irqs
    irq_set_exclusive_handler(PIO0_IRQ_0, PIOx_IRQHandler);
    irq_set_priority(PIO0_IRQ_0, 1);
    irq_set_enabled(PIO0_IRQ_0, true);

    // Start canbus
    can2040_start(&cbus, sys_clock, bitrate, gpio_rx, gpio_tx);
}

static can2040_msg cmsg = {
    .id = 0x223,
    .dlc = 8,
    .data32 = {0, 1},
};

int main() {
    int rc, flg=0;
    stdio_init_all();
    canbus_setup();

    while (true) {
        char c = flg?'\\':'/';
        flg=1-flg;
        printf("%c\r", c);
        //rc = can2040_transmit(&cbus, &cmsg);
        //if (rc < 0) {
        //    printf("failed to send the canbus message.\n");
        //}
        sleep_ms(1000);
    }
}
