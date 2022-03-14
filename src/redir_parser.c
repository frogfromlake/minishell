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

// static void	insert_redir_type(t_token *curr_t, t_table **new)
// {
	

	// t_type	*tmp_redir;
	// char	**tmp_infiles;
	// int		i;
	// int		count;

	// if ((*new)->redir_in)
	// {
	// 	tmp_redir = (*new)->redir_in;
	// 	tmp_infiles = (*new)->infiles;
	// 	free((*new)->redir_in);
	// 	free((*new)->infiles);
	// }
	// count = sizeof(tmp_redir) / sizeof(t_type);
	// (*new)->redir_in = ft_calloc(count + 1, sizeof(t_type));
	// (*new)->infiles = ft_calloc(count + 1, sizeof(char));
	// i = 0;
	// printf("%d\n", count);
	// while (i < count)
	// {
	// 	(*new)->redir_in[i] = tmp_redir[i];
	// 	(*new)->infiles[i] = tmp_infiles[i];
	// 	i++;
	// }
	// (*new)->redir_in[i] = curr_t->type;
	// (*new)->infiles[i] = curr_t->name;
	// free(tmp_redir);
	// free(tmp_infiles);
// }

int	redir_parser(t_token *curr_t, t_table **new)
{
	if (curr_t->type == LESS || curr_t->type == LESSLESS)
	{
		if (curr_t->type == LESS)
		{
			ft_lstadd_back(&(*new)->redir_in, ft_lstnew(&curr_t->type));
			ft_lstadd_back(&(*new)->infiles, ft_lstnew(curr_t->name));
		}
		else
		{
			ft_lstadd_back(&(*new)->redir_in, ft_lstnew(&curr_t->type));
			ft_lstadd_back(&(*new)->delimiter, ft_lstnew(curr_t->name));
		}
	}
	else if (curr_t->type == GREAT || curr_t->type == GREATGREAT)
	{
		ft_lstadd_back(&(*new)->redir_out, ft_lstnew(&curr_t->type));
		ft_lstadd_back(&(*new)->outfiles, ft_lstnew(curr_t->name));
	}
	return (1);
}
