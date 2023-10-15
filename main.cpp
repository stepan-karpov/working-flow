#include "storage.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

const int ALL_MAX_SIZE = 4096;
const char CHAR = '@';
const size_t MAX_VAL_SIZE = (1 << 10) - 1;

void storage_init(storage_t* storage, const char* root_path) {
    storage->root_path = malloc(strlen(root_path) + 1);
    strcpy(storage->root_path, root_path);
}

void storage_destroy(storage_t* storage) {
    storage = NULL;
}

void getbuffer(const char* cur_path, storage_key_t key, returned_value_t buf) {
    buf[0] = '\0';
    strcat(buf, cur_path);
    size_t index = strlen(buf) + 1;
    buf[index - 1] = '/';
    size_t sz = strlen(key);
    size_t j = 0;
    size_t directory_size = 0;
    while (j < sz) {
        buf[index++] = key[j++];
        ++directory_size;
        if (directory_size == SUBDIR_NAME_SIZE) {
            buf[index] = '\0';
            mkdir(buf, MAX_VAL_SIZE);
            buf[index++] = '/';
            directory_size = 0;
        }
    }
    if (directory_size == 0) {
        buf[index++] = CHAR;
    }
    buf[index++] = '\0';
}

version_t storage_set(storage_t* storage, storage_key_t key, storage_value_t value) {
    struct stat st;
    char buf[ALL_MAX_SIZE];
    buf[0] = '\0';
    getbuffer(storage->root_path, key, buf);
    int fd = open(buf, O_CREAT | O_RDWR, S_IRWXU);
    int result = stat(buf, &st);
    size_t val_sz = strlen(value);
    size_t index = 0;
    size_t lines_count = 0;
    char curvalue;
    for (size_t index = 0; index < st.st_size; ++index) {
        result = read(fd, &curvalue, 1);
        if (curvalue == '\n') {
            ++lines_count;
        }
    }
    result = write(fd, value, val_sz);
    result = write(fd, "\n", 1);
    close(fd);
    return lines_count + 1;
}

version_t storage_get(storage_t* storage, storage_key_t key, returned_value_t returned_value) {
    struct stat st;
    char buf[ALL_MAX_SIZE];
    buf[0] = '\0';
    getbuffer(storage->root_path, key, buf);
    int fd = open(buf, O_CREAT | O_RDWR, S_IRWXU);
    int result = stat(buf, &st);
    int prevline = -1;
    int thisline = -1;
    size_t index = 0;
    size_t lines_count = 0;
    size_t curread = 0;
    char curvalue;
    char linesread[ALL_MAX_SIZE];
    for (size_t index = 0; index < st.st_size; ++index) {
        result = read(fd, &curvalue, 1);
        linesread[index] = curvalue;
        if (curvalue == '\n') {
            ++lines_count;
            prevline = thisline;
            thisline = index;
        }
    }
    close(fd);
    for (int i = prevline + 1; i < thisline; ++i) {
        returned_value[i - prevline - 1] = linesread[i];
    }
    returned_value[thisline] = '\0';
    return lines_count;
}

version_t storage_get_by_version(storage_t* storage, storage_key_t key, version_t version, returned_value_t returned_value) {
    char buf[ALL_MAX_SIZE];
    struct stat st;
    buf[0] = '\0';
    int result;
    getbuffer(storage->root_path, key, buf);
    int fd = open(buf, O_CREAT | O_RDWR, S_IRWXU);
    result = stat(buf, &st);
    size_t index = 0;
    size_t curread = 0;
    size_t lines_count = 0;
    int prevline = -1;
    int thisline = -1;
    char curvalue;
    char linesread[ALL_MAX_SIZE];
    for (size_t index = 0; index < st.st_size; ++index) {
        result = read(fd, &curvalue, 1);
        linesread[index - thisline - 1] = curvalue;
        if (curvalue == '\n') {
            prevline = thisline;
            thisline = index;
            ++lines_count;
            if (lines_count == version) {
                close(fd);
                for (int i = 0; i < thisline - prevline - 1; ++i) {
                    returned_value[i] = linesread[i];
                }
                returned_value[thisline - prevline - 1] = '\0';
                return lines_count;
            }
        }
    }
    close(fd);
    return 0;
}