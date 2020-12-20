#ifndef FZETTA_FMC_GPIO_H_
#define FZETTA_FMC_GPIO_H_

#include <stdio.h>
#include "xgpio.h"

XGpio fzetta_fmc_GpioOutput; /* The driver instance for GPIO Device configured as O/P */

int fzetta_fmc_gpio_init(u8 Dev_ID);

int fzetta_fmc_spi_channel_select(u8 Channel);

void fzetta_fmc_init_done();

#endif /* FZETTA_FMC_GPIO_H_ */
