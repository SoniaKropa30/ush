#include "ush.h"
char *mx_join_to_path(char *dst, char *str) {
    int dst_len = 0;
    char *s = NULL;

    if (str && dst) {
        dst_len = strlen(dst);
        s = mx_strnew(dst_len + strlen(str));

        for (int i = 0; i < dst_len; i++)
            s[i] = dst[i];
        for (int j = 0; j < mx_strlen(str); dst_len++, j++)
            s[dst_len] = str[j];
        free(dst);
        return s;
    }
    if (str == 0 && dst == 0)
        return NULL;
    if (dst != 0)
        return mx_strdup(str);
    return mx_strdup(str);
}

