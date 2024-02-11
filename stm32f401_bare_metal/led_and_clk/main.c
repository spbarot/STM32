
#include "stm32f4xx.h"

#define PLLM 16
#define PLLN 192
#define PLLP 1 // PLLP = 4;

void static Sys_Clock_Config(void) {
	
	// 1) enable HSE
	RCC->CR |= RCC_CR_HSEON; 
	while (!(RCC->CR & RCC_CR_HSERDY)); 
	
	// 2) set power enable clock and voltage regulator
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	PWR->CR |= PWR_CR_VOS;

	// 3) configure flash
	FLASH->ACR |= FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_5WS;
	
	// 4) configure prescalars
	// AHB 
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
	// APB1 
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV1; 
	// APB2
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;
	
	// 5) configure pll
	// pllm
	RCC->PLLCFGR |= PLLM << 0;
	//PLLN
	RCC->PLLCFGR |= PLLN << 6; 
	//PLLP
	RCC->PLLCFGR |= PLLP << 16; 
	//HSE source
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE;
	
	// 6) enable PLL and wait for ready
	RCC->CR |= RCC_CR_PLLON;
	while (!(RCC->CR & RCC_CR_PLLRDY));
	
	// 7) select the clock source - pll
	RCC->CFGR |= RCC_CFGR_SW_PLL; 
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}

void static GPIO_Config(void) {

	// 1) enable gpio clock
	RCC->AHB1ENR |= (1<<0);
	
	// 2) set pin as output
	GPIOA->MODER |= (1<<10);

	// 3) set pin output type
	GPIOA->OTYPER = 0; 
	GPIOA->OSPEEDR = 0;

}

void static delay(uint32_t time) {
	while (time--);
}

int main(void) {
	Sys_Clock_Config();
	GPIO_Config();
	
	
	while(1) {
		GPIOA->BSRR |= 1<<5; // set pin PA5
		delay(100000);
		GPIOA->BSRR |= 1<<21; // reset pin PA5
		delay(100000);
	}
	
//return 0;
}	