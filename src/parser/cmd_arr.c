/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 01:46:59 by dmontema          #+#    #+#             */
/*   Updated: 2022/04/04 14:52:12 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_arr_size(char **arr)
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
	size = get_arr_size(tmp);
	*arr = ft_calloc(size + 2, sizeof(char *));
	i = 0;
	while (tmp[i])
	{
		(*arr)[i] = ft_strdup(tmp[i]);
		i++;
	}
	(*arr)[i] = ft_strdup(str);
	ft_free_split(tmp);
	return (SUCCESS);
}

void	add_args_to_arr(t_token *token, t_table **new)
{
	t_stringbuilder	*sb;

	sb = sb_create();
	while (token)
	{
		sb_append_str(sb, token->name);
		if (token->next)
			sb_append_char(sb, ' ');
		insert_cmd_arr(&(*new)->cmd_arr, token->name);
		token = token->next;
	}
	(*new)->args = sb_get_str(sb);
	sb_destroy(sb);
}
