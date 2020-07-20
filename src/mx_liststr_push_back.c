#include "ush.h"

void mx_liststr_push_back(t_liststr **head, char *key, char *value) {
    t_liststr *cur;
    t_liststr *new_n;
    
    if (head == NULL)
        return;

    if (*head == NULL) {  // if list is empty
        mx_liststr_push_front(head, key, value);
        return;
    }
    
    new_n = mx_liststr_init(key, value);
    if (new_n == NULL)
        return;
    
    for (cur = *head; cur->next != NULL; cur = cur->next)
        ;
    cur->next = new_n;
    new_n->next = NULL;
}
