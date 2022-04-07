/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:49:49 by fquist            #+#    #+#             */
/*   Updated: 2022/04/07 19:39:01 by dmontema         ###   ########.fr       */
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
# define SIGQUIT 3
# define WRITE 1
# define READ 0
# define SUCCESS 0
# define FAIL 1

/* ************************************************************************** */
/* 	SHELL																	  */
/* ************************************************************************** */
char	*get_prompt(void);
void	print_header(void);
void	init_snake_shell(t_node **head, t_table **table);

/* ************************************************************************** */
/* 	FREES																	  */
/* ************************************************************************** */
void	free_node(t_node **node);
void	free_token(t_token **token);
void	free_table(t_table **table);
void	free_redir(t_redir **redir);
void	free_cmd_arr(char **cmd_arr);

#endif
