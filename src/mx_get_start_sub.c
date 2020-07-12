#include "ush.h"

int mx_get_start_sub(char *cmd) {
    int scopes = 0;
    int n = 0;

    for (int i = 0; cmd[i + 1] != '\0'; i++) {
        scopes = mx_xcombcounter(cmd[i], cmd[i + 1], "\\'", scopes);
        n = mx_combcounter(cmd[i], cmd[i + 1], "$(", n);
        n = mx_counter(cmd[i], '`', n);
        if (n != 0 && scopes % 2 == 0)
            return i;
    }
    return -1;
}
