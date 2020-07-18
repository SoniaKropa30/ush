#include "ush.h"

void mx_write_hist(int len, char *str) {
    char *tmp = mx_strndup(str, len);
    FILE * fp;

    fp = fopen (".history.txt", "a");
    fprintf(fp, "%s\t", tmp);
    fclose(fp);
    free(tmp);
}
