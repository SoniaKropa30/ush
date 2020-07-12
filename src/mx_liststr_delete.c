#include "ush.h"

void mx_liststr_delete(t_liststr **head) {
    if (head == NULL)
        return ;
    while (*head != NULL)
        mx_liststr_pop_front(head);
}
