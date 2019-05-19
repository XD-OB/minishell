/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_invquote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <obelouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 20:45:42 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/19 08:22:49 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int		ft_not_blank(char ch)
{
	if (ch == ' ')
		return (0);
	return (1);
}

/*
**	v:	0: i	1: j	2: n	qt: quote
*/

static	int		ft_count_w(const char *str)
{
	int		qt;
	int		v[3];

	v[1] = 0;
	v[2] = 0;
	qt = 0;
	v[0] = -1;
	while (str[++v[0]] != '\0')
	{
		if ((str[v[0]] == 34 || str[v[0]] == 39) && !qt)
			qt = 1;
		if ((str[v[0]] == 34 || str[v[0]] == 39) && qt)
			qt = 0;
		if (ft_not_blank(str[v[0]]) == 0 && !qt)
			if (v[1] == 1)
				v[1] = 0;
		if (ft_not_blank(str[v[0]]) == 1 && !qt)
			if (v[1] == 0)
			{
				v[2]++;
				v[1] = 1;
			}
	}
	return (v[2]);
}

static	int		ft_size_w(const char *str, int ind)
{
	int		i;

	i = ind;
	if (str[i] == 34)
	{
		i++;
		while (str[i] && str[i] != 34)
			i++;
		return (i + 1 - ind);
	}
	if (str[i] == 39)
	{
		i++;
		while (str[i] && str[i] != 39)
			i++;
		return (i + 1 - ind);
	}
	while (ft_not_blank(str[i]) == 1 && str[i])
		i++;
	return (i - ind);
}

static	int		ft_position(const char *str, int *pt)
{
	if (str[*pt] == 34 || str[*pt] == 39)
	{
		(*pt)++;
		while (str[*pt] && str[*pt] != 34 && str[*pt] != 39)
			(*pt)++;
		return (0);
	}
	while (str[*pt])
	{
		if (ft_not_blank(str[*pt]) == 1)
			break ;
		(*pt)++;
	}
	return (0);
}

char			**ft_split_invquote(char *str)
{
	int		t[3];
	int		pt[1];
	char	**table;

	if (str == NULL)
		return (NULL);
	t[0] = 0;
	*pt = 0;
	table = (char**)malloc((ft_count_w(str) + 1) * sizeof(char*));
	if (table)
	{
		while (t[0] < ft_count_w(str))
		{
			t[1] = 0;
			ft_position(str, pt);
			t[2] = ft_size_w(str, *pt);
			table[t[0]] = (char*)malloc((t[2] + 1) * sizeof(char));
			while (t[1] < t[2])
				table[t[0]][t[1]++] = str[(*pt)++];
			table[t[0]][t[1]] = '\0';
			t[0]++;
		}
		table[t[0]] = 0;
	}
	return (table);
}
