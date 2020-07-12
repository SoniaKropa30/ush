#include "ush.h"

void mx_del_conveer(t_st *st) {
    if (st->in)
        free(st->in);
    if (st->out)
        free(st->out);
    if (st->end)
        free(st->end);
    if (st->pipes)
        free(st->pipes);
    if (st->fbuf)
        mx_del_strarr(&st->fbuf);
    if (st->buf)
        mx_del_strarr(&st->buf);
    for (int i = 0; st->input[i] != NULL; i++)
        mx_del_strarr(&st->input[i]);
    for (int i = 0; st->output[i] != NULL; i++)
        mx_del_strarr(&st->output[i]);
    for (int i = 0; st->endout[i] != NULL; i++)
        mx_del_strarr(&st->endout[i]);
}
