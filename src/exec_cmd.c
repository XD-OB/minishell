/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <obelouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 07:02:03 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/20 06:40:21 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**get_paths(char **envp)
{
	char		**tab_path;
	char		*path;
	int			i;

	i = -1;
	path = ft_strnew(0);
	while (envp[++i])
		if (!ft_strncmp(envp[i], "PATH=", 5))
			ft_strcombin(&path, &(envp[i][5]));
	if (!path)
		path = ft_strdup(".");
	tab_path = ft_strsplit(path, ':');
	free(path);
	return (tab_path);
}

int				check_fx(char *str)
{
	struct stat		stats;

	if (stat(str, &stats) == -1)
		return (msg_usrerr(str, 0));
	if (!S_ISREG(stats.st_mode))
		return (msg_type(stats.st_mode, str));
	if (access(str, X_OK))
		return (msg_usrerr(str, 1));
	return (0);
}

int				cmd_user(char ***tab, char **envp, char **full_path)
{
	char		*cmd;

	cmd = (full_path) ? *full_path : (*tab)[0];
	if (check_fx(cmd))
	{
		free_tabstr(tab);
		return (1);
	}
	if (execve(cmd, *tab, envp) == -1)
	{
		ft_printf("%s: Execution error\n", cmd);
		free_tabstr(tab);
		return (1);
	}
	if (full_path)
		free(*full_path);
	free_tabstr(tab);
	return (0);
}

int				exec_cmd(t_minishell *ms)
{
	char		*full_path;
	char		**tab_path;
	char		**tab;
	int			i;

	tab = clean_cmds(ms->cmd, 1);
	if (!access(tab[0], F_OK))
		return (cmd_user(&tab, ms->envp, NULL));
	i = -1;
	tab_path = get_paths(ms->envp);
	while (tab_path[++i])
	{
		full_path = ft_strjoin(tab_path[i], "/");
		ft_strcombin(&full_path, tab[0]);
		if (!access(full_path, F_OK))
		{
			free_tabstr(&tab_path);
			return (cmd_user(&tab, ms->envp, &full_path));
		}
		free(full_path);
	}
	msg_cmd_nfound(tab[0]);
	free_tabstr(&tab_path);
	free_tabstr(&tab);
	return (127);
}
