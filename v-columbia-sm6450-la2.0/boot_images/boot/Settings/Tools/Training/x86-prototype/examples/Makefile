
all: libdtbextn example tlmm-example list-access struct-access phandle-access adc packed-struct compatible adversarial cache slice

clean:
	rm -f *.o
	rm -f libdtbextn.a
	rm -f *.cpp
	rm -f example
	rm -f tlmm-example
	rm -f list-access
	rm -f struct-access
	rm -f phandle-access
	rm -f packed-struct
	rm -f compatible
	rm -f adversarial
	rm -f adc
	rm -f cache
	rm -f slice
	rm -f core.*
	rm -f *.dtb
	rm -f $(QCOM_PATH)/Library/DTBExtnLib/*.o

QCOM_PATH = ../../../../../QcomPkg
DFLAGS = -DBUILD_X86 -DPORT_ARMv8 -DINSTRUMENTATION
CPPFLAGS = -ggdb $(DFLAGS) -I. -I../oss-dtc/libfdt -I$(QCOM_PATH)/Include/Library -I$(QCOM_PATH)/Library/DTBExtnLib

libdtbextn: $(QCOM_PATH)/Library/DTBExtnLib/DTBExtnLib_blob.o \
$(QCOM_PATH)/Library/DTBExtnLib/DTBExtnLib_node.o \
$(QCOM_PATH)/Library/DTBExtnLib/DTBExtnLib_prop.o \
$(QCOM_PATH)/Library/DTBExtnLib/DTBExtnLib_driver.o \
$(QCOM_PATH)/Library/DTBExtnLib/DTBHexDump.o
	ar rcs libdtbextn.a $(QCOM_PATH)/Library/DTBExtnLib/*.o

example: libdtbextn example.o main.o
	gcc -o example main.o example.o -L. -ldtbextn -lfdt

cache: libdtbextn cache.o main.o
	gcc -o cache main.o cache.o -L. -ldtbextn -lfdt

adc: libdtbextn adc.o main.o
	gcc -o adc main.o adc.o -L. -ldtbextn -lfdt

adversarial: libdtbextn adversarial.o main.o
	gcc -o adversarial main.o adversarial.o -L. -ldtbextn -lfdt

compatible: libdtbextn compatible.o main.o
	gcc -o compatible main.o compatible.o -L. -ldtbextn -lfdt

list-access: libdtbextn list-access.o main.o
	gcc -o list-access main.o list-access.o -L. -ldtbextn -lfdt

struct-access: libdtbextn struct-access.o main.o
	gcc -o struct-access main.o struct-access.o -L. -ldtbextn -lfdt

packed-struct: libdtbextn packed-struct.o main.o
	gcc -o packed-struct main.o packed-struct.o -L. -ldtbextn -lfdt

phandle-access: libdtbextn phandle-access.o main.o
	gcc -o phandle-access main.o phandle-access.o -L. -ldtbextn -lfdt

tlmm-example: libdtbextn tlmm-example.o main.o
	gcc -o tlmm-example main.o tlmm-example.o -L. -ldtbextn -lfdt

slice: libdtbextn slice.o main.o
	gcc -o slice main.o slice.o -L. -ldtbextn -lfdt
