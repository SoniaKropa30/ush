#include "ush.h"

static char **for_each_pipe(t_st *st, char **tokens, int k) {
    if ((st->in[k] = mx_count_streams(tokens, '<', 0, 0)) > 0)
        tokens = mx_streams_in(st, tokens, k, 0);
    if ((st->out[k] = mx_count_streams(tokens, '>', 0, 0)) > 0)
        tokens = mx_streams_out(st, tokens, k, 0);
    if ((st->end[k] = mx_count_streams(tokens, '>', 0, 1)) > 0)
        tokens = mx_streams_endout(st, tokens, k, 0);
    return tokens;
}

static void streams_get_midl(t_st *st, int n) {
    st->input = (char ***)malloc(sizeof(char **) * (n + 1));
    st->input[n] = NULL;
    st->output = (char ***)malloc(sizeof(char **) * (n + 1));
    st->output[n] = NULL;
    st->endout = (char ***)malloc(sizeof(char **) * (n + 1));
    st->endout[n] = NULL;
    st->in = malloc(sizeof(int) * n);
    st->out = malloc(sizeof(int) * n);
    st->end = malloc(sizeof(int) * n);
    st->buf = malloc(sizeof(char *) * (n + 1));
    st->buf[n] = NULL;
    st->fbuf = malloc(sizeof(char *) * (n + 1));
    st->fbuf[n] = NULL;
}

char ***mx_streams_get(t_st *st, char **tokens) {
    int n = mx_count_pipes(st, tokens) + 1;
    char ***tok = (char ***)malloc(sizeof(char **) * (n + 1));
    char **tmp = NULL;

    tok[n] = NULL;
    streams_get_midl(st, n);
    for (int i = 0; i < n; i++) {
        st->buf[i] = NULL;
        st->fbuf[i] = NULL;
        tmp = mx_get_cmd_tok(st, tokens, i, st->pipes[i]);
        tok[i] = for_each_pipe(st, tmp, i);
    }
    mx_del_strarr(&tokens);
    return tok;
}
