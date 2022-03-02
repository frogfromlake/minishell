/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 03:59:54 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/02 04:07:15 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_parser(t_token *curr_t, t_table **new)
{
	if (curr_t->type == LESS || curr_t->type == LESSLESS)
	{
		if ((*new)->redir_in)
			(*new)->redir_in = str_join((*new)->redir_in, " ", curr_t->name);
		else
			(*new)->redir_in = ft_strdup(curr_t->name);
	}
	else
	{
		if ((*new)->redir_out)
			(*new)->redir_out = str_join((*new)->redir_out, " ", curr_t->name);
		else
			(*new)->redir_out = ft_strdup(curr_t->name);
	}
	return (1);
}
