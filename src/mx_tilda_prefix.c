#include "ush.h"

static char *check_homedirs(char *prefix) {
    DIR *ddir;
    struct dirent *dirptr;
    struct stat buff;
    char *path = NULL;

    ddir = opendir("/Users");
    while ((dirptr = readdir(ddir)) != NULL) {
        path = mx_strjoin("/Users/", dirptr->d_name);
        lstat(path, &buff);
        if (strcmp(dirptr->d_name, prefix) == 0
            && buff.st_mode & S_IFDIR) {
            closedir(ddir);
            return path;
        }
        mx_del_chararr(path);
    }
    closedir(ddir);
    return NULL;
}

static char *make_change(char *cmd, int tilda, char *res, int prefix) {
    char *head = NULL;
    char *midl = NULL;
    char *tail = NULL;

    if (tilda != 0)
        head = mx_strndup(cmd, tilda);
    midl = mx_strjoin(head, res);
    tail = mx_strdup(&cmd[tilda + prefix + 1]);
    mx_del_chararr(cmd);
    cmd = mx_strjoin(midl, tail);
    mx_del_chararr(head);
    mx_del_chararr(midl);
    mx_del_chararr(tail);
    mx_del_chararr(res);
    return cmd;
}

char *mx_tilda_prefix(int start, char *cmd) {
    int end = strcspn(&cmd[start + 1], " /\0") + start;
    char *prefix = mx_strndup(&cmd[start + 1], end - start);
    int n = mx_strlen(prefix);
    char *res = NULL;

    if ((res = check_homedirs(prefix)) != NULL)
        cmd = make_change(cmd, start, res, n);
    else {
        write(2, "ush: no such user or named directory: ", 38);
        write(2, prefix, n);
        write(2, "\n", 1);
        exit(1);
    }
    mx_del_chararr(prefix);
    return cmd;
}
