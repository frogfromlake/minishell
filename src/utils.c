/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelix <nelix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 16:35:36 by fquist            #+#    #+#             */
/*   Updated: 2022/03/03 05:23:14 by nelix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	error_msg(char *error_msg, int r_value)
{
	ft_putstr_fd(error_msg, 2);
	return (r_value);
}

int	open_file(char *file, int mod, int rights)
{
	int	fd;

	if (ft_strncmp(file, "here_doc", 8) == 0)
		return (STDIN_FILENO);
	fd = open(file, mod, rights);
	if (fd < 0)
		file_error("pipex", strerror(errno), file);
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

int	child_wait_pid(pid_t *pid, int n)
{
	int	i;
	int	status;

	i = 0;
	while (i < n)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	status = status >> 8;
	status = status & 0x000000ff;
	return (status);
}
