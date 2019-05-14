/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 00:27:49 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/13 18:45:20 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setpwd(char **envp, char *value)
{
	char	*new;
	int		i;

	i = 0;
	new = NULL;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PWD=", 4))
		{
			new = ft_strjoin("PWD=", value);
			ft_strclr(envp[i]);
			ft_strcpy(envp[i], new);
			break ;
		}
		i++;
	}
	if (!new)
	{
		new = ft_strjoin("PWD=", value);
		ft_strclr(envp[i]);
		ft_strcpy(envp[i], new);
		envp[++i] = NULL;
	}
	free(new);
}

char		*ft_getpwd(char **envp)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PWD=", 4))
		{
			path = ft_strdup(&envp[i][4]);
			break ;
		}
		i++;
	}
	if (!path)
	{
		path = ft_strnew(500);
		getcwd(path, 500);
	}
	return(path);
}

static char	*home_path(char *envp[])
{
	char	*home;
	int		i;

	i = 0;
	home = NULL;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "HOME=", 5))
			home = ft_strdup(&envp[i][5]);
		i++;
	}
	if (!home)
		exit(1);
	return (home);
}

/*
 **	i[3]:	0:i		1:j		2:k
 */

static void	remove_tilda(char **r_path, char *home)
{
	char	*a_path;
	int		len_rpath;
	int		len_home;
	int		i[3];

	len_home = ft_strlen(home);
	len_rpath = ft_strlen(*r_path);
	a_path = ft_strnew(len_home + len_rpath - 1);
	i[0] = 0;
	i[2] = 0;
	while (i[0] < len_rpath)
	{
		if ((*r_path)[i[0]] == '~')
		{
			i[0]++;
			i[1] = 0;
			while(i[1] < len_home)
				a_path[i[2]++] = home[i[1]++];
		}
		a_path[i[2]++] = (*r_path)[i[0]++];
	}
	free(*r_path);
	*r_path = a_path;
}

int			is_relative(char *path)
{
	if (ft_strstr(path, "./"))
		return (1);
	if (ft_strstr(path, "../"))
		return (1);
	if (!ft_strcmp(path, "."))
		return (1);
	if (!ft_strcmp(path, ".."))
		return (1);
	return (0);
}

void		rel_to_abs(char **r_path)
{
	int		type;
	char	*dir;
	char	*tmp;

	dir = ft_strnew(500);
	getcwd(dir, 500);
	tmp = *r_path;
	*r_path = dir;
	free(tmp);
}

void	fix_path(char **envp, char **tab)
{
	char	*home;

	home = home_path(envp);
	if (len_tab(tab) == 1)
		tab[1] = ft_strdup(home);
	if (ft_strchr(tab[1], '~'))
		remove_tilda(&tab[1], home);
	free(home);
}

static char	*get_oldpwd(char **envp)
{
	int		i;

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

int			cd_minus(char **tab, char **envp)
{
	char	*oldpwd;

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

int			change_dir(char *path)
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

int			ft_cd(char *cmd, char **envp)
{
	char	**tab;

	tab = ft_strsplit(cmd, ' ');
	if (len_tab(tab) > 2)
	{
		ft_dprintf(2, "%{red}-obsh%{eoc}:");
		ft_dprintf(2, "%{CYAN} cd%{eoc}: ");
		ft_dprintf(2, "too many arguments\n");
		return (1);
	}
	fix_path(envp, tab);
	if (cd_minus(tab, envp))
		return (1);
	if (change_dir(tab[1]))
		return (1);
	if (is_relative(tab[1]))
		rel_to_abs(&tab[1]);
	ft_setpwd(envp, tab[1]);
	return (0);
}
