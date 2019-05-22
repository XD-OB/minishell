/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 02:15:05 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/22 05:22:31 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_exit(char *str)
{
	if (!ft_strcmp(str, "bye"))
		return (1);
	if (!ft_strcmp(str, "exit"))
		return (1);
	if (!ft_strncmp(str, "exit ", 5))
		return (1);
	return (0);
}

int			ft_isnumeric(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static void		usage_exit(char ***tab, char *msg, int type)
{
	if (type == 0)
		ft_printf("%{RED}-obsh%{eoc}: %{CYAN}exit%{eoc}: ");
	else if (type == 1)
		ft_printf("%{RED}-obsh%{eoc}: %{CYAN}exit%{eoc}: %s", (*tab)[1]);
	if (msg)
		ft_putstr(msg);
	ft_printf("usage: exit [value]\n");
	free_tabstr(tab);
}

void			ft_exit(t_minishell *ms)
{
	char	**tab;
	int		ret;

	if (!ft_strcmp(ms->cmd, "bye") || !ft_strcmp(ms->cmd, "exit"))
	{
		ft_printf("exit : 0\n");
		free_ms(ms, NULL);
		exit(0);
	}
	tab = ft_strsplit(ms->cmd, ' ');
	if (len_tab(tab) > 2)
		return (usage_exit(&tab, "Too many argument\n", 0));
	else if (!ft_isnumeric(tab[1]))
		return (usage_exit(&tab, ": is not a number\n", 1));
	free_ms(ms, NULL);
	ret = ft_atoi(tab[1]);
	free_tabstr(&tab);
	ft_printf("exit : %d\n", ret);
	exit(ret);
}
