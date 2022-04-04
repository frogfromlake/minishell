/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 23:09:51 by dmontema          #+#    #+#             */
/*   Updated: 2022/04/04 14:50:52 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	token_parser(t_token *token, t_table **new)
{
	while (token && (g_exit_status == SUCCESS))
	{
		if (token->type == COMMAND)
			g_exit_status = command_parser(&token, new);
		else if (check_redir(token->type))
			g_exit_status = redir_parser(&token, new);
		else
			g_exit_status = arg_parser(&token, new);
	}
}
