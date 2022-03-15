/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:25:35 by fquist            #+#    #+#             */
/*   Updated: 2022/03/15 23:34:07 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	open_file(t_exec *permission, char *file, int mod, int rights)
{
	int	fd;

	fd = open(file, mod, rights);
	if (fd < 0)
		file_error("minishell", strerror(errno), file);
	if (access(file, W_OK) < 0)
	{
		file_error("minishell", strerror(errno), file);
		permission->no_rights = -1;
		return (permission->no_rights);
	}
	return (fd);
}

int	file_error(char *name_b, char *msg, char *name_a)
{
	if (name_b)
		ft_putstr_fd(name_b, 2);
	if (msg)
	{
		if (name_b)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg, 2);
	}
	if (name_a)
	{
		if (msg)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(name_a, 2);
	}
	ft_putchar_fd('\n', 2);
	return (EXIT_FAILURE);
}
