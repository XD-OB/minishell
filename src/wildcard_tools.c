/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 07:19:46 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/20 07:21:25 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_allstar(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '*')
			return (0);
		i++;
	}
	return (1);
}

char		*first_w(char *str)
{
	char	*before;
	int		len;
	int		i;

	i = -1;
	len = 0;
	while (str[++i] && str[i] != '*')
		len++;
	before = ft_strnew(len);
	i = -1;
	while (++i < len)
		before[i] = str[i];
	return (before);
}

char		*last_w(char *str)
{
	char	*after;
	int		len_str;
	int		len;
	int		i;
	int		j;

	len = 0;
	len_str = ft_strlen(str);
	i = len_str;
	while (str[--i] && str[i] != '*')
		len++;
	after = ft_strnew(len);
	j = 0;
	i = len_str - len;
	while (j < len)
		after[j++] = str[i++];
	return (after);
}

void		join_tab_snull(char ***tab, char **str)
{
	char	*new;
	int		len;
	int		i;

	new = ft_strnew(0);
	len = len_tab(*tab);
	i = -1;
	while (++i < len)
		if (ft_strcmp((*tab)[i], ""))
		{
			ft_strcombin(&new, (*tab)[i]);
			if (i + 1 < len)
				ft_strcombin(&new, " ");
		}
	free_tabstr(tab);
	free(*str);
	if (!ft_strcmp(new, ""))
	{
		free(new);
		*str = NULL;
	}
	else
		*str = new;
}
