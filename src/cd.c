/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 00:27:49 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/17 00:56:36 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*get_oldpwd(char **envp)
{
	int			i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "OLDPWD=", 7))
		{
			if (envp[i][7] == '\0')
				return (NULL);
			return (ft_strdup(&envp[i][7]));
		}
		i++;
	}
	return (NULL);
}

int				cd_minus(char **tab, char **envp)
{
	char		*oldpwd;

	oldpwd = get_oldpwd(envp);
	if (len_tab(tab) == 2 && !ft_strcmp(tab[1], "-"))
	{
		if (!oldpwd)
		{
			ft_putstr_fd("obsh: cd: OLD PWD not set\n", 2);
			return (1);
		}
		free(tab[1]);
		tab[1] = ft_strdup(oldpwd);
	}
	if (oldpwd)
		free(oldpwd);
	oldpwd = ft_getpwd(envp);
	set_oldpath(&envp, oldpwd);
	free(oldpwd);
	return (0);
}

int				change_dir(char *path)
{
	if (chdir(path) == -1)
	{
		ft_dprintf(2, "%{red}-obsh%{eoc}:");
		ft_dprintf(2, "%{CYAN} cd%{eoc}: ");
		ft_dprintf(2, "%{CYAN}%s%{eoc}: ", path);
		if (access(path, F_OK))
			ft_dprintf(2, "No such file or directory\n");
		else if (access(path, X_OK))
			ft_dprintf(2, "Permission denied\n");
		else
			ft_dprintf(2, "Unknown error\n");
		return (1);
	}
	return (0);
}

void			isnt_complete(char **str)
{
	char		*new;
	int			len;
	int			i;

	len = ft_strlen(*str) + 2;
	new = (char*)malloc(sizeof(char) * (len + 1));
	new[len] = '\0';
	new[0] = '.';
	new[1] = '/';
	i = 0;
	while ((*str)[i])
	{
		new[i + 2] = (*str)[i];
		i++;
	}
	free(*str);
	*str = new;
}

int				ft_cd(char *cmd, char **envp, int *last)
{
	char		**tab;

	tab = ft_strsplit(cmd, ' ');
	if (len_tab(tab) > 2)
	{
		ft_dprintf(2, "%{red}-obsh%{eoc}:");
		ft_dprintf(2, "%{CYAN} cd%{eoc}: ");
		ft_dprintf(2, "too many arguments\n");
		return ((*last = 1));
	}
	fix_path(envp, tab);
	if (cd_minus(tab, envp))
		return ((*last = 1));
	if (change_dir(tab[1]))
		return ((*last = 1));
	if (!ft_strchr(tab[1], '/'))
		isnt_complete(&tab[1]);
	if (is_relative(tab[1]))
		rel_to_abs(&tab[1]);
	ft_setpwd(envp, tab[1]);
	return ((*last = 0));
}
