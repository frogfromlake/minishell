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

#include "../include/stringbuilder.h"

int	sb_append_char(t_stringbuilder *sb, char c)
{
	char 	*tmp;
	int		old_len;
	int		i;
	char	*newstr;

	if (!c)
		return (1);
	newstr = ft_calloc(sb->len + 2, sizeof(char));
	if (!newstr)
		return (2);
	i = 0;
	old_len = sb->len;
	while (i < old_len)
	{
		newstr[i] = sb->str[i];
		i++;
	} 
	newstr[i] = c;
	sb->len = ++i;
	newstr[++i] = 0;
	tmp = sb->str;
	sb->str = newstr;
	free(tmp);
	return (0);
}

int	sb_append_str(t_stringbuilder *sb, char *str) //FIXME: line too long!
{
	int		str_len;
	char	*tmp;
	int		i;
	int		j;
	char	*newstr;

	if (!str)
		return (1);
	str_len = ft_strlen(str);
	newstr = ft_calloc(sb->len + str_len + 1, sizeof(char));
	if (!newstr)
		return (2);
	i = 0;
	while (i < sb->len)
	{
		newstr[i] = sb->str[i];
		i++;
	}
	j = 0;
	while (j < str_len)
	{
		newstr[i + j] = str[j];
		j++;
	}
	newstr[i + j] = 0;
	sb->len = i + j;
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
	res = ft_calloc(sb->len, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (sb->str[i] && i < sb->len)
	{
		res[i] = sb->str[i];
		i++;
	}
	res[i] = 0;
	return (res);
}
