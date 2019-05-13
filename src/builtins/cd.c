/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 00:27:49 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/13 18:45:55 by obelouch         ###   ########.fr       */
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
	}
	free(new);
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

void	fix_path(int ac, char **av, char **envp)
{
	char	*home;

	home = home_path(envp);
	if (ac == 1)
		av[1] = ft_strdup(home);
	if (ft_strchr(av[1], '~'))
		remove_tilda(&av[1], home);
	free(home);
}

int		main(int ac, char **av, char **envp)
{
		int		i;

	if (ac > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	fix_path(ac, av, envp);
	if (chdir(av[1]) == -1)
	{
		ft_putstr_fd("yawraha mhawda\n", 2);
		return(1);
	}
	if (is_relative(av[1]))
		rel_to_abs(&av[1]);
	ft_setpwd(envp, av[1]);
		i = -1;
		while (envp[++i])
			ft_putendl(envp[i]);
		ft_putstr("\n");
	return(0);
}
