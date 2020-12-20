#ifndef FZETTA_FMC_SPI_H_
#define FZETTA_FMC_SPI_H_

#include <stdio.h>
#include "xspi.h"

XSpi_Config *fzetta_fmc_Spi_ConfigPtr;	/* Pointer to Configuration data */
XSpi fzetta_fmc_Spi; /* The instance of the SPI device */

typedef enum{
	SPI_RCLKR = 0x01,
	SPI_DRVR  = 0x02,
	SPI_RCVR  = 0x04,
	DUMMY     = 0xFF
}spi_slave_sel;

#define SPI_WR       0x00
#define SPI_RD       0x80
#define SPI_DUMMY    0xFF

int fzetta_fmc_spi_init(u8 Dev_ID);

int fzetta_fmc_spi_devices_register_write(spi_slave_sel Slave_Sel, u8 RegAddr, u8 RegData);

u8 fzetta_fmc_spi_devices_register_read(u32 Slave_Sel, u8 RegAddr);

#endif /* FZETTA_FMC_SPI_H_ */
