#include "storage.h"
#include <dirent.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

void storage_init(storage_t* storage, const char* root_path) {
    storage->root_path = calloc(strlen(root_path) + 1, sizeof(char));
    strcpy(storage->root_path, root_path);
}

void storage_destroy(storage_t* storage) {
    // free(storage) - no need to call 'free'
    storage = NULL;
}

void find_path(const char* cur_path, storage_key_t key, returned_value_t buf) {
    strcat(buf, cur_path);
    size_t size = strlen(buf) + 1;
    buf[size - 1] = '/';
    size_t j = 0, dir_sz = 0;
    while (j < strlen(key)) {
        buf[size] = key[j];
        ++size; ++dir_sz;
        if (dir_sz == SUBDIR_NAME_SIZE) {
            buf[size] = '\0';
            mkdir(buf, (1 << 10) - 1);
            buf[size++] = '/';
            dir_sz = 0;
        }
        ++j;
    }
    if (dir_sz == 0) {  buf[size++] = '@'; }
    buf[size++] = '\0';
}

version_t storage_set(storage_t* storage, storage_key_t key, storage_value_t value) {
    char buf[MAX_KEY_SIZE];
    for (int i = 0; i < MAX_KEY_SIZE; ++i) { buf[i] = '\0'; }
    find_path(storage->root_path, key, buf);

    int fd = open(buf, O_CREAT | O_RDWR, S_IRWXU);
    struct stat st;
    if (stat(buf, &st) == -1) { return -1; }

    size_t res = 0;
    for (size_t index = 0; index < st.st_size; ++index) {
        char current_value;
        if (read(fd, &current_value, 1) < 0) { return -1; }
        if (current_value == '\n') { ++res; }
    }
    if (write(fd, value, strlen(value)) < 0) { return -1; }
    if (write(fd, "\n", 1) < 0) { return -1; }
    close(fd);
    ++res;
    return res;
}

version_t storage_get(storage_t* storage, storage_key_t key, returned_value_t returned_value) {
    char buf[MAX_KEY_SIZE];
    for (int i = 0; i < MAX_KEY_SIZE; ++i) { buf[i] = '\0'; }
    find_path(storage->root_path, key, buf);

    struct stat st;
    int fd = open(buf, O_CREAT | O_RDWR, S_IRWXU);
    if (stat(buf, &st) == -1) { return -1; }

    int startln = -1, endln = -1;
    size_t res = 0;
    char content[MAX_VALUE_SIZE];
    for (size_t index = 0; index < st.st_size; ++index) {
        char current_value;
        if (read(fd, &current_value, 1) < 0) { return -1; }
        // if (strcmp(current_value, '\n') == 0) {
        if (current_value == '\n') {
            ++res;
            startln = endln;
            endln = index;
        }
        content[index] = current_value;
    }
    close(fd);
    // strncopy??
    for (int i = startln + 1; i < endln; ++i) {
        returned_value[i - startln - 1] = content[i];
    }
    returned_value[endln] = '\0';
    return res;
}

version_t storage_get_by_version(storage_t* storage, storage_key_t key, version_t version, returned_value_t returned_value) {
    char buf[MAX_VALUE_SIZE];
    for (int i = 0; i < MAX_KEY_SIZE; ++i) { buf[i] = '\0'; }
    find_path(storage->root_path, key, buf);

    struct stat st;
    int fd = open(buf, O_CREAT | O_RDWR, S_IRWXU);
    if (stat(buf, &st) == -1) { return -1; }

    size_t res = 0;
    int startln = -1, endln = -1;
    char content[MAX_KEY_SIZE];
    for (size_t index = 0; index < st.st_size; ++index) {
        char current_value;
        if (read(fd, &current_value, 1) < 0) { return -1; }
        content[index - endln - 1] = current_value;
        if (current_value == '\n') {
            ++res;
            startln = endln;
            endln = index;
            if (res == version) {
                close(fd);
                for (int i = 0; i < endln - startln - 1; ++i) {
                    returned_value[i] = content[i];
                }
                returned_value[endln - startln - 1] = '\0';
                return res;
            }
        }
    }
    close(fd);
    return 0;
}
