#include "ush.h"

int mx_count_pipes(t_st *st, char **tokens) {
    int k = 0;
    int n = 0;

    st->pipe = 0;
    st->pipes = NULL;
    for (; tokens[n] != NULL; n++) {
        if (tokens[n][0] == '|' && tokens[n][1] == '\0')
            st->pipe++;
    }
    st->pipes = malloc((st->pipe + 1) * sizeof(int));
    st->pipes[st->pipe] = n;
    for (int i = 0; st->pipe != 0 && tokens[i] != NULL; i++) {
        if (tokens[i][0] == '|' && tokens[i][1] == '\0')
            st->pipes[k++] = i;
    }
    return st->pipe;
}
