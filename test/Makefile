APP = inrevium-config

APP_OBJS = fzetta_fmc_ctlr.o fzetta_fmc_gpio.o fzetta_fmc_spi.o fzetta_fmc_iic.o fzetta_fmc_init_table.o 

INCLUDE=-I. -I../include

LINKLIBS= -L../lib/
#LINKLIBS += -L./usr/lib/

CFLAGS = -D _GNU_SOURCE

all: $(APP)

$(APP): sdi_app.o fzetta_fmc_ctlr.o fzetta_fmc_gpio.o fzetta_fmc_spi.o fzetta_fmc_iic.o fzetta_fmc_init_table.o
	$(CC) $(INCLUDE) -o inrevium-config sdi_app.o fzetta_fmc_ctlr.o fzetta_fmc_gpio.o fzetta_fmc_spi.o fzetta_fmc_iic.o fzetta_fmc_init_table.o $(LINKLIBS) -lxgpio -lxspi -lxiic -lxuart

fzetta_fmc_ctlr.o: fzetta_fmc_ctlr.c
	$(CC) -c  $(INCLUDE) fzetta_fmc_ctlr.c $(LINKLIBS) -lxgpio -lxspi -lxiic -lxuart

fzetta_fmc_gpio.o: fzetta_fmc_gpio.c
	$(CC) -c  $(INCLUDE) fzetta_fmc_gpio.c $(LINKLIBS) -lxgpio -lxspi -lxiic -lxuart

fzetta_fmc_spi.o: fzetta_fmc_spi.c
	$(CC) -c  $(INCLUDE) fzetta_fmc_spi.c $(LINKLIBS) -lxgpio -lxspi -lxiic -lxuart

fzetta_fmc_iic.o: fzetta_fmc_iic.c
	$(CC) -c  $(INCLUDE) fzetta_fmc_iic.c $(LINKLIBS) -lxgpio -lxspi -lxiic -lxuart

clean:
	rm -rf *.o $(APP) $(APP_OBJS)
