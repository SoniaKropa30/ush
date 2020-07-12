#include "ush.h"

bool mx_is_buildin(char *str) {
    if (str == 0)
        return 0;
    if ((strcmp(str, "cd") == 0)
        || (strcmp(str, "pwd") == 0)
        || (strcmp(str, "env") == 0)
        || (strcmp(str, "which") == 0)
        || (strcmp(str, "echo") == 0)
        || (strcmp(str, "export") == 0)
        || (strcmp(str, "unset") == 0)
        || (strcmp(str, "fg") == 0)
        || (strcmp(str, "exit") == 0)
        || (strcmp(str, "jobs") == 0)
        || (strcmp(str, "history") == 0)) {
        return true;
    }
    return false;
}
