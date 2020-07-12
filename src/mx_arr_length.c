#include "ush.h"

int mx_arr_len(char **arr) {
    int i = 0;
    while (arr[i] != NULL)
        i++;
    return i;
}
