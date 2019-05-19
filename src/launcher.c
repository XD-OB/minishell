/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_buitin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 07:33:09 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/19 00:27:44 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ret_exit(char *str)
{
	char	**tab;
	int		ret;

	tab = ft_strsplit(str, ' ');
	if (tab[1])
		ret = ft_atoi(tab[1]);
	else
		ret = 0;
	free_tabstr(&tab);
	return (ret);
}

int			builtin_parent(t_minishell *ms)
{
	int		ret;

	if (!ft_strcmp(ms->cmd, "bye"))
	{
		free_ms(ms, NULL);
		exit(0);
	}
	if (!ft_strcmp(ms->cmd, "exit") ||
		!ft_strncmp(ms->cmd, "exit ", 5))
	{
		ret = ret_exit(ms->cmd);
		free_ms(ms, NULL);
		exit(ret);
	}
	if (!ft_strcmp(ms->cmd, "cd") || !ft_strncmp(ms->cmd, "cd ", 3))
		ms->last = ft_cd(ms);
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
	char	**tab;

	if (!ft_strcmp(ms->cmd, "echo") ||
		!ft_strncmp(ms->cmd, "echo ", 5))
	{
		tab = (well_quoted(ms->cmd)) ? ft_split_quote(ms->cmd)
									: ft_split_invquote(ms->cmd);
		ms->last = ft_echo(tab, ms);
		free_tabstr(&tab);
	}
	else if (!ft_strcmp(ms->cmd, "env") ||
			!ft_strncmp(ms->cmd, "env ", 4))
		ms->last = ft_env(ms);
	else if (!ft_strcmp(ms->cmd, "printenv") ||
			!ft_strncmp(ms->cmd, "printenv ", 9))
		ms->last = ft_printenv(ms);
	else if (ms->cmd[0] == '$' && ms->cmd[1])
		ms->last = ft_dollarenv(ms);
	else
		return (0);
	return (1);
}

int			cmd_lancher(t_minishell *ms)
{
	if (builtin_parent(ms))
		return (0);
	if ((ms->pid = create_process()) == -1)
		return (fork_error());
	if (ms->pid == 0)
	{
		signal(SIGINT, ms->old);
		if (builtin_child(ms))
			exit(ms->last);
		else
			exit(exec_cmd(ms));
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
