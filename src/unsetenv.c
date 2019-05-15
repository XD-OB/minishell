/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 22:33:11 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/15 02:43:27 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	indice_env(char **envp, char *var, int len_var)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, len_var))
			return (i);
		i++;
	}
	return (-5);
}

void		ft_swap_env(char **env1, char **env2)
{
	char	*tmp;

	tmp = ft_strdup(*env1);
	*env1 = ft_strdup(*env2);
	*env2 = tmp;
}

int			ft_unsetenv(char **envp, char *cmd, int *last)
{
	char	**tab;
	int		len_var;
	int		found;
	int		i;

	tab = ft_strsplit(cmd, ' ');
	if (len_tab(tab) != 2)
	{
		ft_dprintf(2, "unsetenv: too many arguments\n");
		ft_dprintf(2, "usage: unsetenv variable\n");
		return ((*last = 1));
	}
	len_var = ft_strlen(tab[1]);
	found = indice_env(envp, tab[1], len_var);
	if (found == -5)
		return ((*last = 1));
	i = found - 1;
	while (envp[++i + 1])
		ft_swap_env(&envp[i], &envp[i + 1]);
	envp[i] = NULL;
	return ((*last = 0));
}
