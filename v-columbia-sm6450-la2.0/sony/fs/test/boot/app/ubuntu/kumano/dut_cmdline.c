/* A list of expected command line arguments from bootloader */
const char * const cmdline_args[] = {
	"androidboot.bootloader",
	"oemandroidboot.xboot",
	"androidboot.serialno",
	"startup",
	"warmboot"};

const int nr_of_cmdline_args = sizeof(cmdline_args) /
	sizeof(cmdline_args[0]);
