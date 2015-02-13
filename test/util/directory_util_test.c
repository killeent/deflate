// Original Author: Trevor Killeen (2015)
//
// Test Suite for the directory util implementation

#include <stdlib.h>
#include <assert.h>
#include <check.h>
#include <errno.h>
#include <sys/stat.h>

#include "./directory_util_test.h"
#include "../files/test_files.h"
#include "../../src/util/queue.h"
#include "../../src/util/directory_util.h"

struct queue *q;

static void free_str(void *str) {
	free(str);
}

static void setup() {	
	q = allocate_queue();
	assert(q != NULL);
}

static void teardown() {
	free_queue(q, free_str);	
}

// tests trying to crawl a directory specified by an invalid path
START_TEST(crawl_invalid_directory_test)
{
	char *invalid_dir = "adjkadjkads\n";
	ck_assert_int_eq(crawl_directory(invalid_dir, q), ENOENT);
}
END_TEST

// tests trying to crawl a directory path that is actually a file
START_TEST(crawl_file_directory_test)
{
	ck_assert_int_eq(crawl_directory(EMPTY_FILE, q), ENOTDIR);	
}
END_TEST

// tests trying to crawl a directory we don't have permission to read
START_TEST(crawl_directory_without_permission_test)
{
	int res;

	// make directory unreadable
	res = chmod(EMPTY_DIR, 0);
	if (res != 0) {
		if (errno == EPERM) {
			ck_abort_msg("cannot perform necessary chmod");
		}
		// todo: this could probably be better
		ck_abort_msg("unknown error");
	}

	ck_assert_int_eq(crawl_directory(EMPTY_DIR, q), EACCES);

	// make it readable again (chmod 755)
	chmod(EMPTY_DIR, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
}
END_TEST

// tests crawling an empty directory
START_TEST(crawl_empty_directory_test)
{
	ck_assert_int_eq(crawl_directory(EMPTY_DIR, q), 0);
	// check that queue is empty
	ck_assert(dequeue(q) == NULL);
}
END_TEST

// tests crawling a directory with a single file
START_TEST(crawl_single_file_directory_test)
{

}
END_TEST

// tests crawling a directory with a single file that we don't have
// permission to read
START_TEST(crawl_single_file_without_permission_directory_test)
{

}
END_TEST

// tests crawling a directory with multiple files
START_TEST(crawl_multi_file_directory_test)
{

}
END_TEST

// tests crawling a directory with multiple files, where at least
// one file we don't have permission to read
START_TEST(crawl_multi_file_without_permission_directory_test)
{

}
END_TEST

// tests crawling a directory recursively, but the recursive directories
// and the top-level directories contain no files
START_TEST(crawl_empty_directory_recursive_test)
{

}
END_TEST

// tests crawling a directory recursively with a single file in
// every directory
START_TEST(crawl_single_file_directory_recursive_test)
{

}
END_TEST

// tests crawling a directory recursively with a multiple files in
// every directory
START_TEST(crawl_multi_file_directory_recursive_test)
{

}
END_TEST

Suite *directory_util_suite() {
	Suite *s;
	TCase *tc_core;

	s = suite_create("directory_util");

	tc_core = tcase_create("core");
	tcase_add_checked_fixture(tc_core, setup, teardown);

	tcase_add_test(tc_core, crawl_invalid_directory_test);
	tcase_add_test(tc_core, crawl_file_directory_test);
	tcase_add_test(tc_core, crawl_directory_without_permission_test);
	tcase_add_test(tc_core, crawl_empty_directory_test);
	tcase_add_test(tc_core, crawl_single_file_directory_test);
	tcase_add_test(tc_core, crawl_single_file_without_permission_directory_test);
	tcase_add_test(tc_core, crawl_multi_file_directory_test);
	tcase_add_test(tc_core, crawl_multi_file_without_permission_directory_test);
	tcase_add_test(tc_core, crawl_empty_directory_recursive_test);
	tcase_add_test(tc_core, crawl_single_file_directory_recursive_test);
	tcase_add_test(tc_core, crawl_multi_file_directory_recursive_test);

	suite_add_tcase(s, tc_core);

	return s;
}