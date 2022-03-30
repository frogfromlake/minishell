/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 21:04:56 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/30 02:54:52 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_args_var_name(char *args)
{
	t_stringbuilder	*sb;
	int				i;
	char			*res;

	sb = sb_create();
	i = 0;
	while (args[i])
	{
		if (args[i] == '=')
			break ;
		i++;
	}
	sb_append_strn(sb, args, i);
	res = sb_get_str(sb);
	sb_destroy(sb);
	return (res);
}

t_env	*check_var_existence(t_env **env, char *args)
{
	t_env	*tmp;
	char	*var_name;
	char	*args_var_name;

	tmp = *env;
	while (tmp)
	{
		var_name = get_var_name(tmp);
		args_var_name = get_args_var_name(args);
		if (!ft_strcmp(var_name, args_var_name))
		{
			free(args_var_name);
			free(var_name);
			return (tmp);
		}
		free(args_var_name);
		free(var_name);
		tmp = tmp->next;
	}
	return (NULL);
}

static void	rm_pluschar(char **str)
{
	t_stringbuilder	*sb;
	int				i;

	sb = sb_create();
	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '+')
		{
			i++;
			continue ;
		}
		sb_append_char(sb, (*str)[i]);
		i++;
	}
	free(*str);
	*str = sb_get_str(sb);
	sb_destroy(sb);
}

bool	check_valid_var(char **str)
{
	int		i;
	bool	rm_plus;

	rm_plus = false;
	if (!ft_is_alpha(**str) && **str != '_')
		return (false);
	i = 1;
	while ((*str)[i] && (*str)[i] != '=')
	{
		if ((*str)[i] == '+' && (*str)[i + 1] && (*str)[i + 1] == '=')
		{
			i++;
			rm_plus = true;
			continue ;
		}
		if (!ft_is_all_num((*str)[i]) && (*str)[i] != '_')
			return (false);
		i++;
	}
	if (rm_plus)
		rm_pluschar(str);
	return (true);
}
