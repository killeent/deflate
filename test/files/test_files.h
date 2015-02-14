// Original Author: Trevor Killeen (2015)
//
// #defines for test files to be used by multiple test suites

#ifndef _TEST_FILES_H_
#define _TEST_FILES_H_

// files
#define EMPTY_FILE "./test/files/empty.txt"
#define DOUBLE_BYTE_FILE "./test/files/double.txt"
#define ASCII_FILE "./test/files/ascii.txt"
#define PRIDE_AND_PREJUDICE "./test/files/prejudice.txt"

// dirs
#define EMPTY_DIR "./test/files/empty_dir"
#define RECURSIVE_EMPTY_DIR "./test/files/recursive_empty_dir"

#define SINGLE_FILE_DIR "./test/files/single_file_dir"
#define RECURSIVE_SINGLE_FILE_DIR "./test/files/recursive_single_file_dir"
#define RECURSIVE_SINGLE_FILE_DIR_SUB_DIR "./test/files/recursive_single_file_dir/sub_dir"
#define SINGLE_FILE_DIR_FILE "empty.txt"

#define MULTI_FILE_DIR "./test/files/multi_file_dir"
#define RECURSIVE_MULTI_FILE_DIR "./test/files/recursive_multi_file_dir"
#define RECURSIVE_MULTI_FILE_DIR_SUB_DIR "./test/files/recursive_multi_file_dir/sub_dir"
#define MULTI_FILE_DIR_COUNT 3
extern const char *multi_file_dir_files[3];

#endif
