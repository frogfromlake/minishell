/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:24:41 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/11 23:00:52 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_cmd_arr_size(char **arr)
{
	int	res;

	res = 0;
	while (arr[res])
		res++;
	return (res);
}

int	insert_cmd_arr(char ***arr, char *str)
{
	int		i;
	int		size;
	char	**tmp;

	tmp = *arr;
	size = get_cmd_arr_size(tmp);
	*arr = ft_calloc(size + 2, sizeof(char *));
	i = 0;
	while (tmp[i])
	{
		(*arr)[i] = ft_strdup(tmp[i]);
		i++;
	}
	(*arr)[i] = ft_strdup(str);
	return (1);
}

int	parser(t_node **node, t_table **table)
{
	create_cmd_table(node, table);
	return (0);
}

void	create_cmd_table(t_node **node, t_table **table)
{
	t_node	*curr_n;
	// t_token	*token;
	t_table	*new;

	curr_n = *node;
	while (curr_n)
	{
		new = append_table(table, new_table());
		if (check_log_op(curr_n->type))
		{
			new->log_op = curr_n->type;
			curr_n = curr_n->next;
			continue ;
		}
		while (curr_n && !check_log_op(curr_n->type))
		{
			if (check_redir(curr_n->type))
				redir_parser(curr_n->tokens, &new);
			if (curr_n->type == COMMAND)
			{
				command_parser(curr_n->tokens, &new);
				// new->exe = ft_strdup(curr_n->tokens->name);
				// if (!check_builtin(new))
				// {
				// 	if (set_cmd_path(&new, get_env(NULL)))
				// 		printf("bitchy snake shell: command not found: %s\n", new->exe);
				// 	else
				// 	{
				// 		if (curr_n->tokens->next)
				// 		{
				// 			token = curr_n->tokens->next;
				// 			while (token)
				// 			{
				// 				if (!new->args)
				// 					new->args = ft_strdup(token->name);
				// 				else
				// 					new->args = ft_strjoin_ws(new->args, token->name);
				// 				insert_cmd_arr(&new->cmd_arr, token->name);
				// 				token = token->next;
				// 			}
				// 		}
				// 	}
				// }
				// else if (!ft_strcmp(new->exe, "echo"))
				// {
				// 	if (curr_n->tokens->next)
				// 		echo_parser(curr_n->tokens->next, &new);
				// }
				// else 
				// {
				// 	if (curr_n->tokens->next)
				// 	{
				// 		new->args = ft_strdup(curr_n->tokens->next->name);
				// 	}
				// }
			}
			curr_n = curr_n->next;
		}
	}
}
