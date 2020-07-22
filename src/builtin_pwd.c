#include "ush.h"

static bool switch_flags(char *argv[], t_app *pwd) {
        for (int i = 1; argv[i] != NULL; i++) {
            if ((strcmp(argv[i], "--") == 0 && argv[i + 1]) ||
                (strcmp(argv[i], "-") == 0 && argv[i + 1]) ||
                    argv[i][0] != '-') {
                fprintf(stderr, "pwd: too many arguments\n");
                return false;
            }
            for (unsigned int j = 1; j < strlen(argv[i]); j++) {
                if (argv[i][j] == 'P')
                    pwd->flag_p = 1;
                else if ((argv[i][j] != 'P' && argv[i][j] != 'L'
                    && argv[i][j] != '-') || (argv[i][j] == '-' && j == 2)) {
                    fprintf(stderr, "pwd: bad option: -%c\n", argv[i][j]);
                    return false;
                }
            }
        }
        return true;
}

static void check_last_simbols(t_app *pwd) {
    char *buf = NULL;

      if(mx_get_substr_index(pwd->pwd_l, "/.") != -1) {
        buf = mx_replace_substr(pwd->pwd_l, "/.", "");
        free(pwd->pwd_l);
        pwd->pwd_l = mx_strdup(buf);
        mx_strdel(&buf);
      }
}

static void check_double_slesh(t_app *app) {
  char *buf = NULL;
  int i = 0;
  int len = mx_strlen(app->pwd_l);

    while (i < len) {
      if(app->pwd_l[i] == '/')
        i++;
      else
        break;
     
    }
    if(app->pwd_l[0] == '/' && app->pwd_l[1] == '/') {
      buf = mx_strndup(&app->pwd_l[i - 1], (mx_strlen(app->pwd_l) - i + 1));
        free(app->pwd_l);
        app->pwd_l = mx_strdup(buf);
        free(buf); 
    }
}

int mx_pwd_builtin(char *argv[], t_app *pwd) {
    pwd->flag_p = 0;
    if(switch_flags(argv,pwd)) {
      check_double_slesh(pwd);
      check_last_simbols(pwd);
      
    if (pwd->flag_p) {
        printf("%s\n", pwd->pwd_p);
    }
    else if (!pwd->flag_p) {
        printf("%s\n", pwd->pwd_l);
        }
    else
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;

}
