#include <stdio.h>

#include "minitop.h"

char* version = "0.0.0";

int main() {
    printf("minitop %s\n\n", version);
    int res = run_minitop();
    return res;
}

