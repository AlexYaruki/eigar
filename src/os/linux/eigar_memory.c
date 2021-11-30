#include <eigar.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

#define MEMORY_BLOCK_SIZE_PATH "/sys/devices/system/memory/block_size_bytes"
#define MEMORY_BLOCKS_ROOT_DIR_PATH "/sys/bus/memory/devices"

static int64_t get_memory_block_size() {
    FILE* file = fopen(MEMORY_BLOCK_SIZE_PATH, "r");
    char* line;
    size_t line_length;

    if(getline(&line, &line_length, file) < 0) {
        free(line);
        printf("Cannot read memory block size from %s", MEMORY_BLOCK_SIZE_PATH);
        exit(-1);
    }
    int64_t result = strtoll(line, NULL, 16);
    fclose(file);
    return result;
}

static char* get_memory_block_online_status_path(const struct dirent* entry) {
    size_t path_buffer_size = strlen(MEMORY_BLOCKS_ROOT_DIR_PATH);
    path_buffer_size += 1;
    path_buffer_size += strlen(entry->d_name);
    path_buffer_size += 1;
    path_buffer_size += strlen("online");
    path_buffer_size += 1;
    char* path_buffer = malloc(path_buffer_size);
    path_buffer[0] = '\0';
    sprintf(path_buffer, "%s/%s/%s", MEMORY_BLOCKS_ROOT_DIR_PATH, entry->d_name, "online");
    return path_buffer;
}

static char get_memory_block_online_status(const struct dirent* entry){
    char* online_status_file_path = get_memory_block_online_status_path(entry);
    FILE* online_status_file = fopen(online_status_file_path, "r");
    char online_status;
    fread(&online_status,1,1,online_status_file);
    fclose(online_status_file);
    free(online_status_file_path);
    return online_status;
}

static int32_t get_online_memory_blocks_count(){
    DIR* memory_clocks_root_dir = opendir(MEMORY_BLOCKS_ROOT_DIR_PATH);
    if(memory_clocks_root_dir == NULL) {
        printf("Cannot open memory blocks root dir at %s, error code: %d\n", MEMORY_BLOCKS_ROOT_DIR_PATH, errno);
        exit(-1);
    }
    struct dirent* entry;
    int32_t count = 0;
    while((entry = readdir(memory_clocks_root_dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        char online_status = get_memory_block_online_status(entry);
        if(online_status == '1') {
            count += 1;
        }
    }
    closedir(memory_clocks_root_dir);
    return count;
}
//TODO: Solution is not working when RAM is allocated to integrated graphics card
int64_t eigar_memory_total_physical() {
    int64_t memory_block_size = get_memory_block_size();
    int32_t memory_blocks_online = get_online_memory_blocks_count();
    return memory_block_size * memory_blocks_online;
}

