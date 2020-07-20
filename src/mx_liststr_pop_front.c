#include "ush.h"

void mx_liststr_pop_front(t_liststr **head) {
    if (head == NULL) return;
    if (*head == NULL) return;

    t_liststr *node = *head;
    *head = (*head)->next;
    mx_liststr_delete_node(node);
}

void mx_liststr_delete_node(t_liststr *node) {
    if (node == NULL)
        return ;
    if (node->key != NULL)
        free(node->key);
    if (node->value != NULL)
        free(node->value);
    free(node);
}
