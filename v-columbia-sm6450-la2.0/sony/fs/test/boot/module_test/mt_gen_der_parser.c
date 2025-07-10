#include "iterator.h"
#include "integration_main.h"
#include "der_parser.h"

/* Test 1:
 * Sequence of integers of various values
 */
static const struct asn1_item asn1pdu_test1_items[] = {
	{
		.param = 0,
		.name = "integer",
		.handler = type_handler_int,
		.items_count = 0,
		.items = NULL
	}
};
static const struct asn1_item asn1pdu_test1[] = {
	{
		.param = 0,
		.name = "test1",
		.handler = type_handler_seq_of,
		.items_count = sizeof(asn1pdu_test1_items)/
				sizeof(struct asn1_item),
		.items = asn1pdu_test1_items
	}
};
static const char * const ASN1PDU_MATCH_TEST1[] = {
	"integer", "\0" };
static const uint8_t data_test1[34] = {
	0x30, 0x20,
	/* -1 */
	0x02, 0x02, 0xff, 0xff,
	/* min int 4 bytes */
	0x02, 0x04, 0x80, 0x00, 0x00, 0x00,
	/* +1 */
	0x02, 0x01, 0x01,
	/* max int 4 bytes */
	0x02, 0x04, 0x7f, 0xff, 0xff, 0xff,
	/* pos int with initial zeros */
	0x02, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00,
	/* zero */
	0x02, 0x01, 0x00,
};
static const int ref_values_test1[] = {
	-1, -0x80000000, 1, 0x7fffffff, 0x800000, 0 };

int execute_module_gen_der_parser(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match)
{
	int res = FCSERR_OK;
	struct iterator_info *iterator = NULL;
	struct derparser_object *value = NULL;
	int i;

	switch (it->cur_module_item) {
	case 0:
		/* If unexpected shutdown goto 2 */
		set_next_module_item(it, 1);
		export_tcstate(it);


		/*
		 * Test 1:
		 */
		/* Create value object */
		value = derparser_create_integer();
		if (value == NULL) {
			log("Failed to create integer object\n");
			goto test_failure;
		}
		/* Create iterator */
		res = derparser_create_iterator(
			&iterator,
			asn1pdu_test1,
			sizeof(data_test1),
			(uint8_t *)data_test1,
			(const char **)ASN1PDU_MATCH_TEST1);
		if (res != FCSERR_OK) {
			log("Failed to create iterator\n");
			goto test_failure;
		}
		for (i = 0; i < sizeof(ref_values_test1)/sizeof(int); i++) {
			res = derparser_next(iterator, value);
			if (res < 0) {
				log("Failed to parse test1\n");
				goto test_failure;
			}
			if (res == 0) {
				log("Failed to find integer\n");
				goto test_failure;
			}
			if (ref_values_test1[i] !=
				derparser_get_integer(value)) {
				log("Unexpected integer %d, expected %d\n",
					derparser_get_integer(value),
					ref_values_test1[i]);
				goto test_failure;
			}
		}
		derparser_delete_iterator(iterator);
		iterator = NULL;
		derparser_delete_object(value);
		value = NULL;

		/* We got through the test, goto next test */
		inc_n_executed(it);
		set_next_module_item(it, -1);
		break;
	default:
		/* Unexpected shutdown/restart */
		goto test_failure;
	}

	return FCSERR_OK;

test_failure:
	set_next_module_item(it, -1);
	inc_n_failed(it);
	inc_n_executed(it);
	derparser_delete_iterator(iterator);
	derparser_delete_object(value);
	return FCSERR_OK;
}


