#include "ush.h"
static int *init_fl() {
    int *fl = malloc(4);

    for(int i =  0; i < 4; i++) {
        fl[i] = 0;
    }
    return fl;
}
//fl[0] = s;
//fl[1] = p;
//fl[2] = dash;
//fl[3] = home;
static int *standart_check_flags(char *argv[], t_app *app, int *fl) {
    for (app->cur_arg = 1; argv[app->cur_arg] != NULL; app->cur_arg++) {
        if (strcmp(argv[app->cur_arg], "-") == 0) {
            fl[2] = 1;
            return fl;
        }
        else {
            for (int j = 1; j < mx_strlen(argv[app->cur_arg]); j++) {
                if (argv[app->cur_arg][j] == 's')
                    fl[0] = 1;
                else if (argv[app->cur_arg][j] == 'P')
                    fl[1] = fl[0] == 1 ? 0 : 1;
                else {
                    return fl;
                }
            }
        }
    }
    return fl;
}

static int *get_flags(char *argv[], t_app *app) {
    int *fl = init_fl();
    app->cur_arg = 0;

    if(argv[1] && argv[1][0] != '-') {
        app->cur_arg = 1;
        return fl;
    }
    else if (argv[1] && strcmp(argv[1], "--") == 0 && !argv[2]) {
        app->cur_arg = 2;
        fl[3] = 1;
        return fl;
    }
    else if (argv[1]) {
        fl = standart_check_flags(argv, app, fl);
        return fl;
    }
    return fl;
}

static int check_arg(char *argv[], t_app *app, int *f) {
    char *our = f[1] ? strstr(app->pwd_p, argv[app->cur_arg]) :
            strstr(app->pwd_l, argv[app->cur_arg]) ;
    if (our != NULL && mx_strcmp(argv[app->cur_arg], our) == 0)
        app->in_pwd = 1;
    else
        app->in_pwd = 0;

    if ((argv[app->cur_arg] && argv[app->cur_arg + 1]
            && !argv[app->cur_arg + 2] && !app->in_pwd) ||
            (strcmp(argv[app->cur_arg], "-") == 0 && argv[app->cur_arg + 1])) {
            fprintf(stderr, "cd: string not in pwd: %s\n", argv[app->cur_arg]);
            return -1;
        }
    else if (argv[app->cur_arg] && argv[app->cur_arg + 2]){
        fprintf(stderr, "cd: too many arguments\n");
        return -1;
    }
    else if (app->in_pwd && argv[app->cur_arg + 1]) { // todo output ~...
        app->cur_arg++;
    }
    return 0;
}

int mx_cd_builtin(char *argv[], t_app *app) {
    int *flag = get_flags(argv, app);

   if(!argv[1] || argv[app->cur_arg] == NULL  || flag[3] == 1) {
       mx_swap_pwd(app->home, argv, app);
   }
   else if (argv[app->cur_arg] && check_arg(argv, app, flag) == 0) {
       if (mx_is_link(argv[app->cur_arg]) == 1 && flag[0] == 1)
           fprintf(stderr, "cd: not a directory: %s\n", argv[app->cur_arg]);
       else if(flag[1] == 1) {
           if (mx_cd_p(argv, app, flag) == 0) {
               app->pwd_l = app->pwd_p;
               setenv("PWD", app->pwd_l, 1);
               return EXIT_SUCCESS;
           }
       }
       else if (flag[1] == 0) {
           if (mx_cd_l(argv, app, flag) == 0) {
               setenv("PWD", app->pwd_l, 1);
               return EXIT_SUCCESS;
           }

       }
   }
    return EXIT_FAILURE;
}