#include "ush.h"

static int get_end_sub(char *cmd, int start) {
    int open = 0;
    int close = 0;
    int scopes = 0;

    for (int i = start; start != -1 && cmd[i] != '\0'; i++) {
        if (i == start)
            scopes = mx_counter(cmd[i], '`', scopes);
        scopes = mx_xcombcounter(cmd[i], cmd[i + 1], "\\`", scopes);
        open = mx_combcounter(cmd[i], cmd[i + 1], "$(", open);
        close = mx_counter(cmd[i], ')', close);
        if ((open - close == 0 && scopes % 2 == 0)
            && (open + close > 1 || scopes != 0)) {
            if (cmd[i + 1] == '`')
                return i + 2;
            if  (cmd[i] == ')')
                return i + 1;
        }
    }
    return -1;
}

static int count_without_scopes(char *cmd, int open, int close, int scopes) {
    int num = mx_strlen(cmd);

    for (int i = 0; cmd[i] != '\0'; i++) {
        if (open - close == 0) {
            scopes = mx_combcounter(cmd[i], cmd[i + 1], "\\`", scopes);
        }
        open = mx_combcounter(cmd[i], cmd[i + 1], "$(", open);
        close = mx_counter(cmd[i], ')', close);
    }
    return num - scopes;
}

char *without_slash(char *cmd, int open, int close, int scopes) {
    int num = count_without_scopes(cmd, 0, 0, 0);
    char *tmp = malloc(sizeof(char) * (num + 1));
    int k = 0;

    tmp[num] = '\0';
    for (int i = 0; cmd[i] != '\0'; i++) {
        if (open - close == 0) {
            scopes = mx_combcounter(cmd[i], cmd[i + 1], "\\`", 0);
            if (scopes > 0)
                i++;
        }
        open = mx_combcounter(cmd[i], cmd[i + 1], "$(", open);
        close = mx_counter(cmd[i], ')', close);
        tmp[k++] = cmd[i];
    }
    free(cmd);
    return tmp;
}

char *mx_command_sub(t_st *st, char *cmd, char *begin, t_config* term) {
    int start = mx_get_start_sub(cmd);
    int end = get_end_sub(cmd, start);
    char *final = NULL;
    char *midl = NULL;

    if (start != -1 && end != -1) {
        if (start > 0)
            begin = mx_strndup(cmd, start);
        if (end < mx_strlen(cmd))
            final = mx_strdup(&cmd[end]);
        if (cmd[start + 1] == '(')
            midl = mx_strndup(&cmd[start + 2], end - start - 3);
        else
            midl = mx_strndup(&cmd[start + 1], end - start - 2);
        midl = without_slash(midl, 0, 0, 0);
        cmd = mx_get_com_sub(term, begin, midl, final);
    }
    start = mx_get_start_sub(cmd);
    if (start != -1 && get_end_sub(cmd, start) != -1)
        cmd = mx_command_sub(st, cmd, NULL, term);
    return cmd;
}



