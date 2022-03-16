/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:47:19 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/13 00:41:03 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	delete_token(t_token **token)
{
	t_token	*tmp;

	tmp = (*token)->next;
	(*token)->prev->next = tmp;
	if (tmp)
		tmp->prev = (*token)->prev;
	free((*token)->name);
	(*token)->name = NULL;
	free(*token);
	*token = tmp;
}

void	add_env_var(t_stringbuilder **sb, char **tmp)
{
	char	*env_var;

	(*tmp)++;
	env_var = get_word_ws(tmp);
	sb_append_str((*sb), get_env_var(env_var));
	free(env_var);
	env_var = NULL;
}

void	complex_expand(t_token **token)
{
	t_stringbuilder	*sb;
	char			*tmp;

	sb = sb_create();
	tmp = (*token)->name;
	while (*tmp)
	{
		if (*tmp == '$')
		{
			add_env_var(&sb, &tmp);
			continue ;
		}
		sb_append_char(sb, *tmp);
		tmp++;
	}
	tmp = (*token)->name;
	(*token)->name = sb_get_str(sb);
	sb_destroy(sb);
	free(tmp);
	if (!ft_strcmp((*token)->name, "\"\""))
		delete_token(token);
	else
		(*token) = (*token)->next;
}

void	simple_expand(t_token **token)
{
	char	*env_var;

	env_var = get_env_var((*token)->name + 1);
	if (!env_var)
		delete_token(token);
	else
	{
		free((*token)->name);
		(*token)->name = ft_strdup(env_var);
		(*token) = (*token)->next;
	}
}

int	expander(t_node **head)
{
	t_node	*node;
	t_token	*token;

	node = *head;
	while (node)
	{
		if (!check_log_op(node->type) && node->type != LESSLESS)
		{
			if (node->tokens)
			{
				token = node->tokens;
				while (token)
				{
					if (*token->name == '$')
						simple_expand(&token);
					else if (*token->name == '\"')
						complex_expand(&token);
					else
						token = token->next;
				}
			}
		}
		node = node->next;
	}
	return (1);
}
