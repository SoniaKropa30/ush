#include "ush.h"

static char *get_name(char *cmd) {
    char *name = NULL;
    int i = 0;

    for (; cmd[i] != '\0' && cmd[i] != '='; i++);
    if (cmd[i] == '=')
        name = mx_strndup(cmd, i);
    else {
        write(2, "ush: alias: ", 12);
        write(2, cmd, mx_strlen(cmd));
        write(2, ": not found\n", 12);
    }
    return name;
}

static int check_and_replace(char *cmd, char **alias, char *name) {
    int cur = -1;
    int i = 0;

    if (name != NULL) {
        for (; alias[i] != NULL; i++) {
            if (strncmp(alias[i], name, mx_strlen(name)) == 0
                && alias[i][mx_strlen(name)] == '=') {
                cur = i;
                break;
            }
        }
        if (cur != -1) {
            alias[cur] = realloc(alias[cur], mx_strlen(cmd));
            mx_strcpy(alias[cur], cmd);
            free(name);
            return 0;
        }
    }
    return 1;
}

static char **new_alias(char *cmd, char **alias) {
    char **res = NULL;
    int i = 0;

    for (; alias[i] != NULL; i++);
    res = malloc(sizeof(char *) * (i + 2));
    for (int j = 0; alias[j] != NULL; j++)
        res[j] = mx_strdup(alias[j]);
    res[i] = mx_strdup(cmd);
    res[i + 1] = NULL;
    mx_del_strarr(&alias);
    return res;
}

static int next_alias(char **tok, int i) {
    int n = i + 1;

    for (; tok[n] != NULL; n++) {
        if (mx_check_quotes(tok[n]) == 1
            && tok[n + 1] != NULL) {
            n++;
            break;
        }
    }
    return n;
}

int mx_builtin_alias(t_st *st, char **tokens, char *name, char *all) {
    for (int i = 1; tokens[i] != NULL; ) {
        name = get_name(tokens[i]);
        if (mx_check_quotes(tokens[i]) == 1 && name) {
            all = mx_get_all_alias(tokens, i);
            if (check_and_replace(all, st->alias, name))
                st->alias = new_alias(all, st->alias);
            i = next_alias(tokens, i);
        }
        else if (name) {
            if (check_and_replace(tokens[i], st->alias, name))
                st->alias = new_alias(tokens[i], st->alias);
            i++;
        }
        else
            break;
    }
    return 0;
}
