#include "ush.h"

static int get_flags(char *argv[], int *i) {
    int flag = 0;

    while(argv[(*i)]) {
        if(argv[*i][0] =='-') {
            for (int j = 1; j < mx_strlen(argv[*i]) && flag != -1; j++) {
                if (argv[*i][j] == 's')
                    flag = 1;
                else if(argv[*i][j] == 'a')
                    flag = (flag == 1) ? 1 : 2;
                else {
                    fprintf(stderr, "which: bad option: -%c\n", argv[*i][j]);
                    flag = -1;
                }
            }
            ++(*i);
        }
        else
            return flag;
    }
    return flag;
}

//-1 = bad option;
//0 = standart output;
//1 = flag "s";
//2 = flag "a";

static bool is_command(char *str) {
    struct stat st;

    if (stat(str, &st) != -1) {
        if ((st.st_mode & S_IXUSR) == S_IXUSR) {
            return true;
        }
    }
    free(str);
    return false;
}

static char *search_in_bin(char *argv, char **split_path) {
    char *full_dir;

    for(int i = 0; split_path[i]; i++) {
        full_dir = mx_join_to_path(mx_strjoin(split_path[i], "/"), argv);
        if (is_command(full_dir)) {
            return full_dir;
        }
    }
    return NULL;
}

static void print_which(char *argv, int flag, t_app *app) { // what about nout found commands?? now I just don't print them
    if(app->wch_is_biltin || app->in_bin) {
        if (flag == 1)
            return;
        if (flag == 0) {
            if (app->wch_is_biltin)
                printf("%s: shell built-in command\n", argv);
            else
                printf("%s\n", app->in_bin);
        }
        else if (flag == 2) {
            if (app->wch_is_biltin)
                printf("%s: shell built-in command\n", argv);
            if (app->in_bin)
                printf("%s\n", app->in_bin);
        }
    }
}


int mx_which(char *argv[], t_app *app) {
    char **spl_path = mx_strsplit(getenv("PATH"), ':');
    int index_of_command = 1;
    int flag = 0;
    int not_found = 0;

    if (!argv[1]) {
        fprintf(stderr, "usage: which [-as] program ...\n");
        return 1;
    }
    flag = get_flags(argv, &index_of_command);
    for (int i = index_of_command; argv[i] != NULL; i++) {
        app->wch_is_biltin = mx_is_builtin(argv[i]);
        app->in_bin = search_in_bin(argv[i], spl_path);
        if((!app->in_bin && !app->wch_is_biltin) || flag == -1)
            not_found = 1;
        print_which(argv[i], flag, app);
    }
    mx_del_strarr(&spl_path);
return not_found;
}


// printf("return = %d\n", not_found);
//printf("fl = %d\n", flag);
//printf("ind_of_com = %s\n", argv[i]);
//printf("app->in_bin = %s\n",  app->in_bin);
//printf("app->wch_is_biltin = %d\n", app->wch_is_biltin);


