#include "ush.h"

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
