#include "ush.h"

void mx_del_chararr(char *arr) {
    if (arr != NULL) {
        free(arr);
        arr = NULL;
    }
}
