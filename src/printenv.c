/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 18:49:55 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/18 20:48:07 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			usage_printenv(char *str)
{
	ft_dprintf(2, "printenv: illegal option -- %s\n", str);
	ft_dprintf(2, "usage: printenv [-option] [variable]\n");
	ft_dprintf(2, "       option: 	-0  --null\n");
}

static int			search_env(char **envp, t_printenv *pv, char *var)
{
	char			*new;
	int				p_detail;
	int				i;

	i = -1;
	new = ft_strjoin(var, "=");
	p_detail = (len_tab(pv->tab) > 2) ? 1 : 0;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], new, ft_strlen(new)))
		{
			if (p_detail)
				ft_printf("* %{CYAN}%s%{eoc}:\n", var);
			if (!pv->null)
				ft_putendl(&envp[i][ft_strlen(new)]);
			else
				ft_putstr(&envp[i][ft_strlen(new)]);
			return (0);
		}
	}
	free(new);
	return (1);
}

static int			init_pv(t_printenv *pv, t_minishell *ms)
{
	pv->ret = 0;
	pv->null = 0;
	pv->tab = clean_cmds(ms->cmd);
	if (len_tab(pv->tab) == 1)
	{
		show_env(ms->envp);
		free_tabstr(&pv->tab);
		return (0);
	}
	return (1);
}

int					ft_printenv(t_minishell *ms)
{
	t_printenv		pv;
	int				i;

	if (!init_pv(&pv, ms))
		return (0);
	i = 0;
	while (pv.tab[++i][0] == '-')
	{
		if (!ft_strcmp(&pv.tab[i][1], "0") ||
			!ft_strcmp(&pv.tab[i][1], "-null"))
			pv.null = 1;
		else
		{
			usage_printenv(&pv.tab[i][1]);
			free_tabstr(&pv.tab);
			return (1);
		}
	}
	while (pv.tab[i])
		pv.ret = ft_max(search_env(ms->envp, &pv, pv.tab[i++]), pv.ret);
	free_tabstr(&pv.tab);
	return (pv.ret);
}
