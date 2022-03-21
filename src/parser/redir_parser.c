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

#include "../../include/minishell.h"

// TODO: error handling, change name of check_redir_quotes

int	redir_parser(t_token *curr_t, t_table **new)
{
	t_type	type;
	char	*filename;

	type = curr_t->type;
	filename = ft_strdup(curr_t->name);
	append_redir(&(*new)->redir, new_redir(type, filename));
	return (1);
}
