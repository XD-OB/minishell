/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <obelouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 01:54:45 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/19 09:30:33 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		usage_exec(void)
{
	ft_dprintf(2, "%{red}-obsh%{eoc}: %{CYAN}exec%{eoc}:");
	ft_dprintf(2, "	No Argument.\n");
	ft_dprintf(2, "usage: exec command\n");
	return (1);
}

int				ft_exec(t_minishell *ms)
{
	int			n;

	if (!ft_strcmp(ms->cmd, "exec"))
		return (usage_exec());
	if (!ft_strncmp(ms->cmd, "exec ", 5))
	{
		ms->cmd = ft_strsub(ms->cmd, 4, ft_strlen(ms->cmd) - 4);
		ft_trimstr(&ms->cmd);
		if (builtin_parent(ms))
			n = ms->last;
		else if (builtin_child(ms))
			n = ms->last;
		else
			n = exec_cmd(ms);
		free_ms(ms, ms->cmd);
		exit(n);
	}
	return (0);
}
