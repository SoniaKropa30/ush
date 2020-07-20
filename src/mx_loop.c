#include "ush.h"

// static void shlvl_check() {
//     tmp = getenv("SHLVL");
//     if (tmp == NULL)
//         setenv("SHLVL", "1", 1);
//     else {
//         n = atoi(tmp);
//         n++;
//         sprintf(tmp, "%d", n);
//         setenv("SHLVL", tmp, 1);
//     }
// }

void mx_loop(char *cmd, t_config* term, t_st *st) {

    st->cmd = cmd;
    //printf("%s\n", cmd);
    // if (mx_strcmp(cmd, "./ush") == 0)
    //     shlvl_check();
    if (mx_check_quotes(st->cmd) == 1) {
        write(2, "Odd number of quotes.\n", 22);
        exit(1);
    }
    st->commands = mx_split_line(st->cmd, 64, 0, 0);
    st->status = mx_simple_commands(st, st->commands, term);
    fflush(stdin);
    fflush(stdout);
}
