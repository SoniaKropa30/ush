#include "ush.h"

void mx_putenv(char *var) {
    static char name[1024];
    static char val[1024];
    char *received_name = mx_get_env_name(var);
    char *received_val = mx_get_env_value(var);

    sprintf(name, "%s", received_name);
    sprintf(val, "%s", received_val);
    setenv(name, val, 1);
    mx_strdel(&received_name);
    mx_strdel(&received_val);
}

void mx_env_fill(char **src) {
    mx_clearenv();
    for (int i = 0; src[i]; i++)
        mx_putenv(src[i]);
}

void mx_print_env(void) {
    extern char **environ;
//    printf("hello\n");
    mx_print_strarr(environ, "\n");
}

void mx_clearenv(void) {
    extern char **environ;
    char **vars_to_del = NULL;
    char *delname = NULL;

    if (environ[0] != NULL) {
        vars_to_del = mx_environ_copy();
        for (int i = 0; vars_to_del[i]; i++) {
            delname = mx_get_env_name(vars_to_del[i]);
            unsetenv(delname);
            mx_strdel(&delname);
        }
        mx_del_strarr(&vars_to_del);
    }
}
