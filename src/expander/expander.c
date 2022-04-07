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

#include "../../include/minishell.h"

void	dquote_expand(t_stringbuilder **sb, char **tmp)
{
	sb_append_char(*sb, **tmp);
	(*tmp)++;
	while (**tmp && **tmp != DQUOTE)
	{
		if (**tmp == '$' && (*(*tmp + 1) == DQUOTE || *(*tmp + 1) == ' '))
			sb_append_char(*sb, '$');
		else if (**tmp == '$')
		{
			dollar_expand(sb, tmp);
			continue ;
		}
		else
			sb_append_char(*sb, **tmp);
		(*tmp)++;
	}
	if (**tmp)
	{
		sb_append_char(*sb, **tmp);
		(*tmp)++;
	}
}

void	squote_no_expand(t_stringbuilder **sb, char **tmp)
{
	int	i;

	i = 1;
	while ((*tmp)[i] && (*tmp)[i] != SQUOTE)
		i++;
	if ((*tmp)[i] == SQUOTE)
		i++;
	sb_append_strn(*sb, *tmp, i);
	*tmp += i;
}

void	expand(char **str)
{
	t_stringbuilder	*sb;
	char			*tmp;

	sb = sb_create();
	tmp = *str;
	while (*tmp)
	{
		if (*tmp == '$')
			dollar_expand(&sb, &tmp);
		else if (*tmp == DQUOTE)
			dquote_expand(&sb, &tmp);
		else if (*tmp == SQUOTE)
			squote_no_expand(&sb, &tmp);
		else
		{
			sb_append_char(sb, *tmp);
			tmp++;
		}
	}
	free(*str);
	*str = sb_get_str(sb);
	sb_destroy(sb);
}

static bool	check_valid_expand_arg(t_token **token)
{
	if ((*token)->type == LESSLESS)
	{
		if ((*token)->next)
			(*token) = (*token)->next;
		return (false);
	}
	if (ft_strchr((*token)->name, '$')
		|| ft_strchr((*token)->name, SQUOTE)
		|| ft_strchr((*token)->name, DQUOTE))
		return (true);
	return (false);
}

int	expander(t_node **head)
{
	t_node	*node;
	t_token	*token;

	node = *head;
	while (node)
	{
		if (!check_log_op(node->type) && node->tokens)
		{
			token = node->tokens;
			while (token)
			{
				if (check_valid_expand_arg(&token))
				{
					expand(&token->name);
					if (!ft_strcmp(token->name, "\"\"") || !(*token->name))
						token->type = NONEXISTENV;
				}
				token = token->next;
			}
		}
		node = node->next;
	}
	return (1);
}
