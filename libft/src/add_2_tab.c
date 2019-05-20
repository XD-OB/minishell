/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_2_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 23:47:04 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/20 07:25:51 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		add_2_tab(char ***tab, char *elem)
{
	char	**new;
	int		len;
	int		i;

	len = len_tab(*tab);
	if (!(new = (char**)malloc(sizeof(char*) * (len + 2))))
		return ;
	new[len + 1] = NULL;
	i = -1;
	while (++i < len)
		new[i] = ft_strdup((*tab)[i]);
	new[len] = ft_strdup(elem);
	free_tabstr(tab);
	*tab = new;
}
