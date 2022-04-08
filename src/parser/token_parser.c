/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 23:09:51 by dmontema          #+#    #+#             */
/*   Updated: 2022/04/08 21:49:19 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	token_parser(t_token *token, t_table **new)
{
	while (token)
	{
		if (token->type == COMMAND)
			g_exit_status = command_parser(&token, new);
		else if (check_redir(token->type))
			g_exit_status = redir_parser(&token, new);
		else
			g_exit_status = arg_parser(&token, new);
	}
}
