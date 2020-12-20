#ifndef FZETTA_FMC_INIT_TABLE_H_
#define FZETTA_FMC_INIT_TABLE_H_

#include <stdio.h>
#include "xparameters.h"

typedef enum{
	IIC_Dev = 0,
	SPI_Dev
}fzetta_dev_type;

typedef struct {
	fzetta_dev_type dev;
	u8 				channel;
	spi_slave_sel 	slave_sel;
	u8 				regaddr;
	u8 				regdata;
}fzetta_fmc_reglist;

#define REGLIST_SIZE 25

typedef struct {
	u8 gpio_dev_id;
	u8 iic_dev_id;
	u8 spi_dev_id;
	fzetta_fmc_reglist reglist[REGLIST_SIZE];
}fzetta_fmc_reg;

fzetta_fmc_reglist rclkr_errata_id_80[2];
fzetta_fmc_reglist rclkr_errata_id_81[5];
fzetta_fmc_reglist rclkr_errata_id_82[3];
fzetta_fmc_reglist rcvr_errata_id_01[5];

fzetta_fmc_reg fzetta_fmc_table;

void fzetta_fmc_table_init();

#endif /* FZETTA_FMC_INIT_TABLE_H_ */
