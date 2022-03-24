/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:44:58 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/24 19:15:49 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sigint_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		// write(1, "\n", 1);
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
		unset_attr();
		exit(FAIL);
	}
}

void 	ft_sigchild(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
}

void 	ft_sigchild1(int sig)
{
	if (sig == SIGQUIT)
		write(1, "Quit: 3\n", 9);
}

void set_attr(void)
{
	struct termios termios_p;

	if (tcgetattr(STDIN_FILENO, &termios_p) == -1)
		return ;
	termios_p.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(0, 0, &termios_p) == -1)
		return ;
	signal(SIGINT, sigint_handler);
	// signal(SIGQUIT, SIG_IGN);
}

void set_attr_heredoc(void)
{
	struct termios termios_p;

	if (tcgetattr(STDIN_FILENO, &termios_p) == -1)
		return ;
	termios_p.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(0, 0, &termios_p) == -1)
		return ;
	signal(SIGINT, sigint_handler_heredoc);
	// signal(SIGQUIT, SIG_IGN);
}

void unset_attr(void)
{
	struct termios	termios_p;

	if (tcgetattr(1, &termios_p) == -1)
		return ;
	termios_p.c_lflag |= (ECHOCTL);
	if (tcsetattr(1, 0, &termios_p) == -1)
		return ;
	signal(SIGINT, ft_sigchild);
	signal(SIGQUIT, ft_sigchild1);
}

