// UART Driver

#include "stm32f4xx.h"
#include "Sys_Clock_Config.h"
#include "GPIO_Config.h"
#include "Delay.h"
#include "uart.h"

int main(void) {
	Sys_Clock_Config();
	TIM3_Config();
	GPIO_Config();
	USART2_config();

	while(1) {
		
		//USART2_send_char('G');
		//USART2_send_string("Hello World\n");
		uint8_t data = USART2_get_char();
		USART2_send_char(data);
		//Delay_ms(1000);
		/*
		// if button is not pressed, light LED
		if (GPIOC->IDR){ 						
			GPIOA->BSRR |= (1<<5);
			Delay_ms(500);
			GPIOA->BSRR |= (1<<21);
			Delay_ms(500);
		}
		*/
		
	}
	
}	