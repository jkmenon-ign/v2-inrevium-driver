#ifndef FZETTA_FMC_CTLR_H_
#define FZETTA_FMC_CTLR_H_

#include <stdio.h>
#include "xparameters.h"
#include "fzetta_fmc_gpio.h"
#include "fzetta_fmc_iic.h"
#include "fzetta_fmc_spi.h"
#include "fzetta_fmc_init_table.h"
#include "fzetta_fmc_ctlr.h"

#define DEV_ID_REG 0x01

int fzetta_fmc_ip_init();

int fzetta_fmc_register_write(fzetta_dev_type *Dev, u8 *Channel, spi_slave_sel *Slave_Sel, u8 *RegAddr, u8 *RegData);

u8 fzetta_fmc_register_read(fzetta_dev_type Dev, u8 Channel, spi_slave_sel Slave_Sel, u8 RegAddr);

int fzetta_fmc_dev_init(fzetta_fmc_reg *fzetta_fmc_reg_init);

int fzetta_fmc_dev_errata_init();

int fzetta_fmc_stop();

int fzetta_fmc_init();

#endif /* FZETTA_FMC_CTLR_H_ */
