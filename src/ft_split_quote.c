/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <obelouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 20:45:42 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/19 20:25:39 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	v:	0: i	1: j	2: n	3: s_quote	  4: d_quote
*/

static void		init_v(int *v)
{
	v[1] = 0;
	v[2] = 0;
	v[0] = -1;
	v[3] = 0;
	v[4] = 0;
}

static	int		ft_count_w(const char *str)
{
	int		v[5];

	init_v(v);
	while (str[++v[0]] != '\0')
	{
		if (str[v[0]] == 34 && !v[4])
			v[4] = 1;
		else if (str[v[0]] == 39 && !v[3])
			v[3] = 1;
		else if (str[v[0]] == 34 && v[4])
			v[4] = 0;
		else if (str[v[0]] == 39 && v[3])
			v[3] = 0;
		if ((str[v[0]] == ' ' || str[v[0]] == '\t') && !v[4] && !v[3] && v[1])
			v[1] = 0;
		if (str[v[0]] != ' ' && str[v[0]] != '\t' && !v[4] && !v[3] && !v[1])
		{
			v[2]++;
			v[1] = 1;
		}
	}
	if (v[3] || v[4])
		return (-10);
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
	while (str[i] != ' ' && str[i] != '\t' && str[i])
		i++;
	return (i - ind);
}

static	int		ft_position(const char *str, int *pt)
{
	if (str[*pt] == 39)
	{
		(*pt)++;
		while (str[*pt] && str[*pt] != 39)
			(*pt)++;
		return (0);
	}
	if (str[*pt] == 34)
	{
		(*pt)++;
		while (str[*pt] && str[*pt] != 34)
			(*pt)++;
		return (0);
	}
	while (str[*pt])
	{
		if (str[*pt] != ' ' && str[*pt] != '\t')
			break ;
		(*pt)++;
	}
	return (0);
}

char			**ft_split_quote(char *str)
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
