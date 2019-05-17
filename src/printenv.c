/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 18:49:55 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/17 07:26:53 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			usage_printenv(int *last, char *str)
{
	*last = 2;
	ft_dprintf(2, "printenv: illegal option -- %s\n", str);
	ft_dprintf(2, "usage: printenv [-option] [variable]\n");
	ft_dprintf(2, "       option: 	-0  --null\n");
	return (2);
}

static void			search_env(char **envp, t_printenv *pv)
{
	char			*var;
	int				i;

	i = -1;
	pv->found = 0;
	var = ft_strjoin(pv->tab[pv->j], "=");
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], var, ft_strlen(var)))
		{
			if (!pv->null)
				ft_putendl(&envp[i][ft_strlen(var)]);
			else
				ft_putstr(&envp[i][ft_strlen(var)]);
			pv->found = 1;
		}
	}
	free(var);
	if (!pv->found)
		pv->ret = 1;
	pv->j++;
}

int					ft_printenv(char **envp, char *cmd, int *last)
{
	t_printenv		pv;

	pv.ret = 0;
	pv.tab = ft_strsplit(cmd, ' ');
	(!pv.tab[1]) ? show_env(envp) : 0;
	if (pv.tab[1])
	{
		pv.j = 0;
		while (pv.tab[++pv.j][0] == '-')
		{
			if (!ft_strcmp(&pv.tab[pv.j][1], "0") ||
				!ft_strcmp(&pv.tab[pv.j][1], "-null"))
				pv.null = 1;
			else
			{
				pv.ret = usage_printenv(last, &pv.tab[pv.j][1]);
				free_tabstr(&pv.tab);
				return ((*last = pv.ret));
			}
		}
		while (pv.tab[pv.j])
			search_env(envp, &pv);
	}
	free_tabstr(&pv.tab);
	return ((*last = pv.ret));
}
