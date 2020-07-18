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

static int mx_any_count(char c) {
    if (c == '"' || c == 39 || c == '`' || c == '(' || c == ')' || c == '{'
        || c == '}' || c == ' ' || c == '$')
        return 1;
    return 0;
}

static char *mx_without_slash(char *c, char *res, int k, int n) {
    for (int i = 0; c[i] != '\0'; i++) {
        if (c[i] == '\\' && c[i + 1] == '\\') {
            for (k = i; c[k] == '\\'; k++);
            if ((k - i) % 2 == 0)
                n += (k - i) / 2;
            else if (mx_any_count(c[k]))
                n += (k - i - 1) / 2;
            else {
                write(2, "Odd number of back slashes.\n", 28);
                exit(1);
            }
            i = k - 1;
        }
        else if (c[i] != '\\')
            n++;
    }
    //make
    // printf("%d  %d\n", n, mx_strlen(c));
    if (n != mx_strlen(c)) {
        res = malloc(sizeof(char) * (n + 1));
        res[n] = '\0';
        n = 0;
        for (int i = 0; c[i] != '\0'; i++) {
            if (c[i] == '\\' && c[i + 1] == '\\') {
                for (k = i; c[k] == '\\'; k++);
                if ((k - i) % 2 == 0) {
                    for (int j = 0; j < (k - i) / 2; j++)
                        res[n++] = c[i];
                }
                else if (mx_any_count(c[k])) {
                    for (int j = 0; j < (k - i - 1) / 2; j++)
                        res[n++] = c[i];
                }
                i = k - 1;
            }
            else if (c[i] != '\\')
                res[n++] = c[i];
        }
        mx_del_chararr(c);
        return res;
    }
    return c;
}

char **mx_streams_pars(char *c, int k, int bufsize, char *main_c) {
    char **tokens = malloc(bufsize * sizeof(char*));
    int i = strcspn(c, " \0");

    tokens[0] = main_c;
    for (; c[i] != '\0'; i++) {
        if (c[i] != ' ') {
            tokens[k++] = strndup(&c[i], strcspn(&c[i], " \0"));
            i += strcspn(&c[i], " \0") - 1;
        }
        tokens = mx_split_backup(tokens, bufsize, k);
        if (k >= bufsize)
            bufsize += 64;
    }
    tokens[k] = NULL;
    return tokens;
}

static int count_noslash(char *c, int i) {
    for (; c[i] != '\0'; i++) {
        if (c[i] == ' ' && c[i - 1] != '\\') {
            return i;
        }
    }
    return i;
}

static char *get_tok(char *c, int i, int n, int num) {
    char *res = NULL;

    for (int j = i; c[j] != '\0' && j < i + n; j++) {
        if (c[j] == ' ' && c[j - 1] == '\\')
            num++;
    }
    num = n - num;
    res = malloc(sizeof(char) * (num + 1));
    res[num] = '\0';
    num = 0;
    for (int j = i; c[j] != '\0' && j < i + n;) {
        if (c[j + 1] == ' ' && c[j] == '\\') {
            res[num++] = c[j + 1];
            if (c[j + 2] != '\0')
                j += 2;
        }
        else
            res[num++] = c[j++];
    }
    return res;
}

char **mx_streams_cd(char *c, int k, int bufsize, char *main_c) {
    char **tokens = malloc(bufsize * sizeof(char*));
    int i = strcspn(c, " \0");
    int n = 0;

    tokens[0] = main_c;
    for (; c[i] != '\0'; i++) {
        if (c[i] != ' ') {
            if (c[i] == '-' && c[i - 1] == ' ') {
                tokens[k++] = strndup(&c[i], strcspn(&c[i], " \0"));
                i += strcspn(&c[i], " \0") - 1;
            }
            else {
                n = strcspn(&c[i], " \0");
                if (c[i + n - 1] != '\\') {
                    tokens[k++] = strndup(&c[i], n);
                    i += strcspn(&c[i], " \0") - 1;
                }
                else {
                    n = count_noslash(c, i);
                    tokens[k++] = get_tok(c, i, n - i, 0);
                    i = n - 1;
                }
            }

        }
        tokens = mx_split_backup(tokens, bufsize, k);
        if (k >= bufsize)
            bufsize += 64;
    }
    tokens[k] = NULL;
    return tokens;
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
