/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:05:21 by fquist            #+#    #+#             */
/*   Updated: 2022/04/04 15:35:28 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/* ************************************************************************** */
/* 	ENUMERATION																  */
/* ************************************************************************** */

typedef enum e_type
{
	COMMAND = 0,
	OPTION = -3,
	ARG,
	REDIR_FILE,
	NONEXISTENV = -5,
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

/* ************************************************************************** */
/* 	DATA STRUCTURES															  */
/* ************************************************************************** */

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
	bool			hidden;
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
/* 	DATA STRUCTURE UTILS													  */
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

t_redir	*new_redir(t_type type, char *file);
t_redir	*get_last_redir(t_redir *head);
t_redir	*append_redir(t_redir **head, t_redir *new);
t_redir	*get_last_in_redir(t_redir *head);
t_redir	*get_last_out_redir(t_redir *head);

t_exec	*new_exec(void);

char	*lstlast(t_token *lst);
int		lstsize(t_token *lst);

#endif