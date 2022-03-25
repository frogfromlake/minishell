/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:56:58 by fquist            #+#    #+#             */
/*   Updated: 2022/03/07 22:49:59 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	t_redir	*tmp;
	int		i;

	if (!table)
		printf("EMPTY!!!\n");
	while (table)
	{
		i = 0;
		printf("----------\n");
		printf("CMD_ARR: ");
		while (table->cmd_arr[i])
			printf("%s ", table->cmd_arr[i++]);
		printf("%s ", table->cmd_arr[i]);
		printf("\n");
		printf("EXE: %s\n", table->exe);
		printf("ARGS: %s\n", table->args);
		printf("OPT: %d\n", table->opt);
		printf("LOG_OP: %d\n", table->log_op);
		printf("REDIR: ");
		if (table->redir)
		{
			tmp = table->redir;
			while (tmp)
			{
				printf("[%d %s] ", tmp->type, tmp->file);
				tmp = tmp->next;
			}
			tmp = table->redir;
			if (get_last_in_redir(tmp) || get_last_out_redir(tmp))
			{
				printf("|");
				if (get_last_in_redir(tmp))
					printf(" [LAST IN: %s] ", get_last_in_redir(tmp)->file);
				if (get_last_out_redir(tmp))
					printf(" [LAST OUT: %s]", get_last_out_redir(tmp)->file);
			}
		}
		printf("\n");
		printf("----------\n");
		table = table->next;
	}
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

char	*ft_strjoin_ws(char const *s1, char const *s2)
{
	char	*newstr;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	newstr = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 2, sizeof(char));
	i = 0;
	while (s1[i])
	{
		newstr[i] = s1[i];
		i++;
	}
	newstr[i++] = ' ';
	j = 0;
	while (s2[j])
	{
		newstr[i + j] = s2[j];
		j++;
	}
	return (newstr);
}
