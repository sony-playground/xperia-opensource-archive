KEYSTORE_SOURCES=  ../../core/ks/keystore.o
KEYSTORE_SOURCES+= ../../core/ks/rpmbio.o 
KEYSTORE_SOURCES+= ../../core/ks/nvio.o 
KEYSTORE_SOURCES+= ../../core/ks/ksio.o

KEYSTORE_TEST_SOURCES = $(KEYSTORE_SOURCES) test.o test_ks.o
OUT ?= .
OBJDIR=$(OUT)
KEYSTORE_LIBRARY=../../core/ks/generated/libkeystore.a


CFLAGS += -I. -iquote../../core/ks/generated -iquote../../core/include  -I../../core/ks/generated -iquote../../core/ks/include  -ffunction-sections -Wl,--gc-sections -fno-stack-protector -Os -DNDEBUG -Wall -std=c99 -g
OBJS=${KEYSTORE_SOURCES:.c=.o} 
OBJS_OUT=$(addprefix $(OBJDIR)/, $(OBJS))

all: $(OBJS)

$(OUT):
	mkdir -p $(OUT)

$(KEYSTORE_LIBRARY):
	cd ../../core/ks/generated;\
	make

test: $(KEYSTORE_TEST_SOURCES) $(KEYSTORE_LIBRARY)
	$(CC) $(CFLAGS) $(KEYSTORE_TEST_SOURCES) $(KEYSTORE_LIBRARY)  -o $@  


.SUFFIXES:
.SUFFIXES: .c .o

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS)  -o $@ -c $<
clean:


