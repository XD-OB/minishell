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

#include "../../minishell.h"

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

char		*rel_to_abs()
{
	int		type;
	char	*dir;

	dir = ft_strnew(500);
	getcwd(dir, 500);
	return (dir);
}

void	fix_path(int ac, char **tab, char **envp)
{
	char	*home;

	home = home_path(envp);
	if (ac == 1)
		tab[1] = ft_strdup(home);
	if (ft_strchr(tab[1], '~'))
		remove_tilda(&tab[1], home);
	free(home);
}

int			cd_minus(int ac, char **tab, char **envp, char **prev_cd)
{
	if (ac == 2 && !ft_strcmp(tab[1], "-"))
	{
		if (!*prev_cd)
		{
			ft_putstr_fd("obsh: cd: OLD PWD not set\n", 2);
			return (1);
		}
		free(tab[1]);
		tab[1] = ft_strdup(*prev_cd);
	}
	if (*prev_cd)
		free(*prev_cd);
	*prev_cd = ft_getpwd(envp);
	return (0);
}

int			main(int ac, char **av, char **envp)
{
	char	*tmp;

	if (ac > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	fix_path(ac, av, envp);
	//if (cd_minus(av, envp, prev_cd))
	//	return (1);
	if (chdir(av[1]) == -1)
	{
		ft_putstr_fd("yawraha mhawda\n", 2);
		return (1);
	}
	if (is_relative(av[1]))
	{
		tmp = rel_to_abs();
		ft_setpwd(envp, tmp);
		free(tmp);
		return (0);
	}
	ft_setpwd(envp, av[1]);
	return (0);
}
