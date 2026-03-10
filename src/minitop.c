#include "minitop.h"

#include <ctype.h>
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
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

char* get_cmd(char* pid) {
    return "tbd";
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
