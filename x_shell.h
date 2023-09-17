#ifndef _X_SHELL_H_
#define _X_SHELL_H_

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

/* Below prototype points to an array of ptr to strs named the "environment" */

extern char **enviro;

/**
 * struct data - The structure which contains all relevant data on the runtime
 * @argv: Argument vector
 * @input_x: The ommand line written by the user.
 * @args: The tokens of the command line.
 * @status: The last status of the x_shell.
 * @counter_x: The lines counter.
 * @_enviro: The environment variable.
 * @pid: The process ID of the x_shell.
 */

typedef struct data
{
	char **argv;
	char *input_x;
	char **args;
	int status;
	int counter_x;
	char **_enviro;
	char *pid;
} data_shell;

/**
 * struct sep_list_s - Single linked list.
 * @separator_x: ; | &
 * @next: Next node of x-shell.
 * Description_x: Single linked list to the store separators
 */

typedef struct sep_list_s
{
	char separator_x;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - Single linked list.
 * @line_x: Command line.
 * @next: Next node of x-shell.
 * Description_x: Single linked list to the store command lines.
 */

typedef struct line_list_s
{
	char *line_x;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - Single linked list.
 * @len_xvar: Length of the variable.
 * @val_x: Value of the variable.
 * @len_xval: Length of the value.
 * @next: Next node.
 * Description_x: Single linked list to the store variables.
 */

typedef struct r_var_list
{
	int len_xvar;
	char *val_x;
	int len_xval;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Builtin structure for the command args.
 * @name_x: The name of the command builtin i.e env, cd, exit etc.
 * @func_x: The data type for pointer function.
 */

typedef struct builtin_s
{
	char *name_x;
	int (*func_x)(data_shell *datash);
} builtin_t;

/* x_lists.c */
line_list *add_line_node_end(line_list **head, char *line_x);
void free_line_list(line_list **head);
sep_list *add_sep_node_end(sep_list **head, char sep_x);
void free_sep_list(sep_list **head);

/* x_lists2.c */
void free_rvar_list(r_var **head);
r_var *add_rvar_node(r_var **head, int len_var, char *xval, int l_xval);

/* x_str functions prototype */
char *x_strcat(char *dest_x, const char *src_x);
char *x_strcpy(char *dest_x, char *src_x);
int x_strcmp(char *s1_x, char *s2_x);
char *x_strchr(char *s_x, char c_x);
int x_strspn(char *s_x, char *accept_x);

/* x_mem.c */
void *x_realloc(void *ptr_x, unsigned int x_old_sz, unsigned int x_new_sz);
char **x_reallocdp(char **ptr_x, unsigned int x_old_sz, unsigned int x_new_sz);
void x_memcpy(void *x_newptr, const void *ptr_x, unsigned int x_size);

/* x_str2.c */
int x_cmp_chars(char str[], const char *delim_x);
char *x_strtok(char str[], const char *delim_x);
int x_isdigit(const char *str_x);
char *x_strdup(const char *str_x);
int x_strlen(const char *str_x);

/* x_str3.c */
void rev_string(char *str_x);

/* x_shell_loop.c */
char *without_comment(char *in_x);
void x_shell_loop(data_shell *datash);

/* x-shell-check_syntax_error.c */
int repeated_char(char *input_x, int i);
int error_sep_op(char *input_x, int i, char last_x);
int first_char(char *input_x, int *i);
void print_syntax_error(data_shell *datash, char *input_x, int i, int bool_x);
int check_syntax_error(data_shell *datash, char *input_x);

/* read_x_line.c */
char *read_line(int *x_eof);

/* split_x.c */
char *swap_char(char *input_x, int bool_x);
void add_nodes(sep_list **head_x, line_list **head_l, char *input_x);
void go_next(sep_list **list_x, line_list **list_l, data_shell *datash);
int split_commands(data_shell *datash, char *input_x);
char **split_line(char *input_x);

/* rep_xvar.c */
void check_env(r_var **head, char *in, data_shell *data);
int check_vars(r_var **head, char *in, char *str, data_shell *data);
char *replaced_input(r_var **head, char *input_x, char *xnew_input, int xlen);
char *rep_var(char *input_x, data_shell *datash);

/* x_get_line.c */
void bring_line(char **lineptr_x, size_t *i, char *buffer, size_t j);
ssize_t get_line(char **lineptr_x, size_t *i, FILE *stream);

/* exec_x_line */
int exec_line(data_shell *datash);

/* cmd_exec_x.c */
int is_cdir(char *x_path, int *i);
char *_which(char *cmd_x, char **_enviro);
int is_executable(data_shell *datash);
int check_error_cmd(char *x_dir, data_shell *datash);
int cmd_exec(data_shell *datash);

/* x_env1.c */
char *_getenv(const char *name, char **_enviro);
int _env(data_shell *datash);

/* x_env2.c */
char *copy_info(char *name, char *x_value);
void set_env(char *name, char *x_value, data_shell *datash);
int _setenv(data_shell *datash);
int _unsetenv(data_shell *datash);

/* cd_x.c */
void cd_dot(data_shell *datash);
void cd_to(data_shell *datash);
void cd_previous(data_shell *datash);
void cd_to_home(data_shell *datash);

/* cd_x_shell.c */
int cd_x_shell(data_shell *datash);

/* get_x_builtin */
int (*get_x_builtin(char *cmd_x))(data_shell *datash);

/* x_exit.c */
int exit_x_shell(data_shell *datash);

/* x_stdlib.c */
int get_x_len(int i);
char *x_itoa(int i);
int x_atoi(char *x);

/* x_error1.c */
char *strcat_cd(data_shell *, char *, char *, char *);
char *error_get_cd(data_shell *datash);
char *error_not_found(data_shell *datash);
char *error_exit_x_shell(data_shell *datash);

/* x_error2.c */
char *error_get_alias(char **args);
char *error_env(data_shell *datash);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path_126(data_shell *datash);

/* get_x_error.c */
int get_x_error(data_shell *datash, int err_val);

/* get_x_sigint.c */
void get_x_sigint(int x_sig);

/* x_help1.c */
void x_help_env(void);
void x_help_setenv(void);
void x_help_unsetenv(void);
void x_help_general(void);
void x_help_exit(void);

/* x_help2.c */
void x_help(void);
void x_help_alias(void);
void x_help_cd(void);

/* get_x_help.c */
int get_x_help(data_shell *datash);

#endif /* x_shell.h header file */

