/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:49:49 by fquist            #+#    #+#             */
/*   Updated: 2022/03/22 16:32:58 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/* STANDARD INCLUDES														  */
/* ************************************************************************** */
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libs/libft/include/libft.h"
# include "stringbuilder.h"
# include <stdbool.h>
# include <limits.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <signal.h>
# include <termios.h>

/* ************************************************************************** */
/* 	DEFINES																	  */
/* ************************************************************************** */
extern int	g_exit_status;

# define BLACK	"\033[0;30m"
# define RED	"\033[0;31m"
# define GREEN	"\033[1;32m"
# define LGREEN	"\033[0;32m"
# define YELLOW	"\033[0;33m"
# define BLUE	"\033[0;34m"
# define PURPLE	"\033[0;35m"
# define CYAN	"\033[0;36m"
# define WHITE	"\033[0;37m"
# define RESET	"\e[0m"

# define SIGINT 2
# define SIGHUP 1
# define SIGQUIT 3
# define SIGABRT 6
# define GENERAL_STATE -5
# define SQUOTED_STATE -2
# define DQUOTED_STATE -3
# define END -4
# define HERE_DOC -7
# define PIPEIN -3
# define PIPEOUT -2
# define ERROR -1
# define VAR_NAME 0
# define VAR_CONTENT 1
# define VAR_VALUE 0
# define NEW_NODE 1
# define TRUE 1
# define FALSE 0
# define EXIT 1
# define NO_EXIT 0
# define NORIGHTS 13
# define NOFILE 2
# define LOG 0
# define HEAD 0
# define NEW 1
# define WRITE 1
# define READ 0
# define SUCCESS 0
# define FAIL 1
/* ************************************************************************** */
/* 	DATA STRUCTURES															  */
/* ************************************************************************** */

typedef enum e_type
{
	COMMAND = 0,
	OPTION = -2,
	ARG,
	SQUOTE = '\'',
	DQUOTE = '\"',
	PIPE = '|',
	OR = 496,
	AMPERSAND = '&',
	AND = 152,
	LESS = '<',
	LESSLESS = 240,
	GREAT = '>',
	GREATGREAT = 248,
	LPAREN = '(',
	RPAREN = ')',
}			t_type;

typedef struct s_token
{
	char			*name;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef struct s_node
{
	t_type			type;
	t_token			*tokens;
	struct s_node	*next;
	struct s_node	*prev;
}				t_node;

typedef struct s_redir
{
	t_type			type;
	char			*file;
	struct s_redir	*next;
	struct s_redir	*prev;
}	t_redir;

typedef struct s_table
{
	char			**cmd_arr;
	char			*exe;
	char			*args;
	t_redir			*redir;
	t_type			log_op;
	int				opt;
	struct s_table	*next;
	struct s_table	*prev;
}			t_table;

typedef struct s_env
{
	char			*var;
	int				val;
	struct s_env	*next;
}			t_env;

typedef struct s_exec
{
	int	fd[2];
	int	here_fd[2];
	int	tmp_fd;
	int	stin;
	int	stout;
	int	file_fd;
	int	cmd_count;
	int	no_rights;
	int	pid;
	int	i;
}			t_exec;

/* ************************************************************************** */
/* 	STRUCT UTILS															  */
/* ************************************************************************** */
t_node	*new_node(void);
t_node	*get_last_node(t_node *head);
t_node	*append_node(t_node **head, t_node *new);

t_token	*new_token(char *input, t_type type);
t_token	*get_last_token(t_token *head);
t_token	*append_token(t_token **head, t_token *new);

t_table	*new_table(void);
t_table	*get_last_table(t_table *head);
t_table	*append_table(t_table **head, t_table *new);

t_env	*new_env(char *str);
t_env	*get_last_env(t_env *head);
t_env	*append_env(t_env **head, t_env *new);
t_env	**get_env(char **environ);

void	print_nodes(t_node *node);
void	print_tokens(t_token *token);
void	print_cmd_table(t_table *table);

char	*str_join(char const *s1, char const *s2, const char *s3);
char	*ft_strjoin_ws(char const *s1, char const *s2);
char	*lstlast(t_token *lst);
int		lstsize(t_token *lst);

t_redir	*new_redir(t_type type, char *file);
t_redir	*get_last_redir(t_redir *head);
t_redir	*append_redir(t_redir **head, t_redir *new);
t_redir	*get_last_in_redir(t_redir *head);
t_redir	*get_last_out_redir(t_redir *head);

void	free_node(t_node **node);
void	free_token(t_token **token);
void	free_table(t_table **table);
void	free_redir(t_redir **redir);
void	free_cmd_arr(char **cmd_arr);

/* ************************************************************************** */
/* 	SHELL																	  */
/* ************************************************************************** */
char	*get_prompt(void);
void	print_header(void);

/* ************************************************************************** */
/* 	LEXER																	  */
/* ************************************************************************** */
int		lexer(t_node **head, char *input);
int		define_type(char *input);
int		create_tokens(t_node **node, char **input);
int		create_redir_token(t_node **node, char **input);

char	*get_word(char **input);
char	*get_word_ws(char **input); // TODO: delete this declaration!!

bool	check_whitespace(char c);
bool	check_metachar(char c);
bool	check_quotes(char c);
bool	check_redir(t_type type);
bool	check_log_op(t_type c);

/* ************************************************************************** */
/* 	PARSER																	  */
/* ************************************************************************** */
void	create_cmd_table(t_node **node, t_table **table);
int		parser(t_node **node, t_table **table);
int		echo_parser(t_token *help, t_table **new);
int		redir_parser(t_token *curr_t, t_table **new);
int		valid_name(t_token **token);
void	trim_quotes(t_token **token);
void	add_args_to_arr(t_token *token, t_table **new);

/* ************************************************************************** */
/* 	BUILTIN FUNCS															  */
/* ************************************************************************** */
int		ft_pwd(void);
void	ft_echo(t_table *table);
void	ft_cd(t_table *table);
void	ft_exit(t_table *table);
void	ft_env(void);
void	ft_export(char *args);
void	ft_unset(t_table *table);

int		set_cmd_path(t_table **table, t_env **env);
char	**get_env_path(t_env **env);
int		sb_append_strn(t_stringbuilder *sb, char *str, int len);
void	append_slash(char **cmd_paths);

bool	check_builtin(t_table *table);
char	**get_env_arr(void);
char	*get_env_var(char *str);
int		get_env_size(t_env *env);

int		expander(t_node **node);
void	expand(char **str);

int		open_file(char *file, int mod, int rights);
int		file_error(char *name_b, char *msg, char *name_a);
int		built_in_exec(t_table *table);
int		exec_loop(t_table *table);
int		create_prcs(t_table *table, t_exec *fds);
void	route_stdin(t_table *table, t_exec *fds);
void	route_stdout(t_table *table, t_exec *fds);
int		heredoc(char *delimiter, t_exec *fds, int type);
int		exec(t_table *table);
int		command_parser(t_token *token, t_table **new);
int		define_echo_args(t_token *token, t_table **new);
t_exec	*new_exec(void);
int		operation_logic(t_table *table, t_exec *fds);

void	set_attr(void);
void	unset_attr(void);
void	sigint_handler(int sig);

#endif
