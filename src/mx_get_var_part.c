//
// Created by Pavlo Symonov on 3/6/20.
//

#include "ush.h"

char *mx_get_env_name(char *var) {
    if (var != NULL)
        return strndup(var, mx_get_char_index(var, '='));
    return NULL;
}

char *mx_get_env_value(char *var) {
    if (var != NULL)
        return strdup(var + mx_get_char_index(var, '=') + 1);
    return NULL;
}
