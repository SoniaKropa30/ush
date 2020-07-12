#include "ush.h"

void mx_liststr_push_front(t_liststr **head, char *key, char *value) {
    if (head == NULL)
        return;

    t_liststr *new_n = mx_liststr_init(key, value);
    if (new_n == NULL)
        return;

    new_n->next = *head;
    *head = new_n;
}
