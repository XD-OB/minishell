/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 00:50:12 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/15 03:28:58 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	fill_env(t_env *env, char *cmd)
{
	char	**tab;
	int		i;
	int		j;

	init_env(env);
	tab = ft_strsplit(cmd, ' ');
	i = 0;
	while (tab[++i] && tab[i][0] == '-')
	{
		j = 0;
		while (tab[i][++j])
		{
			if (tab[i][j] == '-')
			{
				if (fill_longopts(env, &tab[i][++j]))
				{
					free_tabstr(&tab);
					return (0);
				}
				break;
			}
			else
			{
				if (fill_opts(env, tab[i][j]))
				{
					free_tabstr(&tab);
					return (0);
				}
			}
		}
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

int			adv_show_env(char **envp, t_env *env, int len_t)
{
	int		i;

	if (len_t == 0)
	{
		show_env(envp);
		return (1);
	}
	if (len_t == 1 && env->null && !env->i && !env->u)
	{
		i = 0;
		while (envp[i])
			ft_putstr(envp[i++]);
		ft_putchar('\n');
		return (1);
	}
	if (len_t == 1 && env->i)
		return (1);
	return (0);
}

void		env_cmd(t_env env, char **envp, int *last)
{
	pid_t	pid;
	int		status;
	char	*cmd;

	if (!env.tab[env.start_cmd])
		return ;
	cmd = join_from_tab(env.tab, env.start_cmd, " ");
	if (cmd_mybuilt(cmd, envp, last) == -1)
	{
		pid = create_process();
		if (pid == 0)
		{
			exec_cmd(cmd, envp);
			exit(0);
		}
		else
		{
			waitpid(pid, &status, 0);
			*last = exit_val(status);
		}
	}
	free(cmd);
}

static int	env_u(char ***envp, t_env env, int i)
{
	int		j;
	int		k;

	j = -1;
	while ((*envp)[++j])
	{
		if (!ft_strncmp((*envp)[j], env.tab[i], ft_strlen(env.tab[i])))
		{
			k = j - 1;
			while ((*envp)[++k + 1])
				ft_swap_env(&((*envp)[k]), &((*envp)[k + 1]));
			(*envp)[k] = NULL;
			break;
		}
	}
	i++;
	if (!env.tab[i])
	{
		show_env(*envp);
		free_tabstr(envp);
		return (1);
	}
	return (0);
}

char		**modify_env(char **envp, t_env env)
{
	char	**new_envp;
	char	*tmp;
	int		i;
	int		j;
	int		k;

	if (env.i)
	{
		new_envp = (char**)malloc(sizeof(char*));
		*new_envp = NULL;
		return (new_envp);
	}
	new_envp = (char**)malloc(sizeof(char*) * (len_tab(envp) + 1));
	new_envp[len_tab(envp)] = NULL;
	i = -1;
	while (envp[++i])
		new_envp[i] = ft_strdup(envp[i]);
	i = env.start_var;
	if (env.u && env.tab[i])
		if (env_u(&new_envp, env, i++))
			return (NULL);
	while (env.tab[i] && i < env.start_cmd)
		add_2_tab(&new_envp, env.tab[i++]);
	return (new_envp);
}

int		ft_env(char **envp, char *cmd, int *last)
{
	char	**new_envp;
	t_env	env;
	int		len_t;
	int		i;

	if (!fill_env(&env, cmd))
	{
		*last = 1;
		return (1);
	}
	*last = 0;
	len_t = len_tab(env.tab);
	if (adv_show_env(envp, &env, len_t))
		return(0);
	new_envp = modify_env(envp, env);
	if (!new_envp)
	{
		free_tabstr(&(env.tab));
		return (1);
	}
	env_cmd(env, new_envp, last);
	free_tabstr(&(env.tab));
	free_tabstr(&new_envp);
	return (0);
}
