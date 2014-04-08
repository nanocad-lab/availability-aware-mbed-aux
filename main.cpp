/* main.cpp
 * Tested with mbed board: FRDM-KL46Z
 * Author: Mark Gottscho
 * mgottscho@ucla.edu
 */
 
#include "mbed.h"

Serial serial1(USBTX, USBRX); //USB-side of bridge
Serial serial2(PTE16, PTE17); //Device-side of bridge
    
void serial1_rx_isr() {
    serial2.putc(serial1.getc());   
}

void serial2_rx_isr() {
    serial1.putc(serial2.getc());   
}

/**
 * Bridge serial traffic from the mbed's UART2
 * to the UART0 which can talk to a
 * PC serial console over USB.
 */
int main() {
    serial1.baud(115200);
    serial2.baud(115200);
    
    serial1.attach(&serial1_rx_isr, Serial::RxIrq);
    serial2.attach(&serial2_rx_isr, Serial::RxIrq);
    
    while (1) { } //spinloop
}