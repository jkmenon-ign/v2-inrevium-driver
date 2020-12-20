#include <stdio.h>
#include "xparameters.h"
#include "fzetta_fmc_ctlr.h"
#include "fzetta_fmc_init_table.h"

/*
 * Initialize CfgPtr and Device for FZetta Control
 */
int fzetta_fmc_ip_init(){
	int Status = XST_SUCCESS;

	Status |= fzetta_fmc_gpio_init(fzetta_fmc_table.gpio_dev_id);
	Status |= fzetta_fmc_iic_init(fzetta_fmc_table.iic_dev_id);
	Status |= fzetta_fmc_spi_init(fzetta_fmc_table.spi_dev_id);

	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	return XST_SUCCESS;
}

/*
 * Perform register write according to FMC device type to access
 * @params:
 * 		Dev 		= device type (IIC_Dev or SPI_Dev)
 * 		Channel 	= SDI Channel to access
 * 		Slave_Sel	= SPI slave type (SPI_RCLKR, SPI_DRVR, SPI_RCVR)
 * 		RegAddr     = 7-bit register to access
 * 		RegData		= data to write
 */
int fzetta_fmc_register_write(fzetta_dev_type *Dev, u8 *Channel, spi_slave_sel *Slave_Sel, u8 *RegAddr, u8 *RegData){
	int Status = XST_SUCCESS;

	if (*Dev == IIC_Dev){
		Status |= fzetta_fmc_iic_xbar_register_write(*RegAddr, *RegData);
	}
	else if (*Dev == SPI_Dev){
		Status |= fzetta_fmc_spi_channel_select(*Channel);
		Status |= fzetta_fmc_spi_devices_register_write(*Slave_Sel, *RegAddr, *RegData);
	}
	else {
		return XST_FAILURE;
	}

	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	return XST_SUCCESS;
}

/*
 * Perform register read according to FMC device type to access
 * @params:
 * 		Dev 		= device type (IIC_Dev or SPI_Dev)
 * 		Channel 	= SDI Channel to access
 * 		Slave_Sel	= SPI slave type (SPI_RCLKR, SPI_DRVR, SPI_RCVR)
 * 		RegAddr     = 7-bit register to access
 *
 * 		return      = register data
 */
u8 fzetta_fmc_register_read(fzetta_dev_type Dev, u8 Channel, spi_slave_sel Slave_Sel, u8 RegAddr){
	int Status = XST_SUCCESS;
	u8 RegData;

	if (Dev == IIC_Dev){
		RegData= fzetta_fmc_iic_xbar_register_read(RegAddr);
	}
	else if (Dev == SPI_Dev){
		Status |= fzetta_fmc_spi_channel_select(Channel);
		RegData = fzetta_fmc_spi_devices_register_read(Slave_Sel, RegAddr);
	}
	else
		return XST_FAILURE;

	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	return RegData;
}

/*
 * Perform FZETTA FMC IIC and SPI devices Initialization
 * based on the initialization table
 */
int fzetta_fmc_dev_init(fzetta_fmc_reg *fzetta_fmc_reg_init){
	int i;
	int Status = XST_SUCCESS;

    for (i = 0; i < sizeof(fzetta_fmc_reg_init->reglist)/sizeof(fzetta_fmc_reglist); i++) {
    	Status |= fzetta_fmc_register_write(&fzetta_fmc_reg_init->reglist[i].dev, &fzetta_fmc_reg_init->reglist[i].channel, \
    							  &fzetta_fmc_reg_init->reglist[i].slave_sel, &fzetta_fmc_reg_init->reglist[i].regaddr, \
    							  &fzetta_fmc_reg_init->reglist[i].regdata);
    }

    if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

    //Indicate init done by setting bit7 of GPIO out reg
    //fzetta_fmc_init_done();
    xil_printf("General Fidus FMC Initialization Done\n\r");
	return XST_SUCCESS;

}

/*
 * Perform FZETTA FMC IIC and SPI devices Initialization
 * based on the initialization table
 */
