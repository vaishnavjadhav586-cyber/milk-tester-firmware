#include "stm32f4xx.h" // Include device header for STM32F401RE

void delay(volatile uint32_t count) {
    while (count--) {
        __NOP(); // No operation (burns cycles)
    }
}

int main(void) {
    // 1. Enable clock for GPIOA in RCC (Reset and Clock Control)
    // AHB1ENR register, bit 0 controls GPIOA clock
    RCC->AHB1ENR |= (1 << 0);

    // 2. Configure PA5 as General Purpose Output Mode
    // MODER5[1:5] bits: 01 = Output mode (clear bits 10 and 11 first, then set bit 10)
    GPIOA->MODER &= ~(3 << (5 * 2)); // Clear mode bits for PA5
    GPIOA->MODER |=  (1 << (5 * 2)); // Set to output mode (01)

    while (1) {
        // 3. Set PA5 High (Turn LED ON)
        // ODR (Output Data Register), bit 5
        GPIOA->ODR |= (1 << 5);
        delay(500000); // Simple software delay

        // 4. Set PA5 Low (Turn LED OFF)
        GPIOA->ODR &= ~(1 << 5);
        delay(500000); // Simple software delay
    }

    return 0;
}
