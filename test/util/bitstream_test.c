// Original Author: Trevor Killeen (2015)
//
// Test Suite for the bitstream IO class

#include <check.h>
#include <stdint.h>

#include "./bitstream_test.h"
#include "../../src/util/bitstream.h"

struct bitstream *bs;

void setup() {
	bs = bitstream_create();
	ck_assert(bs != NULL);
}

void teardown() {
	bitstream_destroy(bs);
}

// Basic test for allocating/freeing a bitstream
START_TEST(alloc_test)
{
}
END_TEST