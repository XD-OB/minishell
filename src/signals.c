/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 22:12:22 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/22 02:14:03 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		handler_sigint(int sig)
{
	char	*user;
	char	*home;
	char	*pwd;

	if (sig == SIGINT)
	{
		pwd = ft_strnew(500);
		getcwd(pwd, 500);
		home = ft_strdup(getenv("HOME"));
		if (ft_strstr(pwd, home))
			to_relative(&pwd, home);
		if (getenv("USER"))
			user = ft_strdup(getenv("USER"));
		else
			user = ft_strdup("user");
		ft_putchar('\n');
		ft_printf("%{red}[%{GREEN}%s%{RED}:%{eoc}", user);
		ft_printf("%{cyan} %s%{red}]%{RED}$%{eoc} ", pwd);
		free(home);
		free(user);
		free(pwd);
	}
}

void		gest_signal(t_minishell *ms)
{
	if (WIFEXITED(ms->status))
	{
		ms->last = WEXITSTATUS(ms->status);
		ft_dprintf(2, "Terminated Normaly: ");
		ft_dprintf(2, "%d\n", WEXITSTATUS(ms->status));
	}
	else
	{
		if (WIFSIGNALED(ms->status))
		{
			ms->last = WTERMSIG(ms->status);
			ft_dprintf(2, "Killed by The Signal: ");
			ft_dprintf(2, "%d\n", WTERMSIG(ms->status));
		}
		else if (WIFSTOPPED(ms->status))
		{
			ms->last = WSTOPSIG(ms->status);
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
	return (1);
}
