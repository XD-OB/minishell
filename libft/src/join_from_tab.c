/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_from_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 23:58:22 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/15 00:00:34 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*join_from_tab(char **tab, int start, char *sep)
{
	char	*res;
	int		len;
	int		i;

	res = ft_strnew(0);
	len = len_tab(tab);
	if (start < 0)
		return (res);
	i = start;
	while (i < len)
	{
		ft_strcombin(&res, tab[i]);
		i++;
		if (i < len)
			ft_strcombin(&res, sep);
	}
	return (res);
}
