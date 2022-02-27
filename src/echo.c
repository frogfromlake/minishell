/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:19:47 by fquist            #+#    #+#             */
/*   Updated: 2022/02/27 21:45:36 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	ft_echo(t_node **node)
{
	t_token	*token;

	token = (*node)->args;
	if (!token->next)
		printf("\n");
	if (token->next)
	{
		printf("%d\n", check_option_input(token->next));
	}
	else
		return ;
	return ;
}

int	check_options(t_node **node)
{
	t_token	*token;
	int		ops;

	ops = 0;
	token = (*node)->args;
	while (token)
	{
		if (!ft_strncmp(token->cmd, "-n", 2))
			ops++;
		// else if (ft_strlen(token->cmd) > 3)
		// {
		// 	while (token->cmd)
		// }
		token = token->next;
	}
	// printf("%d\n", ops);
	if (ops == 1)
		return (1);
	else
		return (0);
}

int	check_option_input(t_token *cmd)
{
	int		i;
	int		res;
	char	**arr;

	i = 0;
	res = 0;
	arr = malloc(sizeof(char *));
	if (!arr)
		return (0);
	printf("cmd = %s\n", cmd->cmd);
	while (cmd)
	{
		arr[i] = cmd->cmd;
		cmd = cmd->next;
		i++;
	}
	i = 0;
	printf("arr = %s\n", arr[i]);
	while (arr[i])
	{
		if (*arr[i - i] == '-' && *arr[1] == 'n')
		{
			if (*arr[i] == 'n' || !*arr[i])
			{
				printf("arr[i] = %c\n", *arr[i]);
				i++;
			}
		}
		else
		{
			printf("oh no\n");
			res = -1;
			break ;
		}
	}
	// ft_free_array(arr, false, false);
	return (res);
}


/*
DESCRIPTION
	ft_lstlast() returns the last element of the list.
*/
char	*lstlast(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst->cmd);
}


int	lstsize(t_token *lst)
{
	int	count_elements;

	count_elements = 0;
	while (lst != NULL)
	{
		count_elements++;
		lst = lst->next;
	}
	return (count_elements);
}
