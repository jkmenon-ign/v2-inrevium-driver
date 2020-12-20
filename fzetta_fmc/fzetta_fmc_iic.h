#ifndef FZETTA_FMC_IIC_H_
#define FZETTA_FMC_IIC_H_

#include <stdio.h>
#include "xiic.h"

XIic_Config *fzetta_fmc_Iic_ConfigPtr;	/* Pointer to configuration data */
XIic fzetta_fmc_Iic; /* The driver instance for IIC Device */

#define XBAR_IIC_WRITE_ADDR 0x50

int fzetta_fmc_iic_init(u8 Dev_ID);

int fzetta_fmc_iic_xbar_register_write(u8 RegAddr, u8 RegData);

u8 fzetta_fmc_iic_xbar_register_read(u8 RegAddr);

#endif /* FZETTA_FMC_IIC_H_ */
