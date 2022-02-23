/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:56:58 by fquist            #+#    #+#             */
/*   Updated: 2022/02/24 00:49:46 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *input)
{
	(void) input;
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->cmd = input;
	new->type = COMMAND;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_token	*get_last_token(t_token *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

t_token	*append_token(t_token **head, t_token *new)
{
	t_token	*last;

	if (!(*head))
		*head = new;
	else
	{
		last = get_last_token(*head);
		last->next = new;
		new->prev = last;
	}
	return (new);
}

t_node	*new_node()
{
	t_node	*new;

	new = ft_calloc(1, sizeof(t_node));
	if (!new)
		return (NULL);
	new->args = NULL;
	new->here_doc = NULL;
	new->cmdpath = NULL;
	new->cmd_arr = NULL;
	new->in = PIPEIN;
	new->out = PIPEOUT;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_node	*get_last_node(t_node *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

t_node	*append_node(t_node **head, t_node *new)
{
	t_node	*last;

	if (!(*head))
		*head = new;
	else
	{
		last = get_last_node(*head);
		last->next = new;
		new->prev = last;
	}
	return (new);
}

void	print_nodes(t_node *head)
{
	while (head)
	{
		printf("%d\n", head->type);
		print_tokens(head->args);
		head = head->next;
	}
}

void	print_tokens(t_token *head)
{
	while (head)
	{
		printf("%s\n", head->cmd);
		head = head->next;
	}
}

void	free_list(t_node **lst, bool exit, bool exit_status)
{
	t_node	*current;
	t_node	*next;

	current = *lst;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*lst = NULL;
	lst = NULL;
	if (exit == true && exit_status == false)
		ft_exit_print(exit_status, "Error\n", 2);
	else if (exit == true && exit_status == true)
		ft_exit_print(exit_status, "Error\n", 2);
}
