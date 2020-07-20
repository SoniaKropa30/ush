#include "ush.h"

static bool check_sound(char *out) {
    for (int i = 0; out[i] != '\0'; i++)
        if (out[i] != '\a')
            return false;
    return true;
}

static void switch_flags(char *argv[], t_app *app) {
    if (argv[1] == NULL || argv[1][0] != '-')
        app->echo_start_of_file = 1;
    else {
        for (int i = 1; argv[i] != NULL && argv[i][0] == '-'; i++) {
            for (unsigned int j = 1; j < strlen(argv[i]); j++) {
                if (argv[i][j] == 'n')
                    app->echo_flag_n = 1;
                else if (argv[i][j] == 'e')
                    app->echo_flag_E = 0;
                else if (argv[i][j] == 'E')
                    app->echo_flag_E = 1;
                else {
                    app->echo_start_of_file = i;
                    return;
                }
            }
            app->echo_start_of_file = i + 1;
        }
    }
}

static void print_new_line(t_app *app) {
    if(!app->echo_flag_n) {
        if(app->echo_only_sound)
            return;
        // else if (isatty(1))
        //     printf("\x1b[0;47;30m%%\x1b[0m\n");
    }
    else 
        mx_printstr("\n");

}

// static void cheсk_quotes(char *argv[]) {
//     char *buf = NULL;
//     int arr_len = mx_arr_len(argv);
//     int len_last_str = mx_strlen(argv[arr_len]);

//     if(argv[1][0] == '"' && argv[arr_len][len_last_str - 1] == '"') {
//         buf = mx_strndup(&argv[1][1], argv[arr_len][len_last_str - 2] == '"');
//         mx_strdel(&argv[1]);
//         argv[1] = mx_strdup(buf);
//         mx_strdel(&buf);
//         buf = mx_strndup(&argv[arr_len], argv[arr_len][len_last_str - 2]);
//         mx_strdel(&argv[arr_len]);
//         mx_strdel(&buf);
//     }
//     else
//         return;    
// }       

int mx_echo_builtin(char *argv[], t_app *app) {
    char *checked_argv = NULL;
    //  printf("argv[i] = %s\n", argv[app->echo_start_of_file]);
    // cheсk_quotes(argv);
    switch_flags(argv, app);
    if (argv[app->echo_start_of_file] != NULL){
            for (int i = app->echo_start_of_file; argv[i] != NULL; i++) {
                if(app->echo_flag_E)
                    mx_printstr(argv[i]);
                else {
                    checked_argv = mx_control_chars(argv[i]);
                    mx_printstr(checked_argv);
                    mx_strdel(&checked_argv);
                    app->echo_only_sound = check_sound(checked_argv);
                }
                if(argv[i+1])
                    mx_printchar(' ');
            }
    }
    print_new_line(app);
    return EXIT_SUCCESS;
}


