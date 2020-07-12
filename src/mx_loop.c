#include "ush.h"

void mx_loop(char *cmd, t_config* term, t_st *st) {

    st->cmd = cmd;
    mx_check_quotes(st);
    st->commands = mx_split_line(st->cmd, 64, 0, 0);
    st->status = mx_simple_commands(st, st->commands, term);
}
