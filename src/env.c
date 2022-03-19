/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:41:10 by fquist            #+#    #+#             */
/*   Updated: 2022/03/10 23:00:05 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// TODO: more syntax control

t_env	*new_env(char *str)
{
	t_env	*new;

	if (!str)
		return (NULL);
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->var = ft_strdup(str);
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

t_env	**get_env(char **environ)
{
	static t_env	*env;
	int				i;

	if (!env)
	{
		// TODO:if environ is NULL -> Error: Couldn't create env variables.
		i = 0;
		while (environ[i])
		{
			append_env(&env, new_env(environ[i]));
			i++;
		}
	}
	return (&env);
}

void	ft_env()
{
	t_env	*tmp;

	tmp = *(get_env(NULL));
	while (tmp)
	{
		printf("%s\n", tmp->var);
		tmp = tmp->next;
	}
}
