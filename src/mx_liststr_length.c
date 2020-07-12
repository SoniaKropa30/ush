#include "ush.h"

int mx_liststr_length(t_liststr *head) {
    int count = 0;
    if (head != NULL) {
        for (t_liststr *cur = head; cur != NULL; cur = cur->next)
            count++;
    }
    return count;
}

