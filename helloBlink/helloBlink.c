#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

// static function: its scope limited to the file in which it is declared
static void gpio_setup(void) {

	/* Enable GPIOC clock. */
	rcc_periph_clock_enable(RCC_GPIOC);

	/* Set GPIO8 (in GPIO port C) to 'output push-pull'. */
	gpio_set_mode(
		GPIOC,                           // GPIO port C
		GPIO_MODE_OUTPUT_2_MHZ,		 // How quickly the output GPIO changes its level
		GPIO_CNF_OUTPUT_PUSHPULL,        // Digital outputs configured for push/pull(totem pole)
		GPIO13 				 // GPIO pin 13
	);
}

int main(void) {
	int i;

	gpio_setup();

	for (;;) {
		gpio_clear(GPIOC,GPIO13);	// LED on
		for (i = 0; i < 1500000; i++){	// Wait a bit
			__asm__("nop");         // Force compiler to always produce the loop code and perform the nop instruction(no operation)
		}				

		gpio_set(GPIOC,GPIO13);		// LED off
		for (i = 0; i < 500000; i++){	// Wait a bit
			__asm__("nop");		// Up
		}				
	}

	return 0;
}