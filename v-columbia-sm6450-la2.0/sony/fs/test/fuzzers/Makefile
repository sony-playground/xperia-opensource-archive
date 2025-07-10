CXX := clang++-4.0
SANITIZERS := -fsanitize=address
LIBFUZZER := -lFuzzer

bins := hwconf_parser_fuzzer sin_parser_fuzzer secprop_fuzzer asahi_parser_fuzzer

incdirs := $(patsubst %,-iquote %,../../core/include ../../core/util/include ../../loader/include)
sanitizerflags := -fsanitize-coverage=trace-pc-guard,trace-cmp $(SANITIZERS)
extraflags := -g -O0 -ffunction-sections -fdata-sections -Wl,--gc-sections

all: $(bins)

.PHONY: clean
clean:
	$(RM) $(bins)

compile = $(CXX) $(incdirs) $(sanitizerflags) $(extraflags) -o $@ $(LIBFUZZER) -xc $+

hwconf_parser_fuzzer: hwconf_parser_fuzzer.c ../../core/hwconf/hwconf_parser.c
	$(compile)

sin_parser_fuzzer: sin_parser_fuzzer.c ../../core/sin/sin_parser.c
	$(compile)

secprop_fuzzer: secprop_fuzzer.c ../../loader/security_properties.c ../../loader/handler_list.c
	$(compile)

asahi_parser_fuzzer: asahi_parser_fuzzer.c ../../core/asahi/asahi_parser.c
	$(compile)
