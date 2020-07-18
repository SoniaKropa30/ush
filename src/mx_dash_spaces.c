#include "ush.h"

static int new_size(char *cmd) {
    int n = mx_strlen(cmd);
    int i = 0;

    for (; cmd[i] == ' ' && cmd[i] != '\0'; i++);
    for (; cmd[i] != ' ' && cmd[i] != '\0'; i++);
    for (; cmd[i] == ' ' && cmd[i] != '\0'; i++);
    if (cmd[i] != ' ' && cmd[i] != '\0') {
        for (; cmd[i] != '\0'; i++) {
            if (cmd[i] == ' ')
                n++;
        }
    }
    return n;
}

char *mx_dash_spaces(char *cmd, char *res, int i, int k) {
    int n = new_size(cmd);

    res = malloc(sizeof(char) * (n + 1));
    res[n] = '\0';
    for (; cmd[i] == ' ' && cmd[i] != '\0'; i++)
        res[k++] = cmd[i];
    for (; cmd[i] != ' ' && cmd[i] != '\0'; i++)
        res[k++] = cmd[i];
    for (; cmd[i] == ' ' && cmd[i] != '\0'; i++)
        res[k++] = cmd[i];
    if (cmd[i] != ' ' && cmd[i] != '\0') {
        for (; cmd[i] != '\0'; i++) {
            if (cmd[i + 1] != '\0' && cmd[i] == ' '
                && cmd[i + 1] != ' ')
                res[k++] = '\\';
            res[k++] = cmd[i];
        }
    }
    free(cmd);
    return res;
}
