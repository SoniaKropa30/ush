#include "ush.h"

int mx_simple_commands(t_st *st, char **commands, t_config* term) {
    for (int i = 0; commands[i] != NULL; i++) {
        if (i % 2 == 0 && commands[i][0] != '\0') {
            commands[i] = mx_replace_cmd(st, commands[i]);
            commands[i] = mx_command_sub(st, commands[i], NULL, term);
            st->status = mx_command_pars(st, commands[i], 0, term);
        }
        else {
            if ((commands[i][0] == '|' || commands[i][0] == '&')
                && (commands[i + 1][0] == '{' || commands[i + 1][0] == '('))
                i += mx_complex_cmd(st, commands, i, i);
            else if ((commands[i][0] == '|' && st->status == 0)
                || (commands[i][0] == '&' && st->status == 1))
                i += 2;
        }
    }
    return st->status;
}
