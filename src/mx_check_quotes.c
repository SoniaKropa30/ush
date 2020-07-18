#include "ush.h"

static int only_quotes(char *cmd, char q, int n) {
    for (int i = 0; cmd[i] != '\0'; i++) {
        if (cmd[i] == q && i == 0)
            n++;
        else if (cmd[i] == q && cmd[i - 1] != '\\')
            n++;
    }
    if (n % 2 != 0)
        return -1;
    return n;
}

static int end_quotes(char *cmd, char q, int n) {
    if (q == '`')
        n = only_quotes(cmd, q, n);
    if (n == -1)
        return 1;
    if (q == '"')
        n = only_quotes(cmd, q, n);
    if (n == -1)
        return 1;
    if (q == 39)
        n = only_quotes(cmd, q, n);
    if (n == -1)
        return 1;
    return 0;
}

static int midl_quotes(char *cmd, char q, char *op, char *cl) {
    int opened = 0;
    int closed = 0;

    for (int i = 0; cmd[i] != '\0' && (q == op[1] || q == cl[1]); i++) {
        if (i == 0) {
            opened = mx_counter(cmd[i], op[1], opened);
            closed = mx_counter(cmd[i], cl[1], closed);
        }
        else {
            opened = mx_xcombcounter(cmd[i - 1], cmd[i], op, opened);
            closed = mx_xcombcounter(cmd[i - 1], cmd[i], cl, closed);
        }
        if (opened - closed < 0)
            return 1;
    }
    if (opened - closed != 0)
        return 1;
    return 0;
}

static int odd_quotes(char *cmd, char q) {
    if (q == '{' || q == '}' || q == '(' || q == ')') {
        if (midl_quotes(cmd, q, "\\{", "\\}")
            || midl_quotes(cmd, q, "\\(", "\\)"))
            return 1;
    }
    else if (end_quotes(cmd, q, 0) != 0)
        return 1;
    return 0;
}

int mx_check_quotes(char *cmd) {
    for (int i = 0; cmd[i] != '\0'; i++) {
        if (strncmp(&cmd[i], "'", 1) == 0
            || cmd[i] == '"' ||  cmd[i] == '('
            || cmd[i] == ')' ||  cmd[i] == '{'
            || cmd[i] == '}' ||  cmd[i] == '`') {
            if (odd_quotes(cmd, cmd[i]) != 0)
                return 1;
        }
    }
    return 0;
}
