/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:49:49 by fquist            #+#    #+#             */
/*   Updated: 2022/02/26 18:45:38 by fquist           ###   ########.fr       */
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
# define GREEN	"\033[0;32m"
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
	LPAREN = '(',
	RPAREN = ')',
	GREAT = '>',
	LESS = '<',
	AND = 152,
	LESSLESS = 240,
	GREATGREAT = 248,
	OR = 496,
	AMPERSAND = '&',
}			t_type;

typedef struct s_token
{
	char			*cmd;
	// int				cmd_present;
	int				is_option;
	int				state;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef struct s_node
{
	t_token			*args;
	t_token			*here_doc;
	char			*cmdpath;
	char			**cmd_arr;
	int				in;
	int				out;
	t_type			type;
	struct s_node	*next;
	struct s_node	*prev;
}				t_node;

t_node	*new_node(void);
t_node	*get_last_node(t_node *head);
t_node	*append_node(t_node **head, t_node *new);
t_token	*new_token(char *input);
t_token	*get_last_token(t_token *head);
t_token	*append_token(t_token **head, t_token *new);
void	print_nodes(t_node *node);
char	*print_tokens(t_token *head);
void	free_list(t_node **lst, bool exit, bool exit_status);

/* ************************************************************************** */
/* 	BUILTIN FUNCS															  */
/* ************************************************************************** */
int		ft_pwd(void);
void	ft_echo(t_node **node);
void	ft_cd(t_node **node);

/* ************************************************************************** */
/* 	FUNCTIONS																  */
/* ************************************************************************** */
int		parser(t_token **commands, char *args);
void	print_shell(void);

int		check_whitespace(char c);
int		lexer(t_node **head, char *input);

#endif
