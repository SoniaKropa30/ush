#include "ush.h"

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
