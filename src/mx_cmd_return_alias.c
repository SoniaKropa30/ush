#include "ush.h"

static char *get_alias(char *cmd, char *tmp, char *res, int i) {
    char *head = NULL;
    char *midl = NULL;
    char *tail = NULL;

    if (i != 0)
        head = mx_strndup(cmd, i);
    midl = mx_strjoin(head, res);
    tail = mx_strdup(&cmd[i + mx_strlen(tmp)]);
    mx_del_chararr(cmd);
    cmd = mx_strjoin(midl, tail);
    mx_del_chararr(head);
    mx_del_chararr(tail);
    mx_del_chararr(midl);
    return cmd;
}

char *mx_cmd_return_alias(t_st *st, char *cmd, char *tmp, char *res) {
    for (int i = 0; cmd[i] != '\0'; i++) {
        tmp = mx_strndup(&cmd[i], strcspn(&cmd[i], " "));
        if ((res = mx_check_env(st->alias, tmp)) != NULL) {
            cmd = get_alias(cmd, tmp, res, i);
            i += mx_strlen(res);
        }
        else
            i += mx_strlen(tmp);
        mx_del_chararr(tmp);
        mx_del_chararr(res);
    }
    if (strstr(cmd, "cd "))
        cmd = mx_dash_spaces(cmd, NULL, 0, 0);
    return cmd;
}
