#include "ush.h"

static char *multinput(char *file, char *tmp, char *res) {
    FILE *mf;
    char line[4096];

    if ((mf = fopen(file, "r")) == NULL)
        printf("ошибка чтения из канала");
    while(!feof(mf))
        fgets(line, 4095, mf);
    fclose(mf);
    if (tmp != NULL) {
        res = mx_strjoin(tmp, line);
        mx_del_chararr(tmp);
    }
    else
        res = mx_strdup(line);
    return res;
}

char *mx_file_input(t_st *st, int pipe) {
    char *tmp = NULL;
    char *res = NULL;

    if (st->in[pipe] > 0) {
        for (int i = 0; i < st->in[pipe]; i++)
            tmp = multinput(st->input[pipe][i], tmp, NULL);
        if (st->fbuf[pipe - 1] != NULL && pipe > 0) {
            res = mx_strjoin(st->fbuf[pipe - 1], tmp);
            mx_del_chararr(tmp);
        }
        else
            res = tmp;
    }
    else if (st->fbuf[pipe - 1] != NULL && pipe > 0)
        res = mx_strdup(st->fbuf[pipe - 1]);
    return res;
}
