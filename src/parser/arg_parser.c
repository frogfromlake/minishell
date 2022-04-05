/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 23:04:37 by dmontema          #+#    #+#             */
/*   Updated: 2022/04/04 14:05:59 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	arg_parser(t_token **token, t_table **new)
{
	g_exit_status = insert_cmd_arr(&(*new)->cmd_arr, (*token)->name);
	(*token) = (*token)->next;
	return (g_exit_status);
}
