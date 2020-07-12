#include "ush.h"

static t_environment *mx_env_lookup_key(char *key, t_environment *env) {
    if (key == NULL)
        return NULL;
    for (t_environment *cur = env; cur != NULL; cur = cur->next) {
        if (strcmp(cur->key, key) == 0)
            return cur;
    }
    return NULL;
}

void mx_env_set_var(char *key, char *value, t_environment **env) {
    t_environment *res = mx_env_lookup_key(key, *env);
    if (res != NULL) {
        char *tmp = res->value;
        res->value = strdup(value);
        free(tmp);
    }
    else
        mx_liststr_push_front(env, key, value);
}

void mx_env_del_var(char *key, t_environment **env) {
    t_environment *temp = *env;
    t_environment *prev = NULL;

    if (temp != NULL && strcmp(key, temp->key) == 0) {
        *env = temp->next;
        free(temp->key);
        free(temp->value);
        free(temp);
        return;
    }
    while (temp != NULL &&  strcmp(key, temp->key) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return;
    prev->next = temp->next;
    free(temp->key);
    free(temp->value);
    free(temp);
}
