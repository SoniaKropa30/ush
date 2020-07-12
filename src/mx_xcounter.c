#include "ush.h"

int mx_xcounter(char cmd, char *not_need, int n) {
    for (int i = 0; i < n; i++) {
        if (cmd == not_need[i])
            return 1;
    }
    return 0;
}
