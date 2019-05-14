/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 22:12:22 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/14 22:24:56 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		gest_signal(t_minishell *ms, int ac, char **av)
{
	if (WIFEXITED(ms->status))
	{
		ms->last_ret = WEXITSTATUS(ms->status);
		ft_dprintf(2, "Terminated Normaly: ");
		ft_dprintf(2, "%d\n", WEXITSTATUS(ms->status));
	}
	else
	{
		if (WIFSIGNALED(ms->status))
		{
			ms->last_ret = WTERMSIG(ms->status);
			ft_dprintf(2, "Killed by The Signal: ");
			ft_dprintf(2, "%d\n", WTERMSIG(ms->status));
		}
		else if (WIFSTOPPED(ms->status))
		{
			ms->last_ret = WSTOPSIG(ms->status);
			ft_dprintf(2, "Stoped by The Signal: ");
			ft_dprintf(2, "%d\n", WSTOPSIG(ms->status));
		}
	}
}

int			exit_val(int stats)
{
	if (WIFEXITED(stats))
		return (WEXITSTATUS(stats));
	if (WIFSIGNALED(stats))
		return (WTERMSIG(stats));
	if (WIFSTOPPED(stats))
		return (WSTOPSIG(stats));
	return(1);
}
