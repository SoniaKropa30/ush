#include "ush.h"

void mx_init (t_app *pwd) {
    pwd->home = getenv("HOME");
    pwd->pwd_l = getenv("PWD");
    pwd->pwd_p = getwd(NULL);
    pwd->old_pwd_p = pwd->pwd_p;
}

