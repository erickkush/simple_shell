#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH '\0'

typedef struct list_s
{
	char *str;
	struct list_s *next;
}
list_t;

typedef struct
{
	int status;
	char **argv;
	int err_num;
	list_t *env;
	int argc;
	int readfd;
	list_t *history;
	int histcount;
	int cmd_buf_type;
}
info_t;

int interactive(info_t *info);
int is_delim(char c, const char *delim);
int _isalpha(int c);
int _atoi(const char *s);

int _myexit(info_t *info);
int _mycd(info_t *info);
int _myhelp(info_t *info);

char *_getenv(info_t *info, const char *name);
int _mysetenv(info_t *info);
int _myunsetenv(info_t *info);
int populate_env_list(info_t *info);

int _myenv(info_t *info);

int set_environment(list_t **env, const char *name, const char *value);
int unset_environment(list_t **env, const char *name);
list_t *find_environment(list_t *env, const char *name);
void print_environment(list_t *env);
int add_environment(list_t **env, const char *str);

void print_list_str(list_t *head);
list_t *add_node_end(list_t **head, const char *str, int type);

char *_strncpy(char *dest, const char *src, size_t n);
char *_strncat(char *dest, thecodeconst char *src, size_t n);
char *_strchr(const char *s, int c);

ssize_t input_buf(info_t *info, char **buf, size_t *len);
ssize_t get_input(info_t *info);
ssize_t read_buf(info_t *info, char *buf, size_t *i);
int custom_getline(info_t *info, char **ptr, size_t *length);
void sigintHandler(int sig_num);

void clear_info(info_t *info);
void set_info(info_t *info, char **av);
void free_info(info_t *info, int all);

char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

size_t list_len(const list_t *h);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *h);
list_t *find_node_starts_with(list_t *head, char *prefix, char c);
ssize_t get_node_index(list_t *head, list_t *node);

int safe_free(void **ptr);

int is_cmd(info_t *info, char *path);
char *extract_substring(const char *str, int start, int end);
char *find_path(info_t *info, char *pathstr, char *cmd);

size_t custom_strlen(const char *str);
int custom_strcmp(const char *str1, const char *str2);
const char *custom_starts_with(const char *str, const char *prefix);
char *custom_strcat(char *dest, const char *src);

char **strtow(char *str, char *d);
char **strtow2(char *str, char d);

int is_chain_delimiter(info_t *info, char *buf, size_t *p);
void check_chain_continue(info_t *info,
		char *buf, size_t *p, size_t i, size_t len);
int replace_aliases(info_t *info);
int replace_variables(info_t *info);
int replace_string(char **old, char *new);

#endif
