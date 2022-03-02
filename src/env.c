/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:41:10 by fquist            #+#    #+#             */
/*   Updated: 2022/03/02 04:23:14 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_env	*new_env(char *str)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->var = str;
	new->val = 0;
	new->next = NULL;
	return (new);
}

t_env	*get_last_env(t_env *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

t_env	*append_env(t_env **head, t_env *new)
{
	t_env	*last;

	if (!(*head))
		*head = new;
	else
	{
		last = get_last_env(*head);
		last->next = new;
	}
	return (new);
}

t_env	*insert_env(t_env **current, t_env *new)
{
	new->next = (*current)->next;
	(*current)->next = new;
	return (new);
}

t_env	**ft_env(char **environ)
{
	int				i;
	static t_env	*env;
	t_env			*tmp;

	if (!env)
	{
		i = 0;
		while (environ[i])
		{
			append_env(&env, new_env(environ[i]));
			i++;
		}
	}
	tmp = env;
	while (tmp)
	{
		printf("%s\n", tmp->var);
		tmp = tmp->next;
	}
	return (&env);
}
