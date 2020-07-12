#include "ush.h"

static void out_print(t_st *st, FILE *f, int pipe, char *tmp) {
    int i = 0;

    for (; st->buf[pipe][i] != '\0'; i++);
    for (; st->buf[pipe][i] != '\n' && i > 0; i--);
    if (i > 0) {
        tmp = mx_strndup(st->buf[pipe], i);
        fprintf(f, "%s\n", tmp);
        mx_del_chararr(tmp);
    }
    if (st->fbuf[pipe] != NULL)
        fprintf(f, "%s", st->fbuf[pipe]);
}

void mx_file_output(t_st *st, int pipe) {
    FILE *begin;
    FILE *end;

    for (int i = 0; i < st->out[pipe]; i++) {
        if ((begin = fopen(st->output[pipe][i], "w")) == NULL)
            printf("ошибка из канала");
        out_print(st, begin, pipe, NULL);
        fclose(begin);
    }
    for (int i = 0; i < st->end[pipe]; i++) {
        if ((end = fopen(st->endout[pipe][i], "a")) == NULL)
            printf("ошибка из канала");
        out_print(st, end, pipe, NULL);
        fclose(end);
    }
}
