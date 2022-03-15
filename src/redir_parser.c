/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 03:59:54 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/03 23:38:20 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	redir_parser(t_token *curr_t, t_table **new)
{
	append_redir(&(*new)->redir, new_redir(curr_t->type, curr_t->name));
	return (1);
}
