#include "ush.h"

int mx_ncounter(char cmd, char *need, int count, int n) {
    for (int i = 0; i < n; i++) {
        if (cmd == need[i])
            count++;
    }
    return count;
}
