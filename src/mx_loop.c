#include "ush.h"

void mx_loop(char *cmd, t_config* term, t_st *st) {

    st->cmd = cmd;
    if (mx_check_quotes(st->cmd) == 1) {
        write(2, "Odd number of quotes.\n", 22);
        exit(1);
    }
    st->commands = mx_split_line(st->cmd, 64, 0, 0);
    st->status = mx_simple_commands(st, st->commands, term);
    fflush(stdin);
    fflush(stdout);
}
