#include "ush.h"

//char prompt[] = "<u$h> "; // command line prompt
void eval(t_app *app, t_cmd *cmd);
enum builtin_t parseBuiltin(t_cmd *cmd);
void error(char *msg);
int parse(t_cmd *cmd);
void runSystemCommand(t_cmd *cmd, int bg);
void runBuiltinCommand(t_cmd *cmd, int bg, t_app *app);


enum builtin_t parseBuiltin(t_cmd *cmd) {
    // quit command??????????????
    if (!strcmp(cmd->argv[0], "cd")) {
        return b_cd;
    }
    else if (!strcmp(cmd->argv[0], "which")) {
        return b_which;
    }
    else if (!strcmp(cmd->argv[0], "echo")) {
        return b_echo;
    }
    else if (!strcmp(cmd->argv[0], "pwd")) {
        return b_pwd;
    }
    else if (!strcmp(cmd->argv[0], "env")) {
        return b_env;
    }
    else if (!strcmp(cmd->argv[0], "export")) {
        return b_export;
    }
    else if (!strcmp(cmd->argv[0], "unset")) {
        return b_unset;
    }
    else if (!strcmp(cmd->argv[0], "exit")) {
        return b_exit;
    }
    else if (!strcmp(cmd->argv[0], "jobs")) { // Отобразить список текущих фоновых задач
        return b_jobs;                               //cостояние процесса Running, Stopped, Done, Exit.
    }
    else if (!strcmp(cmd->argv[0], "bg")) { // восстанавливает jobs в фоновом режиме
        return b_bg;
    }
    else if (!strcmp(cmd->argv[0], "fg")) { // выводит процесс из фонового режима
        return b_fg;                              // (в качестве arg можно передать №задачи)
        // (если без arg, то выведет последнюю, отправленную в фон задачу)
    }
    else {
        return b_none;
    }
}

void error(char *msg) {
    fprintf(stderr, "Error: %s", msg);
    exit(0);
}

int parse(t_cmd *cmd) {
//    static char array[MAXLINE];                 // local copy of command line
//    const char delims[10] = " \t\r\n\v\f\r";    // argument delimiters
//    char *line = array;                         // ptr that traverses command line
//    char *token;                                // ptr to the end of the current arg
//    char *endline;                              // ptr to the end of the cmdline string
    int is_bg;                                  // background job?

//    (void) strncpy(line, cmdline, MAXLINE);
//    endline = line + strlen(line);
//    // build argv list
//    cmd->argc = 0;
//    while (line < endline) {
//        line += strspn (line, delims);              // skip delimiters
//        if (line >= endline) break;
//        token = line + strcspn (line, delims);      // Find token delimiter
//        *token = '\0';                              // terminate the token
//        cmd->argv[cmd->argc++] = line;                // Record token as the token argument
//        if (cmd->argc >= MAXARGS-1) break;          // Check if argv is full
//        line = token + 1;
//    }
//    // argument list must end with a NULL pointer
//    cmd->argv[cmd->argc] = NULL;
    if (cmd->argc == 0)  // ignore blank line
        return 1;
    cmd->builtin = parseBuiltin(cmd);
    // should job run in background?
    if ((is_bg = (*cmd->argv[cmd->argc-1] == '&')) != 0)
        cmd->argv[--cmd->argc] = NULL;
//    for (int i = 0; cmd->argv; i++) {
//        printf("%s", cmd->argv[i]);
//    }
    return is_bg;
}

void runSystemCommand(t_cmd *cmd, int bg) {
    pid_t childPid;
    // FORK !!!
    if ((childPid = fork()) < 0)
        error("fork() error");
    else if (childPid == 0) { // I'm the child and could run a command
        // EXECVP !!!!
        if (execvp(cmd->argv[0], cmd->argv) < 0) {
            printf("%s: Command not found\n", cmd->argv[0]);
            exit(0);
        }
    }
    else { // I'm the parent. Shell continues here.
        if (bg)
            printf("Child in background [%d]\n",childPid);
        else
            wait(&childPid);
    }
}


void runBuiltinCommand(t_cmd *cmd, int bg, t_app *app) {
    switch (cmd->builtin) {

        case b_cd:
            mx_cd_builtin(cmd->argv, app);
            break;
        case b_which:
            mx_which(cmd->argv);
            break;
        case b_echo:
            mx_echo_builtin(cmd->argv);
            break;
        case b_pwd:
            mx_pwd_builtin(cmd->argv, app);
            break;
        case b_env:
            mx_env_builtin(cmd->argv) ;
            break;
        case b_export:
            mx_builtin_export(app, cmd);
            break;
        case b_unset:
            mx_builtin_unset(cmd, app);
            break;
        case b_exit:
            printf("TODO: exit\n");
            break;
        default:
            error("Unknown builtin command");
    }
}



void eval(t_app *app, t_cmd *cmd) {
    int bg;

    // parse line into command struct
    bg = parse(cmd);
    if (bg == -1) return;
    // empty line - ignore
    if (cmd->argv[0] == NULL) return;

    if (cmd->builtin == b_none) {
        runSystemCommand(cmd, bg);
    }
    else {

        runBuiltinCommand(cmd, bg, app);
    }
}

int mx_streams(t_st *st, char **tokens, t_app *app) {
    t_cmd *cmd = malloc(sizeof(t_cmd));

    cmd->argc = 0;
    cmd->argv = tokens;
    for (int i = 0; tokens[i] != NULL; i++)
        cmd->argc++;


    eval(app, cmd);


    return st->status;
}
