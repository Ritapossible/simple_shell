#ifndef SHELL_H
#define SHELL_H

#include <stdio.h> /* for printf*/
#include <unistd.h> /* for fork, execve*/
#include <stdlib.h>
#include <string.h> /* for strtok*/
#include <stddef.h>
#include <errno.h> /* for errno and perror */
#include <sys/types.h> /* for type pid */
#include <sys/wait.h> /* for wait */
#include <sys/stat.h> /* for use of stat function */
#include <signal.h> /* for signal management */
#include <fcntl.h> /* for open files*/

#include "macros.h" /* for msg help and prompt */

/*****STRUCTURES****/

/**
 * struct info- struct for the program's data
 * @program_name: the name of the executable
 * @input_line: pointer to the input read for _getline
 * @command_name: pointer to the first command typed by the user
 * @exec_counter: number of excecuted comands
 * @file_des: file descriptor to the input of commands
 * @tokens: pointer to array of tokenized input
 * @env: copy of the environ
 * @alias_list: array of pointers with aliases.
 */
typedef struct info
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_des;
	char **tokens;
	char **env;
	char **alias_list;
} my_program_info;

/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(my_program_info *data);
} builtins;

/*** MAIN FUNCTIONS ***/

/** my_getline.c */

/* Read one line of the standard input*/
int _getline(my_program_info *data);

/* split the each line for the logical operators if it exist */
int check_logic_ops(char *array_commands[], int i, char array_operators[]);

/* Separate the string in tokens using a designed delimiter */
void tokenize(my_program_info *data);

/*========  shell.c  ========*/

/* Inicialize the struct with the info of the program */
void inicialize_data(my_program_info *data, int arc, char *argv[], char **env);

/* Makes the infinite loop that shows the prompt*/
void sisifo(char *prompt, my_program_info *data);

/* Print the prompt in a new line */
void handle_ctrl_c(int opr UNUSED);

/*** free_info.c ***/

/* Frees the memory for directories */
void free_array_of_pointers(char **directories);

/* Free the fields needed each loop */
void free_recurrent_data(my_program_info *data);

/* Free all field of the data */
void free_all_data(my_program_info *data);

/*** alias.c ***/

int print_alias(my_program_info *data, char *alias);

/* get the alias name */
char *get_alias(my_program_info *data, char *alias);

/* set the alias name */
int set_alias(char *alias_string, my_program_info *data);

/** Helper functions in printers.c ***/

/* Prints a string in the standard output */
int _print(char *string);

/* Prints a string in the standard error */
int _printe(char *string);

/* Prints a string in the standard error */
int _print_error(int errorcode, my_program_info *data);

/***=== Helper functions in strings.c ===***/

/* Counts the number of characters of a string */
int str_length(char *string);

/* Duplicates an string */
char *str_duplicate(char *string);

/* Compares two strings */
int str_compare(char *string1, char *string2, int number);

/* Concatenates two strings */
char *str_concat(char *string1, char *string2);

/* Reverse a string */
void str_reverse(char *string);


/* Cast from int to string */
void long_to_string(long number, char *string, int base);

/* convert an string in to a number */
int _atoi(char *s);

/* count the coincidences of character in string */
int count_characters(char *string, char *character);

/*======== expansions.c ========*/

/* expand variables */
void expand_variables(my_program_info *data);

/* expand aliases */
void expand_alias(my_program_info *data);

/* append the string to the end of the buffer*/
int buffer_add(char *buffer, char *str_to_add);

int execute(my_program_info *data);

char *_strtok(char *line, char *delim);


/*=== env_manage.c ===*/

/* Gets the value of an environment variable */
char *env_get_key(char *name, my_program_info *data);

/* Overwrite the value of the environment variable */
int env_set_key(char *key, char *value, my_program_info *data);

/* Remove a key from the environment */
int env_remove_key(char *key, my_program_info *data);

/* Creates an array of the path directories */
char **tokenize_path(my_program_info *data);

/* Search for program in path */
int find_program(my_program_info *data);

/* If match a builtin, executes it */
int builtins_list(my_program_info *data);

#endif /* SHELL_H */
