#include "ush.h"

char *mx_check_env(char **arr, char *macros) {
    int n = mx_strlen(macros);
    char *res = NULL;
    int j = 0;

    for (int i = 0; arr[i] != NULL; i++) {
        if ((strncmp(arr[i], macros, n) == 0)
            && arr[i][n] == '=') {
            if (strncmp(&arr[i][n + 1], "'", 1) == 0) {
                j = mx_strlen(&arr[i][n + 2]) - 1;
                res = mx_strndup(&arr[i][n + 2], j);
            }
            else
                res = mx_strdup(&arr[i][n + 1]);
        }
    }
    return res;
}
