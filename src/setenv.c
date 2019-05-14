/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 18:53:23 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/14 03:00:24 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	affect_chars(char **s1, char **s2, char *val1, char *val2)
{
	*s1 = ft_strdup(val1);
	*s2 = ft_strdup(val2);
}

static int	error_len(char **envp, int len_t)
{
	if (len_t > 3)
		return (2);
	if (len_t == 1)
	{
		show_env(envp);
		return (1);
	}
	return (0);
}

static int	set_var_value(char **envp, char *cmd, char **var, char **val)
{
	char	**tab;
	char	**tmp;
	int		len_t;
	int 	ret;

	tab = ft_strsplit(cmd, ' ');
	len_t = len_tab(tab);
	if ((ret = error_len(envp, len_t)))
		return (ret);
	if (len_t == 2)
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

static void	add_var_env(char **envp, char **new, char *var, char *value)
{
	if (!*new)
	{
		*new = ft_strjoin(var, "=");
		ft_strcombin(new, value);
		envp[0] = ft_strdup(*new);
		envp[1] = NULL;
	}
}

int			ft_setenv(char **envp, char *cmd)
{
	char	*new;
	char	*var;
	char	*value;
	int		len_var;
	int		i;

	new = NULL;
	if ((i = set_var_value(envp, cmd, &var, &value)))
	{
		if (i != 2)
			return (1);
		ft_dprintf(2, "setenv: Wrong number of arguments\n");
		ft_dprintf(2, "usage: setenv [variable[=value]]\n");
		return (1);
	}
	i = -1;
	len_var = ft_strlen(var);
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], var, len_var))
		{
			new = ft_strjoin(var, "=");
			ft_strcombin(&new, value);
			ft_strclr(envp[i]);
			ft_strcpy(envp[i], new);
			break ;
		}
	}
	add_var_env(&envp[i], &new, var, value);
	triple_free(&new, &var, &value);
	return (0);
}
