/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:39:49 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/22 13:55:53 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	command_parser(t_token *token, t_table **new)
{
	(*new)->exe = ft_strdup(token->name);
	if (!check_builtin(*new))
	{
		g_exit_status = set_cmd_path(new, get_env(NULL));
		if (g_exit_status)
			printf("bitchy snake shell: command not found: %s\n", (*new)->exe); // TODO: create a error_exit func)
		else
			if (token->next)
				add_args_to_arr(token->next, new);
	}
	else if (!ft_strcmp((*new)->exe, "echo"))
	{
		if (token->next)
			if (define_echo_args(token->next, new))
				(*new)->opt = 1;
	}
	else
	{
		if (token->next) // TODO: implement for more args (e.g. export can also set multiple args at once.)
			(*new)->args = ft_strdup(token->next->name);
	}
	return (0);
}
