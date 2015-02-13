// Original Author: Trevor Killeen (2015)

#ifndef _DIRECTORY_UTIL_H_
#define _DIRECTORY_UTIL_H_

#include "./queue.h"

/**
 * Helper functions when working with directories.
 */

/**
 * Crawl a directory and return a queue of paths of files in that
 * directory.
 *
 * @param path to the directory to crawl.
 * @param files output parameter, a queue to store the paths of files in.
 *
 * @return 0 on success, otherwise error. 
 */
int crawl_directory(char *path, struct queue *files);

#endif