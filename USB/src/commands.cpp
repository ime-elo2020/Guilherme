#include "utils/commandline.h"
#include "stm32f4_discovery.h"

extern CommandLine cmdline;
extern int j;


uint16_t cmd_info(uint16_t argc, uint8_t *argv8[]){
	const char **argv=(const char **)argv8;
	uint16_t size=0;
	char* buffer=(char*)argv[0];

	if(argc==1){
		size+=sprintf(buffer+size, "Os leds giram!\r\n");
		j = j^1;
	} else {
		size+=sprintf(buffer+size, "Syntax: info\r\n");
	}
	return size;
}


CommandLine cmdline({"gira"},
					{cmd_info});
