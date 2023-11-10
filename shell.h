#ifndef SHELL
#define SHELL

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>

/**
 * struct list - linked list for environmental variables
 * @var: holds environmental variable string
 * @next: points to next node
 */
typedef struct list
{
	char *var;
	struct list *next;

} list_t;

/* functions of _getenv */
char *_str_dup(char *string, int cs);
char *_getenv(char *str, list_t *env);

/* functions of _getline.c */
size_t _getline(char **string);

/* functions of _strdup.c */
char *_strdup(char *string);

/* functions of cd.c */
char *cd_strcat(char *dest, char *src);
int com_setenv(list_t **env, char *name, char *dir);
void _cdonly(list_t *env, char *cur);
int cd_execute(list_t *env, char *cur, char *dir, char *str, int num);
int _cd(char **str, list_t *env, int num);

/* functions of execute.c */
void c_exit(char **string, list_t *env);
int _execve(char **st, list_t *env, int num);

/* functions of exit.c */
int _atoi(char *s);
int __exit(char **string, list_t *env, int num, char **command);

/* functions of free_ptr.c */
void free_double_p(char **string);

/* functions of interactive.c */
char *_ignore(char *str);
void _interactive(list_t *env);

/* functions of linked_list.c */
list_t *envlinked_list(char **env);
int _env(char **string, list_t *env);

/* functions of list.c */
size_t print_list(list_t *head);
list_t *add_end_node(list_t **h, char *str);
int delete_nodeint_at_index(list_t **h, int index);
void free_linked_list(list_t *list);

/* functions of printer.c */
void n_found(char *string, int c_n, list_t *env);
void not_cd_to(char *string, int c_n, list_t *env);
void wrong_number(char *string, int c_n, list_t *env);

/* functions of read_line.c */
void ctrl_c(int n);
int built_in(char **token, list_t *env, int num, char **cmd);
char *ign_space(char *string);
int prompt(char **environ);

/* functions of realloc.c */
void *_realloc(void *pointer, unsigned int old_size, unsigned int new_size);

/* functions of set_env.c */
int _findenv(list_t *env, char *string);
int _unsetenv(list_t **env, char **string);
int _setenv(list_t **env, char **string);

/* functions of simple_shell.c */
int main(int argc, char **argv, char **env);

/* functions of str.c */
char *_strcat(char *dest, char *src);

/* functions of str1.c */
int _strlen(char *str, int pos, char delm);
int t_size(char *string, char delm);
char *ign_delm(char *string, char delm);
char **_str_tok(char *str, char *delm);

/* functions of str2.c */
int _strcmp(char *s1, char *s2);

/* functions of str_tok.c */
int _size(char *str, char delm);
char **_tok(char *string, char *delim);

/* functions of strings.c */
char *_strcpy(char *dest, char *src);

/* functions to_string.c */
int numlen(int n);
char *to_string(int number);

/* functions of which_cmd.c */
char *which_cmd(char *string, list_t *env);



#endif
