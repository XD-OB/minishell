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

void	remove_tilda(char **r_path, char *home)
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

int		len_tab(char **tab)
{
	int		len;

	len = 0;
	while (tab[len])
		len++;
	return (len);
}

void	fix_path(char **envp, char **tab)
{
	char	*home;

	home = home_path(envp);
	if (len_tab(tab) == 1)
		tab[1] = home;
	//if (is_relative(tab[1]))
	//	rel_to_abs(&tab[1]);
	if (ft_strchr(tab[1], '~'))
		remove_tilda(&tab[1], home);
	free(home);
}

void	ft_cd(char *cmd, char **envp)
{
	char	**tab;

	tab = ft_strsplit(cmd, ' ');
	if (len_tab(tab) > 2)
		msg_error("cd: too many arguments\n", 1);
	fix_path(envp, tab);
	if (chdir(tab[1]) == -1)
		msg_error("yawraha mhawda\n", 1);
	ft_setenv(envp, "PWD", tab[1]);
}
