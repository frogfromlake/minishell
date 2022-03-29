/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:04:43 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/29 19:08:40 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	dollar_special_expand(t_stringbuilder **sb, char **tmp)
{
	if (**tmp == '$')
	{
		sb_append_str(*sb, "$$");
		(*tmp)++;
	}
	else if (**tmp == '?')
	{
		sb_append_int(*sb, g_exit_status);
		(*tmp)++;
	}
	else if (**tmp == ' ')
	{
		sb_append_char((*sb), '$');
		(*tmp)++;
	}
	else if (ft_is_digit(**tmp))
		(*tmp)++;
}

static char	*get_word_envname(char **tmp)
{
	t_stringbuilder	*sb;
	char			*env_name;
	int				i;

	i = 0;
	sb = sb_create();
	while (ft_is_all_num((*tmp)[i]) || (*tmp)[i] == '_')
		i++;
	sb_append_strn(sb, *tmp, i);
	env_name = sb_get_str(sb);
	sb_destroy(sb);
	*tmp += i;
	return (env_name);
}

void	dollar_expand(t_stringbuilder **sb, char **tmp)
{
	char	*env_name;

	(*tmp)++;
	if (ft_is_alpha(**tmp) || **tmp == '_')
	{
		env_name = get_word_envname(tmp);
		sb_append_str(*sb, get_env_var(env_name));
		free(env_name);
	}
	else
		dollar_special_expand(sb, tmp);
}
