#include "ush.h"

int main(int argc, char **argv, char **env) {
    t_config *term = mx_config_init();
    t_hist **hist = (t_hist **)malloc(sizeof(t_hist) * 200);
    char line[8192];
    write (2, "here\n", 5);
//    signal(SIGTSTP, SIG_IGN);
//    signal(SIGINT, SIG_IGN);
//    signal(SIGSEGV, SIG_IGN);
    term->st = malloc(sizeof(t_st));
    mx_init_struct((t_st *)term->st, env);
    term->app = malloc(sizeof(t_app));
    mx_init((t_app *)term->app);

    if ((write(0, "\0", 1)) != 1) {
        memset(line, 0, 8192);
        read(0, line, 8192);
        term->n = mx_strlen(line);
        term->cmd = mx_strndup(line, term->n);
    }

    if (argc > 1 && term->cmd == NULL)
        term->cmd = mx_get_argv(argv[1], NULL);

    if (isatty(0)) {
        mx_lp(term, hist);
    }
    else {
        mx_loop(term->cmd, term, (t_st *)term->st);
        //write(2, "HERE\n", 5);
        dup2(0, STDIN_FILENO);
        dup2(1, STDOUT_FILENO);
        //execl("./ush", NULL);
//        exit(0);
        term = mx_config_init();
        mx_lp(term, hist);
    }
    //system("leaks -q ush");
    return 0;
}
