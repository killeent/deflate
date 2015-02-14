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
 * It is the client's responsibility to allocate and free this queue.
 *
 * @return 0 on success, otherwise error. 
 */
int crawl_directory(char *path, struct queue *files);

/**
 * Joins the paths specified by path1 and path2.
 *
 * @param path1 the prefix path.
 * @param path2 the suffix path.
 * @param combined output parameter for the combined path. It is
 * the client's responsibility to free the memory associated with
 * combined.
 *
 * @return 0 on success, with the joined path in combined, otherwise
 * error and combined has not been allocated. 
 */
int join_path(char *path1, char *path2, char **combined);

#endif