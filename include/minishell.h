/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:49:49 by fquist            #+#    #+#             */
/*   Updated: 2022/03/08 17:58:33 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/* STANDARD INCLUDES														  */
/* ************************************************************************** */
# include <stdbool.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include "../libs/libft/include/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <signal.h>

/* ************************************************************************** */
/* 	DEFINES																	  */
/* ************************************************************************** */
# define BLACK	"\033[0;30m"
# define RED	"\033[0;31m"
# define GREEN	"\033[1;32m"
# define LGREEN	"\033[0;32m"
# define YELLOW	"\033[0;33m"
# define BLUE	"\033[0;34m"
# define PURPLE	"\033[0;35m"
# define CYAN	"\033[0;36m"
# define WHITE	"\033[0;37m"
# define RESET	"\033[0m"

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
	// int				state;
}				t_token;

typedef struct s_node
{
	t_type			type;
	t_token			*tokens;
	struct s_node	*next;
	struct s_node	*prev;
	// t_token			*here_doc;
	// char			*cmdpath;
	// int				in;
	// int				out;
}				t_node;

typedef struct s_table
{
	char			**cmd_arr;
	char			*exe;
	char			*args;
	t_type			log_op;
	t_list			*redir_in;
	t_list			*redir_out;
	t_list			*infiles;
	t_list			*outfiles;
	t_list			*delimiter;
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

void	free_list(t_node **lst, bool exit, bool exit_status);
void	free_table(t_table **lst, bool exit, bool exit_status);

char	*str_join(char const *s1, char const *s2, const char *s3);
char	*ft_strjoin_ws(char const *s1, char const *s2);
char	*lstlast(t_token *lst);
int		lstsize(t_token *lst);

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
char	*get_word_ws(char **input);
char	*get_word_args(char **input);
char	*get_word_redir(t_type type, char **input);
char	*get_word_quoted(char **input);
bool	check_whitespace(char c);
bool	check_metachar(char c);
bool	check_quotes(char c);
bool	check_redir(t_type type);
bool	check_log_op(int c);
void	free_node(t_node **node);
void	free_token(t_token **token);

/* ************************************************************************** */
/* 	PARSER																	  */
/* ************************************************************************** */
void	create_cmd_table(t_node **node, t_table **table);
int		parser(t_node **node, t_table **table);
int		echo_parser(t_token *help, t_table **new);
int		redir_parser(t_token *curr_t, t_table **new);

/* ************************************************************************** */
/* 	BUILTIN FUNCS															  */
/* ************************************************************************** */
int		ft_pwd(void);
void	ft_echo(t_table **table);
void	ft_cd(t_table **table, t_env **env);
void	ft_exit(t_table **table);
void	ft_env(t_env **env);
void	ft_export(t_env **env, t_table *table);
void	ft_unset(t_env **env, t_table *table);

int		set_cmd_path(t_table **table, t_env **env);
char	**get_env_path(t_env **env);
void	append_slash(char **cmd_paths);
int		builtin_exec(t_table **table, t_env **env);

void	executer(t_table **table, t_env **env);
int		*create_child_prcs(t_table **table, int childs, int pipes, t_env **env);

bool	check_builtin(t_table *table);
char	**get_env_arr(t_env **env);

#endif
