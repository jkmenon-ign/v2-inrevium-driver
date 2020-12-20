#include <stdio.h>
#include "xgpio.h"
#include "fzetta_fmc_gpio.h"

XGpio fzetta_fmc_GpioOutput; /* The driver instance for GPIO Device configured as O/P */
unsigned char fmc_init_done_flag = 0;


/*
 * Initialize GPIO IP and set all IO direction to output
 */
int fzetta_fmc_gpio_init(u8 Dev_ID){
	int Status;
	/*
	 * Initialize the GPIO driver so that it's ready to use,
	 * specify the device ID that is generated in xparameters.h
	 */
//	 Status = XGpio_Initialize(&fzetta_fmc_GpioOutput, Dev_ID);
	 Status = xgpio_initialize(&fzetta_fmc_GpioOutput, "xgpio");
	 if (Status != XST_SUCCESS)  {
		  return XST_FAILURE;
	 }

	 /*
	  * Set the direction for all signals to be outputs
	  */
	 XGpio_SetDataDirection(&fzetta_fmc_GpioOutput, 1, 0x0);

	 return XST_SUCCESS;
}

/*
 * Set 4-Channel MUX in FMC according to target channel
 * GPIO[1:0] 	00 - Chan0
 * 				01 - Chan1
 * 				10 - Chan2
 * 				11 - Chan3
 */
int fzetta_fmc_spi_channel_select(u8 Channel) {
	if (Channel > 3) {
		  return XST_FAILURE;
	}

	XGpio_DiscreteWrite(&fzetta_fmc_GpioOutput, 1, fmc_init_done_flag | Channel);

	 return XST_SUCCESS;
}

/*
 * Set bit7 of GPIO to 1 to declare init done

 */
void fzetta_fmc_init_done() {
	fmc_init_done_flag = 0x80;
	XGpio_DiscreteWrite(&fzetta_fmc_GpioOutput, 1, fmc_init_done_flag);
}
