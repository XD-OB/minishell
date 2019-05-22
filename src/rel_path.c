/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rel_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <obelouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 01:02:53 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/22 22:41:03 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*home_path(char **envp)
{
	char		*home;
	int			i;

	i = 0;
	home = NULL;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "HOME=", 5))
		{
			home = ft_strdup(&envp[i][5]);
			break ;
		}
		i++;
	}
	return (home);
}

char			*user_name(char **envp)
{
	char		*user;
	int			i;

	i = 0;
	user = NULL;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "USER=", 5))
		{
			user = ft_strdup(&envp[i][5]);
			break ;
		}
		i++;
	}
	return (user);
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
