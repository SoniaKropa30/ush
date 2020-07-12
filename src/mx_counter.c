#include "ush.h"

int mx_counter(char cmd, char need, int count) {
    if (cmd == need)
        count++;
    return count;
}
