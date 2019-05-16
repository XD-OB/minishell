/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_char2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 00:01:35 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/16 07:45:39 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**copy_char2(char **tab, int start)
{
	char	**new;
	int		len_t;
	int		len;
	int		i;
	int		j;

	len_t = len_tab(tab);
	len = len_t - start;
	if (!(new = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	new[len] = NULL;
	j = 0;
	i = start;
	while (i < len_t)
		new[j++] = ft_strdup(tab[i++]);
	return (new);
}
