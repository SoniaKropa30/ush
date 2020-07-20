#include "ush.h"

int mx_any_count(char c) {
    if (c == '"' || c == 39 || c == '`' || c == '(' || c == ')' || c == '{'
        || c == '}' || c == ' ' || c == '$')
        return 1;
    return 0;
}
