#include "ush.h"

static void pipe_or_file(t_config *term, char *file) {
    char line[8192];

    if (!isatty(0)) {
        memset(line, 0, 8192);
        read(0, line, 8192);
        term->n = mx_strlen(line);
        term->cmd = mx_strndup(line, term->n);
    }
    else
        term->cmd = mx_get_argv(file, NULL);
    mx_loop(term->cmd, term, (t_st *)term->st);
}

int main(int argc, char **argv, char **env) {
    t_config *term = mx_config_init();
    t_hist **hist = mx_hist_init();

    term->st = malloc(sizeof(t_st));
    mx_init_struct((t_st *)term->st, env);
    term->app = malloc(sizeof(t_app));
    mx_init((t_app *)term->app);
    if (!isatty(0) || argc > 1)
        pipe_or_file(term, argv[1]);
    else
        mx_lp(term, hist);
    //system("leaks -q ush");
    //return 0;
}
//    write (2, "here\n", 5);
//    signal(SIGTSTP, SIG_IGN);
//    signal(SIGINT, SIG_IGN);
//    signal(SIGSEGV, SIG_IGN);
