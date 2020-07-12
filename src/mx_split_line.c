#include "ush.h"

static char *split_tok(char *line, int i, int j, char delim) {
    char *token = NULL;
    char *tmp = NULL;

    if (delim == '\0' || delim == ';')
        token = strndup(&line[j], i - j);
    if (delim == '|' || delim == '&')
        token = strndup(&line[j], i - j - 1);
    tmp = token;
    token = mx_del_extra_spaces(token);
    mx_del_chararr(tmp);
    return token;
}

char **mx_split_line(char *line, int bufsize, int j, int k) {
    char **tokens = malloc(bufsize * sizeof(char *));

    for (int i = 0; j != -1; i++) {
        i = mx_ncounter(line[i], "|&\0", i, 2);
        if (i != 0 && (line[i] == '|' || line[i] == '&'
            || line[i] == ';' || line[i] == '\0')) {
            if (mx_check_slash(line, i) == 0) {
                tokens[k++] = split_tok(line, i, j, line[i]);
                tokens[k++] = strndup(&line[i], 1);
                j = i + 1;
            }
        }
        if (line[i] == '\0')
            j = -1;
        tokens = mx_split_backup(tokens, bufsize, k);
        if (k >= bufsize)
            bufsize += 64;
    }
    tokens[k] = NULL;
    return tokens;
}
