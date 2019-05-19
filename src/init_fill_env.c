/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fill_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <obelouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 07:07:29 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/19 08:22:44 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fill_opts(t_env *env, char c)
{
	if (!c || c == 'i')
		env->i = 1;
	else if (c == 'u')
		env->u = 1;
	else if (c == '0')
		env->null = 1;
	else
	{
		ft_dprintf(2, "env: illegal option -- %c\n", c);
		usage_env(NULL);
		return (1);
	}
	return (0);
}

static int	fill_longopts(t_env *env, char *str)
{
	if (!ft_strcmp(str, "ignore-environment"))
		env->i = 1;
	else if (!ft_strcmp(str, "unset"))
		env->u = 1;
	else if (!ft_strcmp(str, "null-separator"))
		env->null = 1;
	else
	{
		ft_dprintf(2, "env: illegal option -- %s\n", str);
		usage_env(NULL);
		return (1);
	}
	return (0);
}

static int	opts_env(t_env *env, char ***tab, int i)
{
	int		j;

	j = 0;
	while ((*tab)[i][++j])
	{
		if ((*tab)[i][j] == '-')
		{
			if (fill_longopts(env, &((*tab)[i][++j])))
			{
				free_tabstr(tab);
				return (0);
			}
			return (2);
		}
		else
		{
			if (fill_opts(env, (*tab)[i][j]))
			{
				free_tabstr(tab);
				return (0);
			}
		}
	}
	return (1);
}

static void	affect_egal(t_env *env, char ***tab, int *i)
{
	env->start_var = *i - 1;
	if (env->u)
		(*i)++;
	while ((*tab)[*i] && ft_strchr((*tab)[*i], '='))
		(*i)++;
	env->start_cmd = *i - 1;
	env->tab = copy_char2(*tab, 1);
	free_tabstr(tab);
}

int			fill_env(t_env *env, char *cmd)
{
	char	**tab;
	int		fail;
	int		i;
	int		k;

	init_env(env);
	if ((fail = fail_qtest(cmd)))
		return (0);
	tab = clean_cmds(cmd, 1);
	i = 0;
	while (tab[++i] && tab[i][0] == '-')
	{
		k = opts_env(env, &tab, i);
		if (k == 2)
			continue ;
		if (k == 0 || fail)
		{
			free_tabstr(&tab);
			return (0);
		}
	}
	affect_egal(env, &tab, &i);
	return (1);
}
