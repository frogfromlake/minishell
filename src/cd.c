/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 18:37:24 by fquist            #+#    #+#             */
/*   Updated: 2022/02/28 18:29:41 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_node **node, char **environ)
{
	t_token	*token;
	char	*home;
	int		i;

	i = 0;
	token = (*node)->tokens;
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], "HOME", 4))
			home = ft_strchr(environ[i], '/');
		i++;
	}
	if (!token->next || !ft_strcmp(token->next->name, "~"))
		chdir(home);
	else
		chdir(token->next->name);
}
