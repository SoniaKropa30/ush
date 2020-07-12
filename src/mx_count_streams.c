#include "ush.h"

int mx_count_streams(char **tokens, char c, int n, int dubl) {
    if (dubl == 0) {
        for (int i = 0; tokens[i] != NULL && tokens[i][0] != '|'; i++) {
            if (((tokens[i][0] == c && i == 0)
                 || (tokens[i][0] == c && tokens[i - 1][0] != c))
                && tokens[i + 1] != NULL && tokens[i + 1][0] != c)
                n++;
        }
    }
    else {
        for (int i = 0; tokens[i] != NULL; i++) {
            if (((tokens[i][0] == c && i == 0)
                 || (tokens[i][0] == c && tokens[i - 1][0] != c))
                && tokens[i + 2] != NULL && tokens[i + 1][0] == c)
                n++;
        }
    }
    return n;
}
