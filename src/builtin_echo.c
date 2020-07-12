#include "ush.h"

static void switch_flags(char *argv[], t_echo *echo) {
    if(argv[1] == NULL || argv[1][0] != '-' )
        echo->start_of_file = 1;
    else {
        for (int i = 1; argv[i] != NULL && argv[i][0] == '-'; i++) {
            for (int j = 1; j < strlen(argv[i]); j++) {
                if (argv[i][j] == 'n')
                    echo->flag_n = 1;
                else if (argv[i][j] == 'e')
                    echo->flag_e = 1;
                else if (argv[i][j] == 'E')
                    echo->flag_E = 1;
                else {
                    echo->start_of_file = i;
                    return;
                }
            }
            echo->start_of_file = i + 1;
        }
    }
}

int mx_echo_builtin(char *argv[]) {
    t_echo *echo  = malloc(sizeof(t_echo));
    switch_flags(argv, echo);
    //check-slash
    //print echo
    if (argv[echo->start_of_file] != NULL){
            for (int i = echo->start_of_file; argv[i] != NULL; i++) {
                if (argv[i + 1] != NULL)
                    printf("%s ", argv[i]);
                else {
                    if (!echo->flag_n)
                        printf("%s\n", argv[i]); // + \n from terminal
                    else
                        printf("%s%c\n", argv[i], '%'); //% надо вставлять?
                }
            }
    }
    else
        echo->flag_n == 0 ? printf("\n") : printf ("");
    free(echo);

    return EXIT_SUCCESS;
}

//system("leaks ush");
//доделать вывод со слэшами и ~ (username);