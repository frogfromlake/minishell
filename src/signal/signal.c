/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:44:58 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/22 16:41:36 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigint_handler(int sig)
{
	// char	*prompt;

	if (sig == SIGINT)
	{
		// write(1, "\n", 1);
		// prompt = get_prompt();
		// printf("%s", prompt);
		// free(prompt);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void set_attr(void)
{
	struct termios termios_p;

	// fprintf(stderr, "SET_ATTR IS RUNNING\n");
	if (tcgetattr(STDIN_FILENO, &termios_p) == -1)
		return ;
	termios_p.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(0, 0, &termios_p) == -1)
		return ;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void unset_attr(void)
{
	struct termios termios_p;

	if (tcgetattr(1, &termios_p) == -1)
		return ;
	termios_p.c_lflag |= (ECHOCTL);
	if (tcsetattr(1, 0, &termios_p) == -1)
		return ;
	// signal(SIGINT, ft_sigchild);
}

