/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 06:03:43 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/18 23:28:47 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		set_oldpath(char ***envp, char *val)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_strjoin("OLDPWD=", val);
	while ((*envp)[i] && ft_strncmp((*envp)[i], "OLDPWD=", 7))
		i++;
	if (!(*envp)[i])
		add_2_tab(envp, new);
	else
	{
		free((*envp)[i]);
		(*envp)[i] = new;
	}
}

void		ft_setpwd(char ***envp, char *value)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_strjoin("PWD=", value);
	if (found_env(*envp, "PWD"))
	{
		while ((*envp)[i])
		{
			if (!ft_strncmp((*envp)[i], "PWD=", 4))
			{
				free((*envp)[i]);
				(*envp)[i] = new;
				return ;
			}
			i++;
		}
	}
	add_2_tab(envp, new);
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
	return (path);
}
