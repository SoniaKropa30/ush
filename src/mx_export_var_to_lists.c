#include "ush.h"

static void add_var_to_lists(char *arg, t_app *gv){
    if (strchr(arg, '=')) {
        char *name = mx_get_env_name(arg);
        char *value = mx_get_env_value(arg);

        mx_env_set_var(name, value, &gv->vars);
        mx_strdel(&name);
        mx_strdel(&value);
    }
    else
        mx_env_set_var(arg, NULL, &gv->vars);
}

void mx_export_var_to_lists(char *arg, t_app *gv) {
    t_environment *current = gv->vars;
    char *arg_name = mx_get_env_name(arg);
    char *var_name = NULL;

    while (current) {
        var_name = current->key;
        if (strcmp(arg_name, var_name) == 0) {
            setenv(current->key, current->value,1);
            break;
        }
        current = current->next;
    }
    if (!current)
        add_var_to_lists(arg, gv);
    mx_strdel(&arg_name);
}
