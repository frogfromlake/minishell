/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 21:04:56 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/27 01:15:00 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
