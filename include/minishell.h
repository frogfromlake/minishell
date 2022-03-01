/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:49:49 by fquist            #+#    #+#             */
/*   Updated: 2022/03/01 02:27:52 by fquist           ###   ########.fr       */
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
# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

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
	bool			is_option;
	int				state;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef struct s_node
{
	t_type			type;
	t_token			*tokens;
	t_token			*here_doc;
	char			*cmdpath;
	char			**cmd_arr;
	int				in;
	int				out;
	struct s_node	*next;
	struct s_node	*prev;
}				t_node;


typedef struct s_table
{
	char			*exe;
	char			*args;
	char			*redir_in;
	char			*redir_out;
	int				opt;
	struct s_table	*next;
	struct s_table	*prev;
}			t_table;


/* ************************************************************************** */
/* 	STRUCT UTILS															  */
/* ************************************************************************** */
t_table	*new_table(void);
t_table	*get_last_table(t_table *head);
t_table	*append_table(t_table **head, t_table *new);
t_node	*new_node(void);
t_node	*get_last_node(t_node *head);
t_node	*append_node(t_node **head, t_node *new);
t_token	*new_token(char *input);
t_token	*get_last_token(t_token *head);
t_token	*append_token(t_token **head, t_token *new);

void	print_nodes(t_node *node);
void	print_tokens(t_token *token);
void	print_cmd_table(t_table *table);
void	free_list(t_node **lst, bool exit, bool exit_status);
void	free_table(t_table **lst, bool exit, bool exit_status);
char	*str_join(char const *s1, char const *s2, const char *s3);

/* ************************************************************************** */
/* 	SHELL																	  */
/* ************************************************************************** */
char	*get_prompt(void);
void	print_shell(void);

/* ************************************************************************** */
/* 	LEXER																	  */
/* ************************************************************************** */
int		lexer(t_node **head, char *input);
int		define_type(char *input);
int		create_tokens(t_node **node, char **input);
int		create_redir_token(t_node **node, char **input);
char	*get_word(char **input, int cmd, int opt);
char	*get_quoted_word(char **input);
int		check_whitespace(char c);
bool	is_metachar(int c);
bool	is_quoted(char c);

/* ************************************************************************** */
/* 	PARSER																	  */
/* ************************************************************************** */
int		parser(t_node **node, t_table **table);
void	create_cmd_table(t_node **node, t_table **table);
int		echo_parse(t_token *help, t_table **new);

/* ************************************************************************** */
/* 	BUILTIN FUNCS															  */
/* ************************************************************************** */
int		ft_pwd(void);
void	ft_echo(t_table **table);
void	ft_cd(t_node **node, char **environ);
void	ft_exit(t_node **node);
void	ft_env(char **environ);
char	*lstlast(t_token *lst);
int		lstsize(t_token *lst);




#endif
