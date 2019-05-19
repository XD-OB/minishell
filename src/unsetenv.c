/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 22:33:11 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/18 07:15:15 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**new_env(char **envp, char *var)
{
	char	**new_envp;
	int		len_var;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = len_tab(envp);
	len_var = ft_strlen(var);
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

static int		wrong_arg(char ***tab)
{
	if (len_tab(*tab) != 2)
	{
		ft_dprintf(2, "unsetenv: too many arguments\n");
		ft_dprintf(2, "usage: unsetenv variable\n");
		free_tabstr(tab);
		return (1);
	}
	return (0);
}

int				ft_unsetenv(t_minishell *ms)
{
	char		**new_envp;
	char		**tab;
	char		*var;

	tab = clean_cmds(ms->cmd);
	if (wrong_arg(&tab))
		return (1);
	var = ft_strjoin(tab[1], "=");
	if (!found_env(ms->envp, var))
	{
		free(var);
		free_tabstr(&tab);
		return (0);
	}
	new_envp = new_env(ms->envp, var);
	free(var);
	free_tabstr(&tab);
	free_tabstr(&ms->envp);
	ms->envp = new_envp;
	return (0);
}
