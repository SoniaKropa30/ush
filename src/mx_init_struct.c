#include "ush.h"

char **mx_set_arr() {
    char **arr = (char**)malloc(sizeof(char*) * 2);

    arr[0] = mx_strdup("111='777 777'");
    arr[1] = NULL;
    return arr;
}

char **mx_alias_arr() {
    char **arr = (char**)malloc(sizeof(char*) * 3);

    arr[0] = mx_strdup("abcabcabc='echo A'");
    arr[1] = mx_strdup("fc='echo fuck'");
    arr[2] = NULL;
    return arr;
}

void mx_init_struct(t_st *st, char **env) {

    st->env = env;
    st->set = mx_set_arr();
    st->alias = mx_alias_arr();
    st->status = 0;

//    st->pwd = mx_strdup(getenv("PWD"));
//    st->pwd_p = getcwd(NULL, 0);
//    st->pwd_l = mx_strdup(st->pwd);
//    st->pwd_old = mx_strdup(getenv("OLDPWD"));
//    st->pwd_home = mx_strdup(getenv("HOME"));
//    signal(SIGSEGV, mx_segfault_in);
//    signal(SIGINT, mx_ctrl_c);
//    signal(SIGTSTP, mx_ctrl_z);
}
