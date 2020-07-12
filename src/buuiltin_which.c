//#include "ush.h"
//
//static bool is_command(char *str) {
//    struct stat st;
//
//    if (stat(str, &st) != -1) { // finded
//        if ((st.st_mode & S_IXUSR) == S_IXUSR) {
////            free(str);
//            return true;
//        }
//    }
////    free(str);
//    return false;
//}
//
//static char *join_to_path(char *dst, char *str) {
//    int dst_len = 0;
//    char *s = NULL;
//
//    if(str && dst) {
//        dst_len = strlen(dst);
//        s = mx_strnew(dst_len + strlen(str));
//
//        for (int i = 0; i < dst_len - 1; i++)
//            s[i] = dst[i];
//        for (int j = 0; j < strlen(str) - 1; dst_len++, j++)
//            s[dst_len] = str[j];
//        free(dst);
//        return s;
//    }
//    if (str == 0 && dst == 0)
//        return NULL;
//    if (dst != 0)
//        return mx_strdup(str);
//    return mx_strdup(str);
//}
//
//static char *finded_command(char *argv[], char **split_path, int flag_a, int cur) {
//    char *str = NULL;
//        for (int j = 0; split_path[j] != NULL; j++) {
//            str = NULL;
////            printf("str_first = %s\n", str);
////            printf("sp_p = %s\n", split_path[j]);
//            str = mx_strjoin(str, split_path[j]);
//            str = mx_strjoin(str, "/");
//            str = mx_strjoin(str, argv[cur]);
////            printf("str_second= %s\n", str);
//            if (is_command(str))
//                return str;
//        }
////    }
//    return NULL;
//}
//
//static int search_commands(char *argv[], int i, int flag_a) {
//    char **split_path = mx_strsplit(getenv("PATH"), ':');
//    int cur = i;
//    bool check_one = 0;
//    char *command = NULL;
//    if (argv[cur] == NULL)
//        return -1;
//    else {
//        for(;argv[cur] != NULL; cur++) {
//            check_one = 0;
//            if (mx_is_buildin(argv[cur])) {
//                printf("%s: shell built-in command\n", argv[cur]);
//                check_one = 1;
//            }
//            if (flag_a || !check_one) {
//                if (finded_command(argv, split_path, flag_a, cur) == NULL) ///вывод под zsh
//                    fprintf(stderr, "%s not found\n", argv[cur]);
//                else {
//                    mx_printstr(finded_command(argv, split_path, flag_a, cur));
//                    mx_printchar('\n');
//                }
//            }
//        }
//    }
//    mx_del_strarr(&split_path);
//    return 0;
//}
//
//
//static void get_flags(char *argv[]) {
//    int flag_a = 0;
//    int i = 1;
//
//    for (; argv[i] != NULL; i++) {
//        if(argv[i][0] =='-') {
//            for (int j = 1; j < strlen(argv[i]); j++) {
//                if(argv[i][j] == 'a' || argv[i][j] == 's')
//                    flag_a = argv[i][j] == 'a' ? 1 : 0;
//                else {
//                    fprintf(stderr, "which: bad option: -%c", argv[i][j]);
//                    return;
//                }
//            }
//        }
//        else
//            break;
//    }
//    int g = search_commands(argv, i, flag_a);
////    printf("g = %d\n", g);
//
//}
//
//
//
//int mx_which(char *argv[]) {
//    if (argv[1]) {
//        get_flags(argv);
//        return 0;
//    }
//    else
//        return -1;
//}