#include "ush.h"

static char *cmd_del_spaces(char *cmd) {
    char *tmp = NULL;
    int n = mx_strlen(cmd) - 1;
    int start = 0;
    int end = 0;

    if (cmd[start] == '{') {
        for (;(cmd[start] == '{' || cmd[start] == ' ')
        && cmd[start] != '\0'; start++);
    }
    if (cmd[n] == '}') {
        for (;(cmd[n] == '}' || cmd[n] == ' ') && n != 0; n--)
            end++;
    }
    if (start || end) {
        tmp = mx_strndup(&cmd[start], mx_strlen(&cmd[start]) - end);
        mx_del_chararr(cmd);
        return tmp;
    }
    return cmd;
}

static char **midl_pars(t_st *st, char *c, int k, int bufsize) {
    char **tokens = malloc(bufsize * sizeof(char*));

    for (int i = 0; c[i] != '\0'; i++) {
        if (c[i] == '|' || c[i] == '<' || c[i] == '>') {
            tokens[k++] = strndup(&c[i], 1);
            mx_counter(c[i], '|', st->pipe);
        }
        else if (c[i] != ' ') {
            tokens[k++] = strndup(&c[i], strcspn(&c[i], " <>|"));
            i += strcspn(&c[i], " <>|") - 1;
        }
        tokens = mx_split_backup(tokens, bufsize, k);
        if (k >= bufsize)
            bufsize += 64;
    }
    tokens[k] = NULL;
    return tokens;
}

static int no_buf(char *main_c) {
    if (mx_strcmp(main_c, "cd") == 0
        || mx_strcmp(main_c, "export") == 0
        || mx_strcmp(main_c, "unset") == 0
        || mx_strcmp(main_c, "exit") == 0
        || mx_strcmp(main_c, "env") == 0
        || mx_strcmp(main_c, "vim") == 0
        || mx_strcmp(main_c, "emacs") == 0
        || mx_strcmp(main_c, "alias") == 0)
        return 1;
    return 0;
}

int mx_command_pars(t_st *st, char *c, int k, t_config* term) {
    int bufsize = 64;
    char **tokens = NULL;
    char *main_c = NULL;

    c = cmd_del_spaces(c);
    c = mx_without_slash(c, NULL, 0, 0);
    main_c = strndup(c, strcspn(c, " \0"));
    if (no_buf(main_c) == 1) {
        if (mx_strcmp(main_c, "cd") == 0)
            tokens = mx_streams_cd(c, 1, bufsize, main_c);
        else
            tokens = mx_streams_pars(c, 1, bufsize, main_c);
        if (mx_strcmp(main_c, "alias") == 0)
            st->status = mx_builtin_alias(st, tokens, NULL, NULL);
        else
            st->status = mx_streams(st, tokens, (t_app *)term->app);
    }
    else {
        tokens = midl_pars(st, c, k, bufsize);
        st->status = mx_conveer(st, tokens, term);
    }
    return st->status;
}
