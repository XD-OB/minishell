/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <obelouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 18:53:23 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/19 08:23:24 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		error_len(char **envp, int len_t)
{
	if (len_t > 3)
		return (1);
	if (len_t == 1)
	{
		show_env(envp);
		return (1);
	}
	return (0);
}

static int		set_var_value(t_minishell *ms, char **var, char **val)
{
	char	**tab;
	char	**tmp;
	int		ret;

	tab = clean_cmds(ms->cmd, 1);
	if ((ret = error_len(ms->envp, len_tab(tab))))
	{
		free_tabstr(&tab);
		return (1);
	}
	if (len_tab(tab) == 2)
	{
		if (ft_strchr(tab[1], '='))
		{
			tmp = ft_strsplit(tab[1], '=');
			affect_chars(var, val, tmp[0], tmp[1]);
			free_tabstr(&tmp);
		}
		else
			affect_chars(var, val, tab[1], "");
	}
	else
		affect_chars(var, val, tab[1], tab[2]);
	free_tabstr(&tab);
	return (0);
}

static int		aff_before(int i)
{
	if (i == 2)
	{
		ft_dprintf(2, "setenv: Wrong number of arguments\n");
		ft_dprintf(2, "usage: setenv [variable[=value]]\n");
	}
	return (1);
}

static char		**modify_var(char **envp, char *var, char *value)
{
	char		**new_envp;
	char		*new;
	int			len_var;
	int			len;
	int			i;

	len = len_tab(envp);
	len_var = ft_strlen(var);
	new = ft_strjoin(var, value);
	new_envp = (char**)malloc(sizeof(char*) * (len + 1));
	new_envp[len] = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, len_var))
			new_envp[i] = ft_strdup(envp[i]);
		else
			new_envp[i] = new;
		i++;
	}
	return (new_envp);
}

int				ft_setenv(t_minishell *ms)
{
	char	**new_envp;
	char	*var;
	char	*value;
	int		i;

	if ((i = set_var_value(ms, &var, &value)))
		return (aff_before(i));
	ft_strcombin(&var, "=");
	if (!found_env(ms->envp, var))
	{
		ft_strcombin(&var, value);
		add_2_tab(&ms->envp, var);
	}
	else
	{
		new_envp = modify_var(ms->envp, var, value);
		free(ms->envp);
		ms->envp = new_envp;
	}
	free(value);
	free(var);
	return (0);
}
