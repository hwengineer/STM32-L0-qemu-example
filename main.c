/*********************************************************
* main.c
*
* An example Program
* Blinks one LED with approximate 10Hz
* Additionaly we can test the arm_semihosting capabilites
* It writes "Hello World" to the Debug Console
*
* remind : As long as arm_semihosting code is in the program
* it jumpes to the HardFault_Handler and probably hangs, if
* no debugger is connected
*********************************************************/

#include "main.h"
#include "arm_semi.h"

void LED_Init(void);
void SysTick_Handler(void);
int  main(void);

int main(void) {

  arm_semi_syswritec('\n');            // write a single character
  arm_semi_syswrite0("Hello World\n"); // write a 0-t string

  HAL_Init(); // init hal driver
  LED_Init(); // init led's

  // foreground process
  while (1)
  {
    HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN); // toggle led
    HAL_Delay(100);                             // blocking wait for 100ms
  }
}

void LED_Init() {
  LED_GPIO_CLK_ENABLE();                        // init LED
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = LED_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
}

// background process
void SysTick_Handler(void) {
  HAL_IncTick();            // inc tick_counter
}
