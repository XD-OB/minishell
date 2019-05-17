/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 07:02:03 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/17 20:30:22 by obelouch         ###   ########.fr       */
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

static void		msg_cmd_nfound(char *str)
{
	ft_dprintf(2, "%{red}-obsh%{eoc}: ");
	ft_dprintf(2, "%{CYAN}%s%{eoc}", str);
	ft_dprintf(2, ": command not found\n");
}

int				exec_cmd(char *cmd, char **envp)
{
	char		*full_path;
	char		**tab_path;
	char		**tab;
	int			i;

	tab = ft_strsplit(cmd, ' ');
	if (!access(tab[0], F_OK))
		return (cmd_user(&tab, envp, NULL));
	i = -1;
	tab_path = get_paths(envp);
	while (tab_path[++i])
	{
		full_path = ft_strjoin(tab_path[i], "/");
		ft_strcombin(&full_path, tab[0]);
		if (!access(full_path, F_OK))
		{
			free_tabstr(&tab_path);
			return (cmd_user(&tab, envp, &full_path));
		}
		free(full_path);
	}
	msg_cmd_nfound(tab[0]);
	free_tabstr(&tab_path);
	free_tabstr(&tab);
	return (1);
}
