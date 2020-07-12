#include "ush.h"

int mx_combcounter(char cmd1, char cmd2, char *need, int count) {
    if (cmd1 == need[0]) {
        if (cmd2 == need[1])
            count++;
    }
    return count;
}
