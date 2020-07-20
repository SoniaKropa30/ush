#include "ush.h"

// ----- Static Functions
static bool dir_or_not(char *path) {
    DIR* dir = opendir(path);

    if (!dir)
        return false;
    closedir(dir);
    return true;
}

static char *file_name_finding(char *path, char *name) {
    char cancat[PATH_MAX];
    char *file_name = NULL;

    if (path != NULL) {
        sprintf(cancat, "%s/%s", path, name);
        file_name = mx_strdup(cancat);
    }
    else
        file_name = mx_strdup(name);
    return file_name;
}

static void process_errors_env(char **arr) {
    int res = 0;

    if (dir_or_not(*arr)) {
        fprintf(stderr, "env: %s: %s\n", strerror(errno), *arr);
        res = 126;
    }
    else if (errno == ENOENT) {
        fprintf(stderr, "env: %s: %s\n", *arr, strerror(errno));
        res = 127;
    }
    else
        res = 1;
    _exit(res);
}

static void inside_the_process(char **arr, char *name, char *path) {
    int res = 0;

    if (path) {
        if (strchr(*arr, '/'))
            res = execv(*arr,  arr);
        else
            res = execv(name,  arr);
    }
    else
        res = execvp(name, arr);
    if (res == -1)
        process_errors_env(arr);
}

// ----    API Function
int mx_exec_env(char **arr, char *path) {
    char *file_name = file_name_finding(path, *arr);
    pid_t pid = fork();
    int status = 0;

    if (pid == -1)
        perror("fork");
    else if (pid == 0)
        inside_the_process(arr, file_name, path);
    else {
        wait(&status);
        if (MX_WIFEXIT(status))
            status = MX_WEXITSTATUS(status);
    }
    mx_strdel(&file_name);
    return status;
}


