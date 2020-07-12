#include "ush.h"

static int count_endout(char **tokens) {
    int i = 0;

    for (; tokens[i] != NULL; i++);
    return i;
}

char **mx_streams_endout(t_st *st, char **tokens, int pipe, int j) {
    int n = st->end[pipe];
    char **tok = NULL;
    int i = count_endout(tokens);

    tok = (char **)malloc(sizeof(char *) * ((i - (n * 3)) + 1));
    tok[i - (n * 3)] = NULL;
    st->endout[pipe] = (char **)malloc(sizeof(char *) * (n + 1));
    st->endout[pipe][n] = NULL;
    n = 0;
    for (i = 0; tokens[i] != NULL; i++) {
        if (!(((tokens[i][0] == '>' && i == 0)
            || (tokens[i][0] == '>' && tokens[i - 1][0] != '>'))
            && tokens[i + 2] != NULL && tokens[i + 1][0] == '>'))
            tok[n++] = mx_strdup(tokens[i]);
        else {
            st->endout[pipe][j++] = mx_strdup(tokens[i + 2]);
            i += 2;
        }
    }
    return tok;
}
