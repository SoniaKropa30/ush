#include "ush.h"

char *mx_get_all_alias(char **tok, int cur) {
    int n = mx_strlen(tok[cur]);
    int all = n;
    char *res = NULL;

    for (int i = cur + 1; tok[i] != NULL; i++) {
        n = mx_strlen(tok[i]);
        all += n + 1;
        if (strstr(tok[i], "'") || tok[i][n - 1] == '"')
            break;
    }
    res = malloc(sizeof(char) * (all + 1));
    for (int i = 0; tok[cur] != NULL && i < all;) {
        for (int j = 0; tok[cur][j] != '\0'; j++)
            res[i++] = tok[cur][j];
        res[i++] = ' ';
        cur++;
    }
    res[all] = '\0';
    return res;
}
