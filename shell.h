#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for numcnv() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environments;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next nd
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@argu: a string generated from getline containing arguements
 *@argvarb: an array of strings generated from argu
 *@pathfl: a string pathfl for the current command
 *@argcount: the argument count
 *@countli: the error count
 *@error_numb: the error code for exit()s
 *@licount_flg: if on count this line of input
 *@name_file: the program filename
 *@env: linked list local copy of environments
 *@environments: custom modified copy of environments from LL env
 *@history: the history nd
 *@alias: the alias nd
 *@chng_enviro: on if environments was changed
 *@allstatus: the return allstatus of the last exec'd command
 *@buffer_cmd: address of pointer to buffer_cmd, on if chaining
 *@buffer_typcmd: CMD_type ||, &&, ;
 *@inptfd: the fd from which to read line input
 *@counting_hist: the history line number count
 */
typedef struct passinfo
{
	char *argu;
	char **argvarb;
	char *pathfl;
	int argcount;
	unsigned int countli;
	int error_numb;
	int licount_flg;
	char *name_file;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environments;
	int chng_enviro;
	int allstatus;

	char **buffer_cmd; /* pointer to cmd ; chain buffer, for memory mangement */
	int buffer_typcmd; /* CMD_type ||, &&, ; */
	int inptfd;
	int counting_hist;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* ssh.c */
int mn_shl(info_t *, char **);
int builtin_findf(info_t *);
void find_com(info_t *);
void fork_com(info_t *);

/* paath.c */
int thecmd(info_t *, char *);
char *charac_dplct(char *, int, int);
char *path_fnd(info_t *, char *, char *);

/* loopingh.c */
int loopingh(char **);

/* strfun.c */
void puterror(char *);
int put_erchar(char);
int char_P(char c, int fd);
int put_stringf(char *str, int fd);

/* str_fun4.c */
int lenstring(char *);
int cmpstring(char *, char *);
char *string_strtw(const char *, const char *);
char *catstring(char *, char *);

/* str_fun3.c */
char *cpystring(char *, char *);
char *dplstring(const char *);
void prtstring(char *);
int prtcharc(char);

/* str_fun2.c */
char *cpy_nstring(char *, char *, int);
char *cat_nstring(char *, char *, int);
char *charc_stringf(char *, char);

/* str_fun1.c */
char **tknstring(char *, char *);
char **tknize_string(char *, char);

/* mefun1.c */
char *set_memory(char *, char, unsigned int);
void arr_free(char **);
void *mmry_reallc(void *, unsigned int, unsigned int);

/* mefun2.c */
int block_afree(void **);

/* morfun1.c */
int isinteractv(info_t *);
int delim(char, char *);
int aalpha(int);
int integerstr(char *);

/* morfun2.c */
int intr_error(char *);
void errorprtt(info_t *, char *);
int intr_prt(int, int);
char *numcnv(long int, int, int);
void cmmrmv(char *);

/* built1.c */
int thexit(info_t *);
int thex(info_t *);
int thehelp(info_t *);

/* built2.c */
int thehistory(info_t *);
int thealias(info_t *);
int unset_alias(info_t *, char *);
int set_alias(info_t *, char *);
int _printal(list_t *);


/* line.c */
ssize_t gtusr_input(info_t *);
int linegt(info_t *, char **, size_t *);
void ctrlc_handle(int);
ssize_t buf_in(info_t *, char **, size_t *);
ssize_t read_buf(info_t *, char *, size_t *);

/* inform.c */
void infoclr(info_t *);
void infoset(info_t *, char **);
void infofr(info_t *, int);

/* environ.c */
char *enviro_get(info_t *, const char *);
int thenviro(info_t *);
int thesetevn(info_t *);
int theunset_env(info_t *);
int env_populate(info_t *);

/* environ2.c */
char **get_thenviron(info_t *);
int unset_enviro(info_t *, char *);
int set_enviro(info_t *, char *, char *);

/* iofun.c */
char *his_file(info_t *info);
int hist_write(info_t *info);
int hist_read(info_t *info);
int hist_list(info_t *info, char *buf, int linecount);
int hist_renum(info_t *info);

/* strlist.c */
list_t *node_adl(list_t **, const char *, int);
list_t *node_adend(list_t **, const char *, int);
size_t string_liprt(const list_t *);
int index_dltnd(list_t **, unsigned int);
void frlist(list_t **);

/* strlist2.c */
size_t gtlist_length(const list_t *);
char **string_lst(list_t *);
size_t listprt(const list_t *);
list_t *strt_nde(list_t *, char *, char);
ssize_t index_nde(list_t *, list_t *);

/* chaing.c */
int chaing(info_t *, char *, size_t *);
void chain_chk(info_t *, char *, size_t *, size_t, size_t);
int alias_rpl(info_t *);
int variable_rpl(info_t *);
int string_rpl(char **, char *);

#endif
