/*
 * main.c
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xparameters.h"
#include "../fzetta_fmc/fzetta_fmc_ctlr.h"


//global variable
unsigned char inchar;
char slv_type[9];
unsigned char IsValid = 0;
unsigned int State;
//unsigned int Channel;

fzetta_dev_type dev;
u8 				channel;
spi_slave_sel 	slave_sel;
u8 				regaddr;
u8 				regdata;


#if 0
void slave_StringCopy(char *StrOut, spi_slave_sel slave_sel)
{
	switch(slave_sel){
		case SPI_RCLKR:
			strcpy(StrOut, "SPI_RCLKR");
			break;

		case SPI_DRVR:
			strcpy(StrOut, "SPI_DRVR");
			break;

		case SPI_RCVR:
			strcpy(StrOut, "SPI_RCVR");
			break;

		default:
			strcpy(StrOut, "DUMMY");
			break;
	}
}


void ctrl_main_menu(unsigned char IsValid)
{
	if(IsValid == 0) return;
		printf("\n\r");
		printf("-----------------------\n\r");
		printf("--  FIDUS Main Menu  --\n\r");
		printf("-----------------------\n\r");
		printf("\n\r");
		printf(" Select option\n\r");
		printf(" 1 = Re-Init \n\r");
		printf(" 2 = IIC Dev Select \n\r");
		printf(" 3 = SPI CH0 Select \n\r");
		printf(" 4 = SPI CH1 Select \n\r");
		printf(" 5 = SPI CH2 Select \n\r");
		printf(" 6 = SPI CH3 Select \n\r");
		printf(" ? = help \n\r");
		printf("------------------\n\r");
		printf(">");
}

void ctlr_spi_slv_select_menu(unsigned char IsValid)
{
	if(IsValid == 0) return;
		printf("\n\r");
		printf("-----------------------\n\r");
		printf("-- CH%d Slave Select  --\n\r", channel);
		printf("-----------------------\n\r");
		printf("\n\r");
		printf(" Select option\n\r");
		printf(" 1 = SPI Receiver \n\r");
		printf(" 2 = SPI Re-Clocker \n\r");
		printf(" 3 = SPI Driver \n\r");
		printf(" m = Main Menu \n\r");
		printf(" ? = help \n\r");
		printf("------------------\n\r");
		printf(">");
}

/**
 * Main control for Fidus FMC register configuration
 */
