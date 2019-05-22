/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <obelouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 07:33:09 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/22 22:55:57 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			builtin_parent(t_minishell *ms)
{
	if (is_exit(ms->cmd))
		ft_exit(ms);
	else if (!ft_strcmp(ms->cmd, "cd") ||
			!ft_strncmp(ms->cmd, "cd ", 3))
		ms->last = ft_cd(ms);
	else if (!ft_strcmp("obsh --version", ms->cmd))
		obsh_version();
	else if (!ft_strcmp(ms->cmd, "setenv") ||
			!ft_strncmp(ms->cmd, "setenv ", 7))
		ms->last = ft_setenv(ms);
	else if (!ft_strcmp(ms->cmd, "unsetenv") ||
			!ft_strncmp(ms->cmd, "unsetenv ", 8))
		ms->last = ft_unsetenv(ms);
	else
		return (0);
	return (1);
}

int			builtin_child(t_minishell *ms)
{
	if (!ft_strcmp(ms->cmd, "echo") ||
		!ft_strncmp(ms->cmd, "echo ", 5))
		ms->last = ft_echo(ms);
	else if (!ft_strcmp(ms->cmd, "env") ||
			!ft_strncmp(ms->cmd, "env ", 4))
		ms->last = ft_env(ms);
	else if (!ft_strcmp(ms->cmd, "printenv") ||
			!ft_strncmp(ms->cmd, "printenv ", 9))
		ms->last = ft_printenv(ms);
	else
		return (0);
	return (1);
}

int			cmd_lancher(t_minishell *ms)
{
	if (!ft_strcmp("false", ms->cmd) || ft_exec(ms))
		return (1);
	if (builtin_parent(ms))
		return (0);
	if ((ms->pid = create_process()) == -1)
		return (fork_error());
	if (ms->pid == 0)
	{
		signal(SIGINT, ms->old);
		exit((builtin_child(ms)) ? ms->last : exec_cmd(ms));
	}
	else
	{
		waitpid(ms->pid, &(ms->status), 0);
		if (ms->sig_bonus)
			gest_signal(ms);
		else
		{
			(WIFSIGNALED(ms->status)) ? ms->sig_int = 1 : 0;
			ms->last = exit_val(ms->status);
		}
	}
	return (0);
}
