/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelix <nelix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:39:49 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/20 05:55:09 by nelix            ###   ########.fr       */
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

static void add_args_to_arr(t_token *token, t_table **new)
{
	t_stringbuilder	*sb;
	char			*trimmed;
	char			dquote;
	char			squote;

	dquote = '\"';
	squote = '\'';
	sb = sb_create();
	while (token)
	{
		if ((token->name[0] == dquote && token->name[1] == squote)
			|| (token->name[0] == squote && token->name[1] == dquote))
		{
			insert_cmd_arr(&(*new)->cmd_arr, token->name);
			return ;
		}
		if ((token->name[0] == dquote) || (token->name[0] == squote))
		{
			if (token->name[0] == squote)
				trimmed = ft_strtrim(token->name, "\'");
			if (token->name[0] == dquote)
				trimmed = ft_strtrim(token->name, "\"");
			if ((trimmed[0] == dquote) || (trimmed[0] == squote))
				continue ;
			else
			{
				sb_append_str(sb, trimmed);
				if (token->next)
					sb_append_char(sb, ' ');
				insert_cmd_arr(&(*new)->cmd_arr, trimmed);
				free(trimmed);
			}
		}
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

int	command_parser(t_token *token, t_table **new)
{
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
