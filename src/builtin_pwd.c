#include "ush.h"

static bool switch_flags(char *argv[], t_app *pwd) {
        for (int i = 1; argv[i] != NULL; i++) {
            if ((strcmp(argv[i], "--") == 0 && argv[i + 1]) ||
                (strcmp(argv[i], "-") == 0 && argv[i + 1]) ||
                    argv[i][0] != '-') {
                fprintf(stderr, "pwd: too many arguments\n"); //todo check \n
                return false;
            }
            for (int j = 1; j < strlen(argv[i]); j++) {
                if (argv[i][j] == 'P')
                    pwd->flag_p = 1;
                else if ((argv[i][j] != 'P' && argv[i][j] != 'L'
                    && argv[i][j] != '-') || (argv[i][j] == '-' && j == 2)) {
                    fprintf(stderr, "pwd: bad option: -%c\n", argv[i][j]);//todo check \n
                    return false;
                }
            }
        }
        return true;
}


int mx_pwd_builtin(char *argv[], t_app *pwd) {
    pwd->flag_p = 0;
    if(switch_flags(argv,pwd)) {

    if (pwd->flag_p) {
        write (1, pwd->pwd_p, mx_strlen(pwd->pwd_p));
        //printf("%s\n", pwd->pwd_p);//todo how to validate?
    }
    else if (!pwd->flag_p) {
        write (1, pwd->pwd_l, mx_strlen(pwd->pwd_l));
        //printf("%s\n", pwd->pwd_l);//todo how to validate?
        }
    else
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;

}

//system("leaks ush");