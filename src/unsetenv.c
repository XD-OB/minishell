/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 22:33:11 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/17 06:25:41 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**new_env(char **envp, char *var, int len_var)
{
	char	**new_envp;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = len_tab(envp);
	new_envp = (char**)malloc(sizeof(char*) * len);
	new_envp[len - 1] = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, len_var))
			new_envp[j++] = ft_strdup(envp[i]);
		i++;
	}
	return (new_envp);
}

int				ft_unsetenv(char ***envp, char *cmd, int *last)
{
	char	**new_envp;
	char	**tab;
	char	*var;

	tab = ft_strsplit(cmd, ' ');
	if (len_tab(tab) != 2)
	{
		ft_dprintf(2, "unsetenv: too many arguments\n");
		ft_dprintf(2, "usage: unsetenv variable\n");
		free_tabstr(&tab);
		return ((*last = 1));
	}
	var = ft_strjoin(tab[1], "=");
	if (!found_env(*envp, var))
	{
		free(var);
		free_tabstr(&tab);
		return ((*last = 0));
	}
	new_envp = new_env(*envp, var, ft_strlen(var));
	free(var);
	free_tabstr(&tab);
	free_tabstr(envp);
	*envp = new_envp;
	return ((*last = 0));
}
