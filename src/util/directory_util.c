// Original Author: Trevor Killeen (2015)

#include <stdlib.h>
#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#include "./directory_util.h"
#include "./queue.h"

int crawl_directory(char *path, struct queue *files) {
	assert(path != NULL);
	assert(files != NULL);

	DIR *dirp;
	struct dirent *de;
	uint8_t file_type;
	char *file_name;
	int res;

	dirp = opendir(path);
	if (dirp == NULL) {
		return errno;
	}

	// loop through the files, adding them to the queue
	while ((de = readdir(dirp)) != NULL) {
		file_type = de->d_type;

		// only make make a copy of the file name if it is a directory
		// or a regular file
		if (file_type == DT_DIR || file_type == DT_REG) {
			// check if '.' or '..'
			if (strncmp(de->d_name, ".", 1) == 0 || 
					strncmp(de->d_name, "..", 2) == 0) {
				continue;
			}

			// join path with file
			res = join_path(path, de->d_name, &file_name);
			if (res != 0) {
				return 0;
			}

			if (file_type == DT_DIR) {
				// recurse on directory
				res = crawl_directory(file_name, files);
				if (res != 0) {
					free(file_name);
					closedir(dirp);
					return res;
				}
				free(file_name);
			} if (file_type == DT_REG) {
				// regular file
				res = enqueue(files, (void *)file_name);
				if (res != 0) {
					closedir(dirp);
					return res;
				}
			}
		}
	}

	closedir(dirp);
	return 0;
}

int join_path(char *path1, char *path2, char **combined) {
	assert(path1 != NULL);
	assert(path2 != NULL);
	assert(combined != NULL);

	size_t len1, len2;
	char *iter;

	// get the number of characters (not including \n) in each path
	len1 = strlen(path1);
	len2 = strlen(path2);

	// if first path is empty, simply return path2 as the path
	if (len1 == 0) {
		*combined = (char *)malloc(len2 + 1);
		if (*combined == NULL) {
			return errno;
		}
		strcpy(*combined, path2);
		return 0;
	} 

	*combined = (char *)malloc(len1 + len2 + 2);
	if (*combined == NULL) {
		return errno;
	}

	// copy the first path
	iter = stpncpy(*combined, path1, len1);

	// add the '/'
	*iter = '/';
	iter++;

	// copy the second path
	strcpy(iter, path2);
	return 0;
}