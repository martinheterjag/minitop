#include "minitop.h"

#include <ctype.h>
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Requirements v 1.0.0:
// 1) list processes
// 2) show process data in a table
// 3) periodic update of the view, exit with 'q'
// 4) sorting using keyboard input

bool is_pid(char* str) {
    int len = strlen(str);

    if (len == 0) {
        return false;
    }

    for (int i = 0; i < len; ++i) {
        // printf("%c is digit: %s\n", str[i], isdigit(str[i])? "true":"false");
        if (!isdigit(str[i])) {
            return false;
        }
    }

    return true;
}

char* get_file_content(char* path) {
    size_t length = 0;
    size_t capacity = 1024;
    char* buffer = malloc(capacity);

    FILE* f = fopen(path, "r");

    if (f) {
        if (buffer) {
            int c;
            while ((c = fgetc(f)) != EOF) {
                if (length + 1 >= capacity) {
                    capacity *= 2;
                    char* tmp = realloc(buffer, capacity);
                    if (!tmp) {
                        free(buffer);
                        fclose(f);
                        return "N/A";
                    }
                    buffer = tmp;
                }
                buffer[length++] = (char)c;
            }
            buffer[length] = '\0';
        }
    }

    fclose(f);

    if (buffer) {
        return buffer;
    }
    return "N/A";
}

char* get_cmd(char* pid) {
    char path[1024];
    snprintf(path, sizeof(path), "/proc/%s/cmdline", pid);
    return get_file_content(path);
}

int run_minitop() {
    struct dirent* de;
    DIR* dr = opendir("/proc");

    if (dr == NULL) {
        printf("Could not open /proc");
    }

    while ((de = readdir(dr)) != NULL) {
        char* pid = de->d_name;
        if (is_pid(pid)) {
            char* cmd = get_cmd(pid);
            printf("PID: %7s |\tcmd: %7s |\n", pid, cmd);
        }
    }
    closedir(dr);
    return 0;
}
