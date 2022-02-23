/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 21:25:26 by dmontema          #+#    #+#             */
/*   Updated: 2022/02/09 21:28:12 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(char *name)
{
	t_cmd	*res;

	res = (t_cmd *) malloc(sizeof(t_cmd *));
	if (!res)
		return (NULL);
	res->cmd = name;
	res->next = NULL;
	return (res);
}

int	add_back(t_cmd **list, t_cmd *new)
{
	t_cmd	*last;

	if (new == NULL)
		return (0);
	if (*list == NULL)
	{
		*list = new;
		return (1);
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = new;
	return (1);
}