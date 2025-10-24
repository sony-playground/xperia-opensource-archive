#include "iterator.h"
#include "fcserr.h"
#include "gen_tests.h"

int setup_modules(struct iterator_info *it)
{
	if (add_module(it, "xmodem-normal-setup:",
			execute_module_xmodem_normal_setup))
		return -FCSERR_ENOMEM;
	return FCSERR_OK;
}

