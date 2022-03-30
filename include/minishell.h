/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:49:49 by fquist            #+#    #+#             */
/*   Updated: 2022/03/30 01:28:20 by fquist           ###   ########.fr       */
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
# include <dirent.h>

# include "../libs/libft/include/libft.h"
# include "stringbuilder.h"
# include "structs.h"
# include "built_ins.h"
# include "lexer.h"
# include "expander.h"
# include "parser.h"
# include "signals.h"
# include "exec.h"

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
/* 	SHELL																	  */
/* ************************************************************************** */
char	*get_prompt(void);
void	print_header(void);

/* ************************************************************************** */
/* 	FREES																	  */
/* ************************************************************************** */
void	print_nodes(t_node *node);
void	print_tokens(t_token *token);
void	print_cmd_table(t_table *table);

void	free_node(t_node **node);
void	free_token(t_token **token);
void	free_table(t_table **table);
void	free_redir(t_redir **redir);
void	free_cmd_arr(char **cmd_arr);

#endif
