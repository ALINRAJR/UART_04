/*
===============================================================================
 Name        : 29_Day63_18112021_UART004.c

 Description : Program to demonstrate the UART0 Reception and Transmission using interrupt method
 	 	 	   and software queue

   TESTCASE0 : For checking the program with interrupts and with swqueue
   TESTCASE1 : For checking the program without interrupts and without swqueue

 	 	 	   Hint :-
 ucswqueueread(&uart0rxqueueobj,<your variable address>);-> To be called from
 main

 ucswqueuewrite(&uart0txqueueobj,<your variable address>); -> To be called from
 vUARTCallbackHandler

 Layered Architecture used for this project
 ************************************
 Application layer-29_Day63_18112021_UART004.c
 ************************************
 Board layer -  configboard.h, led.c/.h
 ************************************
 Low level drivers or chip level - pinmux.c/.h,uart.c/.h, gpio.c/.h
 ************************************
 Hardware
 ************************************
===============================================================================
*/

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
/* Private includes ----------------------------------------------------------*/
#include "pinmux.h"
#include "uart.h"
#include "led.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define TESTCASE0 1
#define TESTCASE1 0

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
const uint8_t Message1[]="TRANSIOT EMBEDDDED SYSTEM PROFESSIONAL TRAINING\r\n";
const uint8_t Message2[]="DEMONSTRATION OF SOFTWARE QUEUE IN UART\r\n";
/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

/**
  * @brief  Initialize all the hardware connected
  * @retval none
  */
void vAppHardwareInit(void)
{
	vPinmuxInitialize();
	vLedInitialize();
	vUARTInitialize(UART0,UART_0,BAUDRATE_9600);
	/* Attaching the vUARTCallbackHandler function when interrupt occurs in UART0 */
	vUARTIntAttachCallback(UART_0,vUARTCallbackHandler);
}

/**
  * @brief  Crude Delay
  * @retval none
  */
void vAppDelay(uint32_t count)
{
	int i,j;
	for(i=0;i<count;i++)
		for(j=0;j<0xA00;j++);
}

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/

  /* Initialize all configured peripherals */
   vAppHardwareInit();

#if TESTCASE1
   /*Disabling the transmission interrupt */
   	vUARTInterruptDisable(UART0,THRE_INTERRUPT);
#endif

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)  // for(;;)
  {
#if TESTCASE1
	  vUARTPutStringBlocking(UART0,Message1);
	  vUARTPutStringBlocking(UART0,Message2);
#endif
#if TESTCASE0
	  ucUARTSendNonBlocking(UART0,Message1,sizeof Message1);
	  ucUARTSendNonBlocking(UART0,Message2,sizeof Message2);
#endif
		/*vLedOn(LED_0);
		vAppDelay(0x200);
		vLedOff(LED_0);
		vAppDelay(0x200);*/

		vLedToggle(LED_0);
		//vLedToggle(LED_1);



  }
  /* End of Application entry point */
}



