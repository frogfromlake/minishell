/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelix <nelix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:39:49 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/20 07:52:59 by nelix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// TODO: put the cmd_arr funcs to another file?!
int	get_cmd_arr_size(char **arr)
{
	int	res;

	res = 0;
	while (arr[res])
		res++;
	return (res);
}

int	insert_cmd_arr(char ***arr, char *str)
{
	int		i;
	int		size;
	char	**tmp;

	tmp = *arr;
	size = get_cmd_arr_size(tmp);
	*arr = ft_calloc(size + 2, sizeof(char *));
	i = 0;
	while (tmp[i])
	{
		(*arr)[i] = ft_strdup(tmp[i]);
		i++;
	}
	(*arr)[i] = ft_strdup(str);
	return (1);
}

static void	trimm_arg_quotes(t_token *token, t_table **new)
{
	t_stringbuilder	*sb;
	t_token			*tmp;
	char			*trimmed;

	tmp = token;
	sb = sb_create();
	while (tmp)
	{
		printf("tmp: %s\n", tmp->name);
		if ((tmp->name[0] == DQUOTE && tmp->name[1] == SQUOTE)
			|| (tmp->name[0] == SQUOTE && tmp->name[1] == SQUOTE))
		{
			insert_cmd_arr(&(*new)->cmd_arr, tmp->name);
			return ;
		}
		if ((tmp->name[0] == DQUOTE) || (tmp->name[0] == SQUOTE))
		{
			if (tmp->name[0] == SQUOTE)
				trimmed = ft_strtrim(tmp->name, "\'");
			if (tmp->name[0] == DQUOTE)
				trimmed = ft_strtrim(tmp->name, "\"");
			if ((trimmed[0] == DQUOTE) || (trimmed[0] == SQUOTE))
				continue ;
			else
			{
				sb_append_str(sb, trimmed);
				if (tmp->next)
					sb_append_char(sb, ' ');
				insert_cmd_arr(&(*new)->cmd_arr, trimmed);
				free(trimmed);
			}
		}
		tmp = tmp->next;
	}
}

static void	add_args_to_arr(t_token *token, t_table **new)
{
	t_stringbuilder	*sb;

	sb = sb_create();
	while (token)
	{
		if ((token->name[0] == DQUOTE) || (token->name[0] == SQUOTE))
			trimm_arg_quotes(token, new);
		else
		{
			sb_append_str(sb, token->name);
			if (token->next)
				sb_append_char(sb, ' ');
			insert_cmd_arr(&(*new)->cmd_arr, token->name);
		}
		token = token->next;
	}
	(*new)->args = sb_get_str(sb);
	sb_destroy(sb);
}

static void	trimm_cmd_quotes(t_token *token, t_table **new)
{
	t_stringbuilder	*sb;
	t_token			*tmp;
	char			*trimmed;

	tmp = token;
	sb = sb_create();
	(void)new;
	while (tmp)
	{
		if ((tmp->name[0] == DQUOTE && tmp->name[1] == SQUOTE)
			|| (tmp->name[0] == SQUOTE && tmp->name[1] == SQUOTE))
		{
			// insert_cmd_arr(&(*new)->cmd_arr, tmp->name);
			return ;
		}
		if ((tmp->name[0] == DQUOTE) || (tmp->name[0] == SQUOTE))
		{
			if (tmp->name[0] == SQUOTE)
				trimmed = ft_strtrim(tmp->name, "\'");
			if (tmp->name[0] == DQUOTE)
				trimmed = ft_strtrim(tmp->name, "\"");
			if ((trimmed[0] == DQUOTE) || (trimmed[0] == SQUOTE))
				continue ;
			else
			{
				sb_append_str(sb, trimmed);
				if (tmp->next)
					sb_append_char(sb, ' ');
				// insert_cmd_arr(&(*new)->cmd_arr, trimmed);
				free(trimmed);
			}
		}
		tmp = tmp->next;
	}
}

int	command_parser(t_token *token, t_table **new)
{
	t_token *tmp;
	t_stringbuilder	*sb;

	if ((token->name[0] == DQUOTE) || (token->name[0] == SQUOTE))
	{
		tmp = token;
		while (tmp)
		{		
			sb = sb_create();
			trimm_cmd_quotes(token, new);
			(*new)->exe = sb_get_str(sb);
			sb_destroy(sb);
			tmp = tmp->next;
		}
	}
	else
		(*new)->exe = ft_strdup(token->name);
	if (!check_builtin(*new))
	{
		if (set_cmd_path(new, get_env(NULL)))
			printf("bitchy snake shell: command not found: %s\n", (*new)->exe); // TODO: create a error_exit func)
		else
			if (token->next)
				add_args_to_arr(token->next, new);
	}
	else if (!ft_strcmp((*new)->exe, "echo"))
	{
		if (token->next)
			if (define_echo_args(token->next, new))
				(*new)->opt = 1;
	}
	else
	{
		if (token->next) // TODO: implement for more args (e.g. export can also set multiple args at once.)
			(*new)->args = ft_strdup(token->next->name);
	}
	return (0);
}
