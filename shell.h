#ifndef _SHELL_
#define _SHELL_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;


/**
 * struct data - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	int counter;
	char **environ;
	char *pid;
	char **av;
	char *input;
	char **args;
	int status;
} data_shell;

/**
 * struct sep_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_var_list
{
	char *val;
	int len_var;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *datash);
} builtin_t;

/* function of CD.c */
void _cddot(data_shell *data);
void _cdto(data_shell *data);
void _cdprevious(data_shell *data);
void cd_tohome(data_shell *data);
/* functions of CD_shell.c */
int _cdshell(data_shell *data);

/* functions of CMD_exec.c */
int _iscdir(char *path, int *i);
char *which(char *cmd, char **environ);
int _isexecutable(data_shell *data);
int _check_error_cmd(char *dir, data_shell *data);
int _cmdexec(data_shell *data);

/* functions of Exec_line.c */
int _execline(data_shell  *data);
int _exit_shell(data_shell *data);
int (*get_builtin(char *cmd))(data_shell *);

/* functions of Help.c */
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_general(void);
void help_exit(void);

/* functions of Help1.c */
void help(void);
void help_alias(void);
void help_cd(void);

/* functions of List1.c */
sep_list *Add_sep_node_end(sep_list **h, char sep);
void free_sep_list(sep_list **h);
line_list *Add_line_node_end(line_list **h, char *line);
void Free_line_list(line_list **h);

/* functions of Lists2.c */
r_var *Add_rvar_node(r_var **h, int lvar, char *val, int lval);
void free_rvar_list(r_var **h);

/* functions of Split.c */
char *_swapchar(char *input, int bool);
void _addnodes(sep_list **head_s, line_list **head_l, char *input);
void _gonext(sep_list **list_s, line_list **list_l, data_shell *data);
int _splitcommands(data_shell *data, char *input);
char **_splitline(char *input);

/* functions of Stdlib.c */
int _getlen(int n);
char *_itoa(int n);
int _atoi(char *s);

/* functions of check-syntax_error.c */
int _repeatedchar(char *input, int i);
int _errorsep_op(char *input, int i, char last);
int _firstchar(char *input, int *i);
void _printsyntax_error(data_shell *data, char *input, int i, int bool);
int _checksyntax_error(data_shell *data, char *input);

/* functions of environ1.c */
int _cmpenv_name(const char *nenv, const char *name);
char *_getenv(const char *name, char **environ);
int env(data_shell *data);

/* functions of environ2.c */
char *_copyinfo(char *name, char *value);
void _setenv(char *name, char *value, data_shell *data);
int set_env(data_shell *data);
int unset_env(data_shell *data);

/* functions of error1.c */
char *strcat_cd(data_shell *data, char *msg, char *err, char *verstr_);
char *err_get_cd(data_shell *data);
char *err_not_found(data_shell *data);
char *err_exit_shell(data_shell *data);

/* functions of error2.c */
char *err_env(data_shell *data);
char *err_path_126(data_shell *data);

/* functions of get_Error.c */
int get_error(data_shell *data, int eval);
int get_help(data_shell *data);

/* functions of get_Line.c */
void _bringline(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void _getsigint(int sig);

/* functions of main.c */
void _freedata(data_shell *data);
void set_data(data_shell *data, char **av);
int main(int ac, char **av);
char *_readline(int *i_eof);

/* functions of mem.c */
void mem_cpy(void *newptr, const void *ptr, unsigned int size);
void *re_alloc(void *ptr, unsigned int new_size, unsigned int old_size);
char **realloc_dp(char **ptr, unsigned int new_size, unsigned int old_size);

/* functions of shell_loop.c */
char *_withoutcomment(char *in);
void _shell_loop(data_shell *data);
ssize_t _puts(char *str);

/* functions of str.c */
char *str_cat(char *dest, const char *src);
char *str_cpy(char *src, char *dest);
int str_cmp(char *s1, char *s2);
char *str_chr(char *s, char c);
int str_spn(char *s, char *accept);

/* functions of str1.c */
char *str_dup(const char *s);
int str_len(const char *s);
int _cmp_chars(char str[], const char *delim);
char *str_tok(char str[], const char *delim);
int is_digit(const char *s);

/* functions of str2.c */
void _revstring(char *s);

/* functions of var.c */
void _check_env(r_var **h, char *in, data_shell *data);
int _checkvars(r_var **h, char *in, char *st, data_shell *data);
char *_replacedinput(r_var **h, char *input, char *new_input, int nlen);
char *_repvar(char *input, data_shell *data);

#endif
