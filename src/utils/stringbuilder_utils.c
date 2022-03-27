/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringbuilder_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:16:41 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/12 22:46:08 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	sb_append_char(t_stringbuilder *sb, char c)
{
	char	*tmp;
	char	*newstr;

	if (!c)
		return (1);
	newstr = ft_calloc(sb->len + 2, sizeof(char));
	if (!newstr)
		return (2);
	sb_copy_oldstr(sb, &newstr);
	newstr[(sb->len)++] = c;
	tmp = sb->str;
	sb->str = newstr;
	free(tmp);
	return (0);
}

int	sb_append_str(t_stringbuilder *sb, char *str)
{
	char	*tmp;
	int		i;
	char	*newstr;

	if (!str)
		return (1);
	newstr = ft_calloc(sb->len + ft_strlen(str) + 1, sizeof(char));
	if (!newstr)
		return (2);
	sb_copy_oldstr(sb, &newstr);
	i = 0;
	while (str[i])
	{
		newstr[sb->len + i] = str[i];
		i++;
	}
	sb->len += i;
	tmp = sb->str;
	sb->str = newstr;
	free(tmp);
	return (0);
}

int	sb_append_strn(t_stringbuilder *sb, char *str, int len)
{
	char	*tmp;
	int		i;
	char	*newstr;

	if (!str)
		return (1);
	newstr = ft_calloc(sb->len + len + 1, sizeof(char));
	if (!newstr)
		return (2);
	sb_copy_oldstr(sb, &newstr);
	i = 0;
	while (str[i] && i < len)
	{
		newstr[sb->len + i] = str[i];
		i++;
	}
	sb->len += i;
	tmp = sb->str;
	sb->str = newstr;
	free(tmp);
	return (0);
}

int	sb_append_int(t_stringbuilder *sb, int nbr)
{
	char	*nbr_str;

	nbr_str = ft_itoa(nbr);
	if (!nbr_str)
		return (1);
	if (sb_append_str(sb, nbr_str))
	{
		free(nbr_str);
		nbr_str = 0;
		return (2);
	}
	free(nbr_str);
	nbr_str = 0;
	return (0);
}

char	*sb_get_str(t_stringbuilder *sb)
{
	char	*res;
	int		i;

	if (!sb)
		return (NULL);
	res = ft_calloc(sb->len + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (sb->str[i] && i < sb->len)
	{
		res[i] = sb->str[i];
		i++;
	}
	return (res);
}
