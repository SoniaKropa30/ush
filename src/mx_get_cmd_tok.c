#include "ush.h"

char **mx_get_cmd_tok(t_st *st, char **tokens, int start, int end) {
    char **tok = NULL;
    int n = 0;

    if (start != 0)
        start = st->pipes[start - 1];
    start = mx_counter(tokens[start][0], '|', start);
    n = end - start;
    tok = (char **)malloc(sizeof(char *) * (n + 1));
    tok[n] = NULL;
    for (int i = 0; i < n && tokens[start] != NULL; i++)
        tok[i] = mx_strdup(tokens[start++]);
    return tok;
}
