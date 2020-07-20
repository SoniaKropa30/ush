#include "ush.h"

bool mx_cmp_name(void *data1, void *data2) {
    if (mx_strcmp(data1, data2) > 0)
        return true;
    else
        return false;
}

void mx_sort_arr(char **arr, bool (*cmp)(void *, void*)) {
    int count = 0;
    int size;

    for (size = 0; arr[size] != NULL; size++);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (cmp(arr[j], arr[j + 1]) > 0) {
                count++;
                char *tmp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}
