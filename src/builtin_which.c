#include "ush.h"

bool mx_is_commad(char *fullname, int flags) {
    struct stat st;

    if (stat(fullname, &st) != -1) { // finded
        if ((st.st_mode & S_IXUSR) == S_IXUSR) {
            if ((flags & 2) == 2) {
                free(fullname);
                return true;
            }

            mx_printstr(fullname);
            mx_printchar('\n');
            free(fullname);
            return true;
        }
    }
    free(fullname);
    return false;
}


static int get_flags(int *i, char **argv) {
    int flags = 0;

    while(argv[++(*i)])
        if (argv[*i][0] == '-') {
            for(int j = 1; j < mx_strlen(argv[*i]); j++)
                if (argv[*i][j] == 'a')
                    flags |= 1;
                else if(argv[*i][j] == 's')
                    flags |= 2;
                else {
                    fprintf(stderr,"which: bad option: -");
                    write(2, &argv[*i][j], 1);
                    write(2, "\n", 1);
                    return -1;
                }
        }
        else
            return flags;
    return flags;
}

/*
1 - return true;
0 - dont return;
*/
static int mx_check_buildin(char *command, int flags, bool *finded) {
    if (mx_is_buildin(command)) {
        if ((flags & 2) == 2)
            return 1;
        write(2, command, mx_strlen(command));
        write(2,": shell built-in command\n", mx_strlen(": shell built-in command\n"));
//        printf("%s: shell built-in command\n", command);
        *finded = true;
        if ((flags & 1) == 0)
            return 1;
    }
    return 0;
}


static bool check_command(char *command, char **pathes, int flags) {
    char *fullname = 0;
    bool finded = false;

    if (mx_check_buildin(command, flags, &finded) == 1)
        return true;
    if (command[0] == '/') {
        if (mx_is_commad(mx_strdup(command), flags))
            return true;
    }
    else {
        for(int i = 0; pathes[i]; i++) {
            fullname = mx_join(mx_strjoin(pathes[i], "/"), command);
           // printf("fullpath = %s\n", fullname);
            if (mx_is_commad(fullname, flags)) {
                if ((flags & 1) == 0)
                    return true;
                finded = true;
            }
        }
    }
    return finded;
}

static bool check_commands(char **commands, char** pathes, int start_index,
                           int flags) {
    int i = start_index - 1;
    bool finded = false;

    while(commands[++i]  != 0) {
        finded = check_command(commands[i], pathes, flags);
        if ((finded == false) && ((flags & 2) == 2))
            return false;
        if (finded == false)
            printf("%s not found\n", commands[i]);
        if (finded && ((flags & 1) == 0 || (flags & 2) == 2))
            return true;
    }
    return finded;
}

int mx_which(char **argv) {
  //  char *path = getenv("PATH");
  //  printf("%s\n", path);
    char **pathes = mx_strsplit(getenv("PATH"), ':');
    int i_args = 0;
    int flags = get_flags(&i_args, argv);
    int finded = false;

    if (flags == -1) {
        mx_del_strarr(&pathes);
        return 0;
    }
    finded = check_commands(argv, pathes, i_args, flags);
    mx_del_strarr(&pathes);
    if (finded)
        return 0;
    return 1;
}
