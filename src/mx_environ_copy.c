#include "ush.h"

static void copying(char **copy, char **environ) {
    for (int i = 0; environ[i]; i++) {
        copy[i] = strdup(environ[i]);
        if (environ[i + 1] == NULL)
            copy[i + 1] = NULL;
    }
}

char **mx_environ_copy(void) {
    extern char **environ;
    char **env_copy = NULL;
    int len;

    for (len = 0; environ[len]; len++);
    env_copy = malloc((len + 1) * sizeof(char*));
    copying(env_copy, environ);
    return env_copy;
}
