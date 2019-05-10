/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 00:27:49 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/10 00:32:31 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*home_path(char *envp[])
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

void	rel_to_abs(char **r_path, char *home)
{
	char	*a_path;
	int		len_rpath;
	int		len_home;
	int		i;
	int		j;
	int		k;

	len_home = ft_strlen(home);
	len_rpath = ft_strlen(*r_path);
	a_path = ft_strnew(len_home + len_rpath - 1);
	k = 0;
	i = 0;
	while (i < len_rpath)
	{
		if ((*r_path)[i] == '~')
		{
			i++;
			j = 0;
			while(j < len_home)
				a_path[k++] = home[j++];
		}
		a_path[k++] = (*r_path)[i++];
	}
	free(*r_path);
	*r_path = a_path;
}

int		len_tab(char **tab)
{
	int		len;

	len = 0;
	while (tab[len])
		len++;
	return (len);
}

//char	*parent_path(char *dir)
//{
//}

void	ft_cd(char *cmd, char **envp)
{
	char	*home;
	char	**tab;
	//char	*parent;

	tab = ft_strsplit(cmd, ' ');
	//parent = parent_path(*curr_dir);
	home = home_path(envp);
	if (len_tab(tab) > 2)
	{
		ft_putstr("cd: too many arguments\n");
		exit(1);
	}
	if (len_tab(tab) == 1)
		tab[1] = home;
	if (ft_strchr(tab[1], '~'))
		rel_to_abs(&tab[1], home);
	if (chdir(tab[1]) == -1)
	{
		ft_putstr("yawraha mhawda\n");
		exit(1);
	}
	ft_setenv(envp, "PWD", tab[1]);
}
