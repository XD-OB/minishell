/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 22:12:22 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/17 07:39:42 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		handler_sigint(int sig)
{
	char	*user;
	char	*pwd;

	if (sig == SIGINT)
	{
		pwd = getenv("PWD");
		if (!pwd)
		{
			pwd = ft_strnew(500);
			getcwd(pwd, 500);
		}
		else
			pwd = ft_strdup(pwd);
		to_relative(&pwd, getenv("HOME"));
		user = getenv("USER");
		user = ft_strdup((!user) ? "user" : user);
		ft_putchar('\n');
		ft_printf("%{red}[%{GREEN}%s%{eoc}", user);
		ft_printf("%{RED}:%{cyan} %s%{red}]%{eoc}", pwd);
		ft_printf("%{RED}$%{eoc} ");
		free(user);
		free(pwd);
	}
}

void		gest_signal(t_minishell *ms)
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
	return (1);
}
