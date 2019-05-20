/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <obelouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 08:04:57 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/20 22:13:49 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			tab_well_quoted(char **tab)
{
	int		d_quote;
	int		s_quote;
	int		i;
	int		j;

	i = -1;
	while (tab[++i])
	{
		j = -1;
		s_quote = 0;
		d_quote = 0;
		while (tab[i][++j])
		{
			(tab[i][j] == 34) ? d_quote++ : 0;
			(tab[i][j] == 39) ? s_quote++ : 0;
		}
		if (!(d_quote % 2) && !(s_quote % 2))
			return (1);
	}
	return (0);
}

int			well_quoted(char *str)
{
	int		d_quote;
	int		s_quote;
	int		i;

	i = 0;
	d_quote = 0;
	s_quote = 0;
	while (str[i])
	{
		if (str[i] == 34)
			d_quote++;
		if (str[i] == 39)
			s_quote++;
		i++;
	}
	if (!(s_quote % 2) && !(d_quote % 2))
		return (1);
	return (0);
}

int			found_env(char **envp, char *var)
{
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(var);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, len))
			return (1);
		i++;
	}
	return (0);
}
