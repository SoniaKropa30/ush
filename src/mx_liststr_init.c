#include "ush.h"

t_liststr *mx_liststr_init(char *key, char *value) {
    t_liststr *p = malloc(sizeof(t_liststr));
    
    if (p == NULL) return NULL;
    p->key = NULL;
    p->value = NULL;
    if (key != NULL)
        p->key = strdup(key);
    if (value != NULL)
        p->value = strdup(value);
    p->next = NULL;
    return p;
}
