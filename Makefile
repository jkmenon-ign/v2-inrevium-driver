

SUBDIRS = gpio_v4_0 iic_v3_1 spi_v4_1 uartlite_v3_0 test 

.PHONY: subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ 

install:
	$(info D is ${DESTDIR})
	$(info B is ${BUILDDIR})
	mkdir -p ${DESTDIR}/usr/bin
	cp ${BUILDDIR}/test/inrevium-config ${DESTDIR}/usr/bin
