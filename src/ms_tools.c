/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 23:43:28 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/20 06:29:00 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		fill_new_ms(t_minishell *new_ms, t_minishell ms)
{
	new_ms->old = ms.old;
	new_ms->last = ms.last;
	new_ms->tab_cmd = NULL;
	new_ms->cmd = NULL;
}

void		init_minishell(t_minishell *ms, char **envp, int ac,
						char **av)
{
	if (ac == 2 && !ft_strcmp(av[1], "--signals"))
		ms->sig_bonus = 1;
	else
		ms->sig_bonus = 0;
	ms->old = signal(SIGINT, handler_sigint);
	ms->envp = copy_2_char(envp);
	ms->tab_cmd = NULL;
	ms->cmd = NULL;
	ms->status = 0;
	ms->last = 0;
	ms->sig_int = 0;
}

void		free_mscmd(t_minishell *ms)
{
	if (ms->cmd_freable == 0)
		return ;
	free(ms->cmd);
	ms->cmd_freable = 0;
}

int			free_ms(t_minishell *ms, char *cmd)
{
	if (cmd)
	{
		free(cmd);
		cmd = NULL;
	}
	if (ms->tab_cmd)
	{
		free_tabstr(&(ms->tab_cmd));
		ms->tab_cmd = NULL;
	}
	if (ms->cmd_freable)
	{
		free(ms->cmd);
		cmd = NULL;
	}
	free_tabstr(&(ms->envp));
	ms->envp = NULL;
	return (1);
}
