
/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */

/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{
  int i = 0;


  /**
  *  IMPORTANT NOTE!
  *  The symbol VECT_TAB_SRAM needs to be defined when building the project
  *  if code has been located to RAM and interrupts are used.
  *  Otherwise the interrupt table located in flash will be used.
  *  See also the <system_*.c> file and how the SystemInit() function updates
  *  SCB->VTOR register.
  *  E.g.  SCB->VTOR = 0x20000000;
  */

  /* TODO - Add your application code here */

  /* Initialize LEDs */
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED5);
  STM_EVAL_LEDInit(LED6);

  /* Spin LEDs */
  while(1)
  {
	  i=9000000;
	  STM_EVAL_LEDOn(LED3);
  	  while(i){
  		  i--;
  	  }
  	  STM_EVAL_LEDOff(LED3);

	  i=9000000;
	  STM_EVAL_LEDOn(LED4);
	  while(i){
		  i--;
	  }
	  STM_EVAL_LEDOff(LED4);


	  i=9000000;
	  STM_EVAL_LEDOn(LED6);
	  while(i){
		  i--;
	  }
	  STM_EVAL_LEDOff(LED6);

	  i=9000000;
	  STM_EVAL_LEDOn(LED5);
	  while(i){
		  i--;
	  }
	  STM_EVAL_LEDOff(LED5);

  }
}


/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
extern "C" void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
extern "C" uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}

