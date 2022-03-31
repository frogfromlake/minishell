/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 23:59:21 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/30 18:06:50 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 130;
	}
}

void	sigint_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		change_termios(false);
		g_exit_status = FAIL;
		exit(g_exit_status);
	}
}

void	sigchild_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_exit_status = 130;
	}
	if (sig == SIGQUIT)
	{
		write(2, "Quit: 3\n", 9);
		g_exit_status = SUCCESS;
	}
}
