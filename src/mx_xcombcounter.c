#include "ush.h"

int mx_xcombcounter(char cmd1, char cmd2, char *first_need, int count) {
    if (cmd1 != first_need[0]) {
        if (cmd2 == first_need[1])
            count++;
    }
    return count;
}