int fzetta_fmc_dev_errata_init(){
	int i;
	u8 ch, dev_id;
	int Status = XST_SUCCESS;

	for(ch=0; ch<4; ch++){

		/*
		 * Reclocker Errata Initialization
		 */

		//Get Reclocker Device ID/Version
		dev_id = fzetta_fmc_register_read(SPI_Dev, ch, SPI_RCLKR, DEV_ID_REG);
		switch (dev_id) {
			case 0x80: //M23145G-11P
				for (i = 0; i < sizeof(rclkr_errata_id_80)/sizeof(fzetta_fmc_reglist); i++) {
					Status |= fzetta_fmc_register_write(&rclkr_errata_id_80[i].dev, &ch, \
							                            &rclkr_errata_id_80[i].slave_sel, &rclkr_errata_id_80[i].regaddr, \
							                            &rclkr_errata_id_80[i].regdata);
				}
				break;

			case 0x81: //M23145G-12P
				for (i = 0; i < sizeof(rclkr_errata_id_81)/sizeof(fzetta_fmc_reglist); i++) {
					Status |= fzetta_fmc_register_write(&rclkr_errata_id_81[i].dev, &ch, \
							                            &rclkr_errata_id_81[i].slave_sel, &rclkr_errata_id_81[i].regaddr, \
							                            &rclkr_errata_id_81[i].regdata);
				}
				break;

			case 0x82: //M23145G-13P
				for (i = 0; i < sizeof(rclkr_errata_id_82)/sizeof(fzetta_fmc_reglist); i++) {
					Status |= fzetta_fmc_register_write(&rclkr_errata_id_82[i].dev, &ch, \
							                            &rclkr_errata_id_82[i].slave_sel, &rclkr_errata_id_82[i].regaddr, \
							                            &rclkr_errata_id_82[i].regdata);
				}
				break;

			default:
				xil_printf("Channel %d No Errata for Reclocker Dev ID (0x%02x)\r\n",ch, dev_id);
		}

		//Actual Register Initiliazation Routine
	    if (Status == XST_SUCCESS) {
			xil_printf("Channel %d Reclocker Errata Init Done (Dev ID 0x%02x)\n\r", ch, dev_id);
		}

		/*
		 * Receiver Errata Initialization
		 */

		//Get Receiver Device ID/Version
	    dev_id = fzetta_fmc_register_read(SPI_Dev, ch, SPI_RCVR, DEV_ID_REG);
		switch (dev_id) {
			case 0x01: //M23544G-12P
				for (i = 0; i < sizeof(rcvr_errata_id_01)/sizeof(fzetta_fmc_reglist); i++) {
					Status |= fzetta_fmc_register_write(&rcvr_errata_id_01[i].dev, &ch, \
							                            &rcvr_errata_id_01[i].slave_sel, &rcvr_errata_id_01[i].regaddr, \
							                            &rcvr_errata_id_01[i].regdata);
				}
				break;

			default:
				xil_printf("Channel %d No Errata for Receiver Dev ID (0x%02x)\r\n", ch, dev_id);
		}
	    if (Status == XST_SUCCESS) {
			xil_printf("Channel %d Receiver Errata Init Done (Dev ID 0x%02x)\n\r", ch, dev_id);
		}

	}

    if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

    //Indicate init done by setting bit7 of GPIO out reg
    fzetta_fmc_init_done();
	return XST_SUCCESS;

}


/*
 * Stop IIC, GPIO and SPI IP
 */
int fzetta_fmc_stop(){
	int Status = XST_SUCCESS;

	Status |= XSpi_Stop(&fzetta_fmc_Spi);

    if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	return XST_SUCCESS;

}

/*
 * Initialize FMC and its control IPs
 */
int fzetta_fmc_init(){
   int Status = XST_SUCCESS;

   fzetta_fmc_table_init();
   Status |= fzetta_fmc_ip_init();
   Status |= fzetta_fmc_dev_init(&fzetta_fmc_table);
   Status |= fzetta_fmc_dev_errata_init();
   //Status |= fzetta_fmc_stop();
   if (Status != XST_SUCCESS) {
		return XST_FAILURE;
   }
   return XST_SUCCESS;
}
