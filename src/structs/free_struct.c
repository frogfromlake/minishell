/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:30:58 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/26 23:50:11 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: check again, if freeing correctly

#include "../../include/minishell.h"

void	free_node(t_node **node)
{
	t_node	*curr;
	t_node	*next;

	curr = *node;
	while (curr)
	{
		next = curr->next;
		if (curr->tokens)
			free_token(&curr->tokens);
		free(curr);
		curr = next;
	}
	*node = NULL;
	node = NULL;
}

void	free_token(t_token **token)
{
	t_token	*curr;
	t_token	*next;

	curr = *token;
	while (curr)
	{
		next = curr->next;
		free(curr->name);
		curr->name = NULL;
		free(curr);
		curr = next;
	}
	*token = NULL;
	token = NULL;
}

void	free_table(t_table **table)
{
	t_table	*curr;
	t_table	*next;

	curr = *table;
	while (curr)
	{
		next = curr->next;
		if (curr->cmd_arr)
			free_cmd_arr(curr->cmd_arr);
		if (curr->exe)
			free(curr->exe);
		if (curr->args)
			free(curr->args);
		if (curr->redir)
			free_redir(&curr->redir);
		free(curr);
		curr = next;
	}
	*table = NULL;
	table = NULL;
}

void	free_redir(t_redir **redir)
{
	t_redir	*curr;
	t_redir	*next;

	curr = *redir;
	while (curr)
	{
		next = curr->next;
		free(curr->file);
		free(curr);
		curr = next;
	}
	*redir = NULL;
	redir = NULL;
}

void	free_cmd_arr(char **cmd_arr)
{
	int	i;

	i = 0;
	while (cmd_arr[i])
	{
		free(cmd_arr[i]);
		i++;
	}
	free(cmd_arr);
}
