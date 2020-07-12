#include "ush.h"

int lsh_cd(char **args);
int lsh_exit(char **args);

char *builtin_str[] = {
        "cd",
        "exit"
};

int (*builtin_func[]) (char **) = {
        &lsh_cd,
        &lsh_exit
};

int lsh_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

int lsh_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "ush: expected argument to \"cd\"\n");
    }
    else {
        if (chdir(args[1]) != 0)
            perror("ush");
    }
    return 1;
}

int lsh_exit(char **args) {
    args[0] = args[0];
    return 0;
}

int lsh_launch(t_st *st, char **args) {
    pid_t pid;

    pid = fork();
    if (pid == 0) {
//        for (int i = 0; args[i] != NULL; i++) {
//            write(2, args[i], mx_strlen(args[i]));
//            write(2, "\n", 1);
//        }
//        write(2, "\n", 1);
        if ((st->status = execvp(args[0], args)) == -1)
            perror("ush");


        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
        perror("ush");
    while (!WIFEXITED(st->status) && !WIFSIGNALED(st->status))
        waitpid(pid, &st->status, WUNTRACED);
    return st->status;
}

int mx_final_exe(t_st *st, char **args) {
    int i;

    if (args[0] == NULL) // An empty command was entered.
        return 1;
    for (i = 0; i < lsh_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0)
            return (*builtin_func[i])(args);
    }
    return lsh_launch(st, args);
}
