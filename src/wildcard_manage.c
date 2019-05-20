/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_manage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 07:08:19 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/20 07:18:26 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**		a_star: after star		b_star: before star
*/

int				is_fine_b(char *str, char *before)
{
	int			i;

	i = 0;
	while (before[i])
	{
		if (before[i] != str[i])
			return (0);
		i++;
	}
	return (1);
}

int				is_fine_a(char *str, char *after)
{
	int			i;
	int			j;

	i = ft_strlen(after) - 1;
	j = ft_strlen(str) - 1;
	while (i >= 0)
		if (str[j--] != after[i--])
			return (0);
	return (1);
}

static int		ft_strlen_ab(char *str, char *b_star, char *a_star)
{
	int			len;
	int			len_a;
	int			len_b;
	int			i;

	len = ft_strlen(str);
	len_b = (b_star) ? ft_strlen(b_star) : 0;
	len_a = (a_star) ? ft_strlen(a_star) : 0;
	len -= len_b + len_a;
	i = len_b - 1;
	while (str[++i] && str[i] == '*')
		len--;
	i = ft_strlen(str) - len_a;
	while (--i >= 0 && str[i] == '*' && len > 0)
		len--;
	return (len);
}

/*
**	len:	0: len	 1: len_a	2: len_b
**	v:		0: i	 1: j
*/

int				manage_mid(char **str, char **b_star, char **a_star)
{
	char		*new;
	int			len[3];
	int			v[2];

	len[0] = ft_strlen_ab(*str, *b_star, *a_star);
	len[1] = (*a_star) ? ft_strlen(*a_star) : 0;
	len[2] = (*b_star) ? ft_strlen(*b_star) : 0;
	if (len[0])
	{
		new = ft_strnew(len[0]);
		v[0] = len[2];
		while ((*str)[v[0]] && (*str)[v[0]] == '*')
			v[0]++;
		v[1] = 0;
		while (v[0] < (int)(ft_strlen(*str) - len[1]))
			new[v[1]++] = (*str)[v[0]++];
		while (--v[1] >= 0 && new[v[1]] == '*')
			new[v[1]] = '\0';
		free(*str);
		*str = new;
		return (1);
	}
	(*a_star) ? free(*a_star) : 0;
	(*b_star) ? free(*b_star) : 0;
	return (0);
}

void			new_verify(char ***tab, char *str)
{
	char		**mid_arg;
	char		*cursor;
	int			i;
	int			j;

	i = -1;
	mid_arg = ft_strsplit(str, '*');
	while ((*tab)[++i])
	{
		j = -1;
		cursor = (*tab)[i];
		while (mid_arg[++j])
		{
			if (!ft_strcmp(cursor, "") ||
					!(cursor = ft_strstr(cursor, mid_arg[j])))
			{
				free((*tab)[i]);
				(*tab)[i] = ft_strnew(0);
				break ;
			}
		}
	}
	free_tabstr(&mid_arg);
}
