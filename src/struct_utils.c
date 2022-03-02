/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:56:58 by fquist            #+#    #+#             */
/*   Updated: 2022/03/02 02:58:40 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_nodes(t_node *node)
{
	while (node)
	{
		printf("%sNODE%s\n", CYAN, RESET);
		printf("Type: %d\n", node->type);
		if (node->tokens)
			print_tokens(node->tokens);
		printf("%s--------%s\n", CYAN, RESET);
		node = node->next;
	}
}

void	print_tokens(t_token *token)
{
	while (token)
	{
		printf("%sTOKEN%s\n", PURPLE, RESET);
		printf("Name: %s\n", token->name);
		printf("Type: %d\n", token->type);
		printf("%s------%s\n", PURPLE, RESET);
		token = token->next;
	}
}

void	print_cmd_table(t_table *table)
{
	while (table)
	{
		printf("EXE: %s\n", table->exe);
		printf("ARGS: %s\n", table->args);
		printf("REDIR_IN: %s\n", table->redir_in);
		printf("REDIR_OUT: %s\n", table->redir_out);
		table = table->next;
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

void	free_table(t_table **lst, bool exit, bool exit_status)
{
	t_table	*current;
	t_table	*next;

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

char	*str_join(char const *s1, char const *s2, char const *s3)
{
	char	*newstr;
	size_t	len1;
	size_t	len2;
	size_t	len3;

	if (!s1 || !s2 || !s3)
		return (NULL);
	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	len3 = ft_strlen((char *)s3);
	newstr = malloc(len1 + len2 + len3 + 1);
	if (!newstr)
		return (NULL);
	if (newstr != NULL)
	{
		ft_memcpy(newstr, s1, len1);
		ft_memcpy(&newstr[len1], s2, len2);
		ft_memcpy(&newstr[len2 + len1], s3, len3);
		newstr[len1 + len2 + len3] = '\0';
	}
	return (newstr);
}
