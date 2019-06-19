
/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "utils/commandline.h"
#include <usb/usb_stm32.h>
#include <usb/usb_device_class_audio.h>
#include <usb/usb_device_class_cdc_vcp.h>
#include <usb/usb_device_class_cdc_rndis.h>
#include <utils/io_pin_stm32.h>
#include <utils/serialnumber.h>
#include <utils/interrupt_stm32.h>

extern "C"{
#include "usb_dcd_int.h"
#include "usb_hcd_int.h"
}

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

extern CommandLine cmdline;

IO_Pin_STM32 USB_DP(IO_Pin::IO_Pin_Mode_SPECIAL, GPIOA, GPIO_Pin_11, GPIO_PuPd_NOPULL, GPIO_OType_PP, GPIO_AF_OTG_FS);
IO_Pin_STM32 USB_DM(IO_Pin::IO_Pin_Mode_SPECIAL, GPIOA, GPIO_Pin_12, GPIO_PuPd_NOPULL, GPIO_OType_PP, GPIO_AF_OTG_FS);

uint8_t USB_DEVICE_CLASS::_numinterfaces=0;
uint8_t USB_DEVICE_CLASS::_numinendpoints=1;
uint8_t USB_DEVICE_CLASS::_numoutendpoints=1;
uint8_t USB_DEVICE_CLASS::_numdescriptorstrings=6;
std::list<USB_DEVICE_CLASS*> USB_DEVICE_CLASS::_usb_device_classes_list;

USB_DEVICE_CLASS_CDC_RNDIS usb_device_class_cdc_rndis(0);
USB_DEVICE_CLASS_CDC_VCP usb_device_class_cdc_vcp(1);
USB_DEVICE_CLASS_AUDIO usb_device_class_audio(0);


USB_STM32 usb(0x29BC, 0x0002, "IME", "Microcontroladores 2017", SerialNumberGetHexaString());

INTERRUPT_STM32 usb_otg_fs_interrupt(OTG_FS_IRQn, 0x0D, 0x0D, ENABLE);

int j,i;
int main(void)
{
	usb.Init();
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

	/* Turn on LEDs */
	STM_EVAL_LEDOn(LED3);
	STM_EVAL_LEDOn(LED4);
	STM_EVAL_LEDOn(LED5);
	STM_EVAL_LEDOn(LED6);

	/* Infinite loop */
	CircularBuffer<uint8_t> buffer(0,1024);
	while (1)
	{
		uint16_t size=usb_device_class_cdc_vcp.GetData(buffer,256);
		if(size) {
			cmdline.In(buffer);
		}

		uint8_t buffer[32];
		do{
			size=cmdline.Out(buffer, 32);
			if(size){
				usb_device_class_cdc_vcp.SendData(buffer, size);
			}
		} while(size==32);
		if(j==1){
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
		else if (j ==0)
				{
				STM_EVAL_LEDOff(LED3);
				STM_EVAL_LEDOff(LED4);
				STM_EVAL_LEDOff(LED5);
				STM_EVAL_LEDOff(LED6);
				}
	}
}

extern USB_OTG_CORE_HANDLE USB_OTG_dev;
extern "C" void OTG_FS_IRQHandler(void){
	USBD_OTG_ISR_Handler (&USB_OTG_dev);
	USBH_OTG_ISR_Handler (&USB_OTG_dev);
}

extern "C" void OTG_FS_WKUP_IRQHandler(void){
	if(USB_OTG_dev.cfg.low_power){
		*(uint32_t *)(0xE000ED10) &= 0xFFFFFFF9 ;
		SystemInit();
		USB_OTG_UngateClock(&USB_OTG_dev);
	}
	EXTI_ClearITPendingBit(EXTI_Line18);
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
