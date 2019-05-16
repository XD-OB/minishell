/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 07:02:03 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/16 07:06:47 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char			**get_paths(char **envp)
{
	char			**tab_path;
	char			*path;
	int				i;

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

static int			test_x_ok(char **full_path, char ***tab, char **envp)
{
	if (!access(*full_path, X_OK))
	{
		if (execve(*full_path, *tab, envp) != -1)
		{
			free(*full_path);
			free_tabstr(tab);
			return (0);
		}
	}
	ft_dprintf(2, "%{red}-obsh%{eoc}: ");
	ft_dprintf(2, "%{CYAN}%s%{eoc}: ", (*tab)[0]);
	ft_dprintf(2, "Permission denied\n");
	free(*full_path);
	free_tabstr(tab);
	return (1);
}

static void			msg_cmd_nfound(char *str)
{
	ft_dprintf(2, "%{red}-obsh%{eoc}: ");
	ft_dprintf(2, "%{CYAN}%s%{eoc}", str);
	ft_dprintf(2, ": commande not found\n");
}

int					exec_cmd(char *cmd, char **envp)
{
	char			*full_path;
	char			**tab_path;
	char			**tab;
	int				i;

	tab = ft_strsplit(cmd, ' ');
	if ((i = cmd_user(tab, envp)))
	{
		free_tabstr(&tab);
		exit(i);
	}
	tab_path = get_paths(envp);
	i = -1;
	while (tab_path[++i])
	{
		full_path = ft_strjoin(tab_path[i], "/");
		ft_strcombin(&full_path, tab[0]);
		if (!access(full_path, F_OK))
			return (test_x_ok(&full_path, &tab, envp));
		free(full_path);
	}
	msg_cmd_nfound(tab[0]);
	free_tabstr(&tab_path);
	free_tabstr(&tab);
	exit(1);
}
