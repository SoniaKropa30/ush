#include "ush.h"

static void check_replace(char **argv, char *str, char *repl_char) {
    char *res = mx_strdup(*argv);
    char *repl = mx_strdup(repl_char);
    
    if(mx_get_substr_index(*argv, str) != -1) {
        mx_strdel(argv);
        *argv = mx_replace_substr(res, str, repl);
    }
    mx_strdel(&res);
    mx_strdel(&repl);
}

static void continue_constrol_chars(char **after_repl) {
    check_replace(after_repl, "\\x09", "\t");
    check_replace(after_repl, "\\x00", "\0");
    check_replace(after_repl, "\\x07", "\a");
    check_replace(after_repl, "\\x08", "\b");
    check_replace(after_repl, "\\x0a", "\n");
    check_replace(after_repl, "\\x0b", "\v");
    check_replace(after_repl, "\\x0c", "\f");
    check_replace(after_repl, "\\x0d", "\r");
    check_replace(after_repl, "\\x1b", "\033");
    check_replace(after_repl, "\\011", "\t");
    check_replace(after_repl, "\\000", "\0");
    check_replace(after_repl, "\\007", "\a");
    check_replace(after_repl, "\\010", "\b");
    check_replace(after_repl, "\\012", "\n");
    check_replace(after_repl, "\\013", "\v");
    check_replace(after_repl, "\\014", "\f");
    check_replace(after_repl, "\\015", "\r");
    check_replace(after_repl, "\\0", "\0");
}

char *mx_control_chars(char *argv) {
    char *after_repl = mx_strdup(argv);  

    check_replace(&after_repl, "\\t", "\t");
    check_replace(&after_repl, "\\n", "\n");
    check_replace(&after_repl, "\\v", "\v");
    check_replace(&after_repl, "\\r", "\r");
    check_replace(&after_repl, "\\b", "\b");
    check_replace(&after_repl, "\\a", "\a");
    check_replace(&after_repl, "\\e", "\033");
    continue_constrol_chars(&after_repl);
    return after_repl;
}

