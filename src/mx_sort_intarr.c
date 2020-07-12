#include "ush.h"

int *mx_sort_intarr(int *arr) {
    int tmp = 0;

    for (int i = 0; arr[i] != -1; i++) {
        for (int j = i + 1; arr[j] != -1; j++) {
            if (arr[i] > arr[j]) {
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
    return arr;
}
