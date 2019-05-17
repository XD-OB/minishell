/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_2_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 07:35:34 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/17 07:36:15 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			**copy_2_char(char **envp)
{
	char		**tab;
	int			len;
	int			i;

	i = 0;
	len = len_tab(envp);
	tab = (char**)malloc(sizeof(char*) * (len + 1));
	tab[len] = NULL;
	while (envp[i])
	{
		tab[i] = ft_strdup(envp[i]);
		i++;
	}
	return (tab);
}