void ctrl_app(unsigned char inchar){
	switch (State){
      case 0: //Main Menu
    	  ctrl_main_menu(IsValid);
    	  switch (inchar){
          	  case '1' :
          		  fzetta_fmc_init();
				  State = 0;
          		  IsValid = 1;
          		  break;

          	  case '2' : // IIC Dev
          		  dev = IIC_Dev;
          		  channel = DUMMY;
				  slave_sel = DUMMY;
				  State = 2;
          		  IsValid = 1;
          		  break;

			  case '3' : // SPI Dev Ch0
			      dev = SPI_Dev;
			      channel = 0;
				  State = 1;
          		  IsValid = 1;
				  break;

			  case '4' : // SPI Dev Ch1
			      dev = SPI_Dev;
			      channel = 1;
				  State = 1;
          		  IsValid = 1;
				  break;

			  case '5' : // SPI Dev Ch2
			      dev = SPI_Dev;
			      channel = 2;
				  State = 1;
          		  IsValid = 1;
				  break;

			  case '6' : // SPI Dev Ch3
			      dev = SPI_Dev;
			      channel = 3;
				  State = 1;
          		  IsValid = 1;
				  break;
          	  case '?' :
          		  IsValid = 1;
          	  	  break;
              case CARRIAGE_RETURN:
            	  IsValid = 0;
            	  break;
          	  default :
          		  printf("Invalid Entry!\n\r");
          		  IsValid = 0;
          		  break;
    	  }
    	  break;


          case 1: //SPI Slave Select Channel
        	  ctlr_spi_slv_select_menu(IsValid);
        	  switch (inchar){
              	  case '1' : // SPI Receiver Select
              		  slave_sel = SPI_RCVR;
					  State = 2;
              		  IsValid = 1;
              		  break;

              	  case '2' : // SPI Re-Clocker Select
              		  slave_sel = SPI_RCLKR;
					  State = 2;
              		  IsValid = 1;
              		  break;

              	  case '3' :
              		  slave_sel = SPI_DRVR;
					  State = 2;
              		  IsValid = 1;
              		  break;

			      case 'm' :
              	  case 'M' :
              		  State = 0;
              		  channel = 99;
              		  IsValid = 1;
              		  break;

                  case CARRIAGE_RETURN:
                	  IsValid = 0;
                	  break;

             	  default :
              		  printf("Invalid Entry!\n\r");
              		  IsValid = 0;
              		  break;
        	  }
        	  break;

          case 2: //Register Read/Write
  			printf("\nEnter E-Exit or Addres: 0x");
			get_input2_val();
            if((get_val[0] == 'E') || (get_val[0] == 'e')) { // Exit
  			      printf("\n");
				  State = (dev == IIC_Dev) ? 0 : 1;
        		  IsValid = 1;
        		  break;
            }
            regaddr = (unsigned int)strtoul(get_val, NULL, 16);
			printf("\nEnter R-Read or Data: 0x");
			get_input2_val();
			slave_StringCopy(&slv_type[0], slave_sel);
			if((get_val[0] == 'R') || (get_val[0] == 'r')) { // READ
			    if (dev == IIC_Dev) {
			        printf("\nCannot Read Registers from IIC Device!\n\r");
			    }
				else {
     			        printf("\n\nREAD  Dev: %s Ch: %d Slave: %s Addr: 0x%02x Data: 0x%02x\n\r", dev?"SPI":"IIC", channel, slv_type, regaddr, fzetta_fmc_register_read(dev, channel, slave_sel, regaddr));
				    //xil_printf("\nReg Val: 0x%02x\n\r", fzetta_fmc_register_read(dev, channel, slave_sel, regaddr));
				}
            }
			else { //WRITE
				   regdata = (unsigned int)strtoul(get_val, NULL, 16);
				   printf("\n\nWRITE Dev: %s Ch: %d Slave: %s Addr: 0x%02x Data: 0x%02x\n\r", dev?"SPI":"IIC", channel, slv_type, regaddr, regdata);
                   fzetta_fmc_register_write(&dev, &channel, &slave_sel, &regaddr, &regdata);
			}
			
		    State = 2;
		    IsValid = 0;
		    break;

      case CARRIAGE_RETURN:
    	  IsValid = 0;
    	  break;

      default :
  		  printf("Invalid Entry!\n\r");
  		  State = 0;
  		  channel = 99;
  		  IsValid = 0;
    	  break;
	}
}
/**
 * Fetch input from UART then callback voip_contrl_app to
 * process the selection
 */
void get_ctrl_app_input(void)
{
	if (!XUartLite_IsReceiveEmpty(STDIN_BASEADDRESS)){
		inchar = (u8)XUartLite_ReadReg(STDIN_BASEADDRESS, XUL_RX_FIFO_OFFSET);
		printf("%c\n\r",inchar);
		ctrl_app(inchar);
		ctrl_app(CARRIAGE_RETURN);
	}
}
#endif

int main(void)
{
	IsValid = 1;
	State = 0;
	//Channel = 99;

   //Xil_ICacheEnable();
   //Xil_DCacheEnable();
   //cls();
   fzetta_fmc_init();


#if 0
   ctrl_app(CARRIAGE_RETURN);
   while (1)
    {
    	get_ctrl_app_input();

    }
#endif
   // Xil_DCacheDisable();
   // Xil_ICacheDisable();
   

   
   return 0;
}


