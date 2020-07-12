#include "ush.h"

int mx_complex_cmd(t_st *st, char **commands, int cur, int passed_cmd) {
    int open = 0;
    int close = 0;

    if ((commands[cur][0] == '&' && st->status == 1)
        || (commands[cur][0] == '|' && st->status == 0)) {
        for (; commands[cur + 1] != NULL; cur += 2) {
            for (int i = 0; commands[cur + 1][i] != '\0'; i++) {
                open = mx_counter(commands[cur + 1][i], '{', open);
                open = mx_counter(commands[cur + 1][i], '(', open);
                close = mx_counter(commands[cur + 1][i], '}', close);
                close = mx_counter(commands[cur + 1][i], ')', close);
            }
            if (close - open == 0)
                break;
        }
        cur = cur - passed_cmd + 2;
        return cur;
    }
    return 0;
}
