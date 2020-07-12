#include "ush.h"

bool mx_is_link(char *file) {
    struct stat buf;

    if (lstat(file, &buf) == -1)
        return false;
    if ((buf.st_mode & S_IFLNK) == S_IFLNK)
        return true;
    return false;
}
