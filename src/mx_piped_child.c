#include "ush.h"

void mx_piped_child(t_st *st, char **tokens, t_config* term) {
    close(st->fd0[1]);
    close(st->fd1[0]);

    if (st->fd0[0] != STDIN_FILENO) {
        if (dup2(st->fd0[0], STDIN_FILENO) != STDIN_FILENO)
            printf("ошибка вызова функции dup2 для stdin");
        close(st->fd0[0]);
    }
    if (st->fd1[1] != STDOUT_FILENO) {
        if (dup2(st->fd1[1], STDOUT_FILENO) != STDOUT_FILENO)
            printf("ошибка вызова функции dup2 для stdout");
        close(st->fd1[1]);
    }
    st->status = mx_streams(st, tokens, (t_app *)term->app);
    exit(st->status);
}
