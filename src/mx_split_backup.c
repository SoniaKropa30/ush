#include "ush.h"

char **mx_split_backup(char **tokens, int bufsize, int k) {
    char **tokens_backup = NULL;

    if (k >= bufsize) {
        bufsize += 64;
        tokens_backup = tokens;
        tokens = realloc(tokens, bufsize * sizeof(char *));
        if (!tokens) {
            free(tokens_backup);
            mx_malloc_err();
        }
        return tokens;
    }
    return tokens;
}
