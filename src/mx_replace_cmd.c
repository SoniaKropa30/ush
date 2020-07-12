#include "ush.h"

static char *replace_env_end(char *cmd, char *head, char *res, char *tail) {
    char *tmp = NULL;

    tmp = mx_strjoin(head, res);
    mx_del_chararr(cmd);
    cmd = mx_strjoin(tmp, tail);
    mx_del_chararr(head);
    mx_del_chararr(tail);
    mx_del_chararr(tmp);
    mx_del_chararr(res);
    return cmd;
}

static char *replace_env_midl(t_st *st, char *tmp, char *res) {
    res = mx_check_env(st->env, tmp);
    if (res == NULL)
        res = mx_check_env(st->set, tmp);
    mx_del_chararr(tmp);
    return res;
}

static char *replace_env(t_st *st, int i, char *cmd, char *head) {
    char *tail = NULL;
    char *tmp = NULL;
    char *res = NULL;
    int k = i + 1;

    if (i != 0)
        head = mx_strndup(cmd, i);
    if (cmd[k] == '{') {
        for (; cmd[k] != '}' && cmd[k]; k++);
        tmp = strndup(&cmd[i + 2], k - i - 2);
        tail = mx_strdup(&cmd[k + 1]);
    }
    else {
        tmp = mx_get_env(cmd, k);
        tail = mx_strdup(&cmd[k + mx_strlen(tmp)]);
    }
    res = replace_env_midl(st, tmp, res);
    cmd = replace_env_end(cmd, head, res, tail);
    return cmd;
}

static char *replace_pwd(int i, char *cmd, char *tail) {
    char *head = mx_strndup(cmd, i);
    char *tmp = NULL;

    if (cmd[i + 1] == '+' || cmd[i + 1] == '-') {
        tail = strdup(&cmd[i + 2]);
        if (cmd[i + 1] == '+')
            tmp = mx_strjoin(head, getenv("PWD"));
        else if (cmd[i + 1] == '-')
            tmp = mx_strjoin(head, getenv("OLDPWD"));
    }
    else {
        tail = strdup(&cmd[i + 1]);
        tmp = mx_strjoin(head, getenv("HOME"));
    }
    mx_del_chararr(cmd);
    cmd = mx_strjoin(tmp, tail);
    mx_del_chararr(head);
    mx_del_chararr(tail);
    mx_del_chararr(tmp);
    return cmd;
}

char *mx_replace_cmd(t_st *st, char *cmd) {
    for (int i = 0; cmd[i] != '\0'; i++) {
        if (cmd[i] == '$' && cmd[i + 1] != '('
            && mx_check_slash(cmd, i) == 0) {
            cmd = replace_env(st, i, cmd, NULL);
        }
    }
    for (int i = 0; cmd[i] != '\0'; i++) {
        if (cmd[i] == '~'
            && ((cmd[i - 1] == ' ' && i != 0) || i == 0)) {
            if (((cmd[i + 1] == '-' || cmd[i + 1] == '+')
                 && (cmd[i + 2] == ' ' || cmd[i + 2] == '/'
                 || cmd[i + 2] == '\0')) || (cmd[i + 1] == ' '
                 || cmd[i + 1] == '/' || cmd[i + 1] == '\0'))
                cmd = replace_pwd(i, cmd, NULL);
            else
                cmd = mx_tilda_prefix(i, cmd);
        }
    }
    cmd = mx_cmd_return_alias(st, cmd, NULL, NULL);
    return cmd;
}
