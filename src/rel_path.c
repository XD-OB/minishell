/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rel_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 01:02:53 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/17 19:05:16 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*home_path(char *envp[])
{
	char		*home;
	int			i;

	i = 0;
	home = NULL;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "HOME=", 5))
			home = ft_strdup(&envp[i][5]);
		i++;
	}
	if (!home)
		return (ft_strdup("/Users/user"));
	return (home);
}

/*
**	i:	0:i		1:j		2:k
*/

static void		remove_tilda(char **r_path, char *home)
{
	char		*a_path;
	int			len_rpath;
	int			len_home;
	int			i[3];

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
			while (i[1] < len_home)
				a_path[i[2]++] = home[i[1]++];
		}
		a_path[i[2]++] = (*r_path)[i[0]++];
	}
	free(*r_path);
	*r_path = a_path;
}

void			fix_path(char **envp, char ***tab)
{
	char		**new_tab;
	char		*home;

	home = home_path(envp);
	if (len_tab(*tab) == 1)
	{
		new_tab = (char**)malloc(sizeof(char*) * 3);
		new_tab[0] = ft_strdup((*tab)[0]);
		new_tab[1] = ft_strdup(home);
		new_tab[2] = NULL;
		free_tabstr(tab);
		*tab = new_tab;
	}
	if (ft_strchr((*tab)[1], '~') && !access(home, F_OK))
		remove_tilda(&(*tab)[1], home);
	free(home);
}

int				is_relative(char *path)
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

void			rel_to_abs(char **r_path)
{
	char		*dir;
	char		*tmp;

	dir = ft_strnew(500);
	getcwd(dir, 500);
	tmp = *r_path;
	*r_path = dir;
	free(tmp);
}
