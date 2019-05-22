/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dicstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 07:28:05 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/22 09:13:02 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				len_dicstr(t_dicstr *tab)
{
	int			len;

	len = 0;
	while (tab[len].var)
		len++;
	return (len);
}

void			free_dicstr(t_dicstr **tab)
{
	int			i;

	i = 0;
	while ((*tab)[i].var)
	{
		free((*tab)[i].var);
		free((*tab)[i].value);
		i++;
	}
	free(*tab);
}

void			add_2_dicstr(t_dicstr **tab, char *var, char *value)
{
	t_dicstr	*new;
	int			len;
	int			i;

	if (!*tab)
		len = 0;
	else
		len = len_dicstr(*tab);
	new = (t_dicstr*)malloc(sizeof(t_dicstr) * (len + 2));
	new[len + 1].value = NULL;
	new[len + 1].var = NULL;
	i = 0;
	while (i < len)
	{
		new[i].var = ft_strdup((*tab)[i].var);
		new[i].value = ft_strdup((*tab)[i].value);
		i++;
	}
	new[len].var = ft_strdup(var);
	new[len].value = ft_strdup(value);
	if (*tab)
		free_dicstr(tab);
	*tab = new;

	int j = -1;
		ft_putstr("----------------------------\n");
		while ((*tab)[++j].var)
		{
			ft_printf("var   %d: %s\n", j, (*tab)[j].var);
			ft_printf("value %d: %s\n", j, (*tab)[j].value);
		}
		ft_putstr("----------------------------\n");

}

t_dicstr		*copy_2_dicstr(t_dicstr *tab)
{
	t_dicstr	*new;
	int			len;
	int			i;

	len = len_dicstr(tab);
	new = (t_dicstr*)malloc(sizeof(t_dicstr) * (len + 1));
	new[len].value = NULL;
	new[len].var = NULL;
	i = 0;
	while (i < len)
	{
		new[i].var = ft_strdup(tab[i].var);
		new[i].value = ft_strdup(tab[i].value);
		i++;
	}
	return (new);
}
