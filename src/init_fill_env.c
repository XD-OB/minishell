#include "minishell.h"

static void	init_env(t_env *env)
{
	env->i = 0;
	env->u = 0;
	env->null = 0;
	env->start_var = 0;
	env->start_cmd = 0;
	env->tab = NULL;
}

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
		ft_printf("env: illegal option -- %c\n", c);
		ft_printf("usage: env [-i0] [-u name]");
		ft_printf("[name=value ...] [utility [argument ...]]\n");
		return (1);
	}
	return (0);
}

static int	fill_longopts(t_env *env, char *str)
{
	if (!str[0] || !ft_strcmp(str, "ignore-environment"))
		env->i = 1;
	else if (!ft_strcmp(str, "unset"))
		env->u = 1;
	else if (!ft_strcmp(str, "null-separator"))
		env->null = 1;
	else
	{
		ft_dprintf(2, "env: illegal option -- %s\n", str);
		ft_dprintf(2, "usage: env [-i0] [-u name]\n");
		ft_dprintf(2, "options: -   -i  --ignore-environment\n");
		ft_dprintf(2, "         -0  --null-separator\n");
		ft_dprintf(2, "         -u  --unset\n");
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

int			fill_env(t_env *env, char *cmd)
{
	char	**tab;
	int		i;
	int		k;

	init_env(env);
	tab = ft_strsplit(cmd, ' ');
	i = 0;
	while (tab[++i] && tab[i][0] == '-')
	{
		k = opts_env(env, &tab, i);
		if (k == 2)
			break ;
		if (k == 0)
			return (0);
	}
	env->start_var = i - 1;
	(env->u) ? i++ : 0;
	while (tab[i] && ft_strchr(tab[i], '='))
		i++;
	env->start_cmd = i - 1;
	env->tab = copy_char2(tab, 1);
	free_tabstr(&tab);
	return (1);
}