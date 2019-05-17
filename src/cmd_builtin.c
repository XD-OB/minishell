/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_buitin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 07:33:09 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/17 07:41:58 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			cmd_lancher(int ac, char **av, t_minishell *ms, char ***envp)
{
	if (cmd_builtin(envp, ms->cmd[ms->i], &(ms->last_ret)) == -1)
	{
		if ((ms->pid = create_process()) == -1)
		{
			ft_dprintf(2, "%{red}-obsh%{CYAN}fork%{eoc}: error\n");
			return (1);
		}
		if (ms->pid == 0)
		{
			signal(SIGINT, ms->old);
			exec_cmd(ms->cmd[ms->i], *envp);
		}
		else
		{
			waitpid(ms->pid, &(ms->status), 0);
			if (ac == 2 && !ft_strcmp(av[1], "--signals"))
				gest_signal(ms);
			else
			{
				(WIFSIGNALED(ms->status)) ? ms->sig_int = 1 : 0;
				ms->last_ret = exit_val(ms->status);
			}
		}
	}
	return (0);
}

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

int			cmd_builtin(char ***envp, char *cmd, int *last)
{
	char	**tab;

	if (!ft_strcmp(cmd, "exit") || !ft_strncmp(cmd, "exit ", 5))
		exit(ret_exit(cmd));
	if (!ft_strcmp(cmd, "echo") || !ft_strncmp(cmd, "echo ", 5))
	{
		tab = (well_quoted(cmd)) ? ft_split_quote(cmd) : ft_split_invquote(cmd);
		ft_echo(len_tab(tab), tab, *envp, last);
		free_tabstr(&tab);
	}
	else if (!ft_strcmp(cmd, "cd") || !ft_strncmp(cmd, "cd ", 3))
		ft_cd(envp, cmd, last);
	else if (!ft_strcmp(cmd, "setenv") || !ft_strncmp(cmd, "setenv ", 7))
		ft_setenv(envp, cmd, last);
	else if (!ft_strcmp(cmd, "unsetenv") || !ft_strncmp(cmd, "unsetenv ", 8))
		ft_unsetenv(envp, cmd, last);
	else if (!ft_strcmp(cmd, "env") || !ft_strncmp(cmd, "env ", 4))
		ft_env(*envp, cmd, last);
	else if (!ft_strcmp(cmd, "printenv") || !ft_strncmp(cmd, "printenv ", 9))
		ft_printenv(*envp, cmd, last);
	else if (cmd[0] == '$' && cmd[1])
		ft_dollarenv(*envp, cmd, last);
	else
		return (-1);
	return (1);
}
