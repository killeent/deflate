// Original Author: Trevor Killeen (2015)

#include <stdlib.h>
#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

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

			file_name = (char *)malloc(de->d_namlen);
			if (file_name == NULL) {
				return errno;
			}
			strncpy(file_name, de->d_name, de->d_namlen);

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