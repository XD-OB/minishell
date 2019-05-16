/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdsplit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 20:45:42 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/16 01:52:44 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int		ft_not_c(char ch)
{
	if (ch == ';')
		return (0);
	if (ch == '&')
		return (0);
	return (1);
}

static	int		ft_count_w(const char *str)
{
	int		i;
	int		j;
	int		n;

	i = 0;
	j = 0;
	n = 0;
	while (str[i])
	{
		if (ft_not_c(str[i]) == 0)
			if (j == 1)
				j = 0;
		if (ft_not_c(str[i]) == 1)
			if (j == 0)
			{
				if (str[i + 1] && str[i + 1] != '&')
					n++;
				j = 1;
			}
		i++;
	}
	return (n);
}

static	int		ft_size_w(const char *str, int ind)
{
	int		i;

	i = ind;
	while (str[i] && ft_not_c(str[i]) == 1)
		i++;
	while (str[i - 1] == ' ')
		i--;
	return (i - ind);
}

static	int		ft_position(const char *str, int *pt)
{
	while (str[*pt])
	{
		if (ft_not_c(str[*pt]) == 1 && str[*pt] != ' ')
			break ;
		(*pt)++;
	}
	return (0);
}

char			**cmdsplit(char const *str)
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
