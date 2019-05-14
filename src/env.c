/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 00:50:12 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/14 02:58:38 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**copy_char2(char **tab, int start)
{
	char	**new;
	int		len_t;
	int		len;
	int		i;
	int		j;

	len_t = len_tab(tab);
	len = len_t - start;
	if (!(new = (char**)malloc(sizeof(char*) * (len + 1))))
		return NULL;
	new[len] = NULL;
	j = 0;
	i = start;
	while (i < len_t)
		new[j++] = ft_strdup(tab[i++]);
	return (new);
}

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
			if (fill_opts(env, tab[i][j]))
			{
				free_tabstr(&tab);
				return (0);
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

void		unset_var(char ***envp, char *var)
{
	char	**new_envp;
	int		len_var;
	int		len;
	int		i;
	int		j;

	ft_strcombin(&var, "=");
	len_var = ft_strlen(var);
	len = len_tab(*envp);
	if(!(new_envp = (char**)malloc(sizeof(char*) * (len + 1))))
		return ;
	new_envp[len] = NULL;
	i = 0;
	j = 0;
	while (i < len)
	{
		if (ft_strncmp((*envp)[i], var, len_var))
			new_envp[j++] = ft_strdup((*envp)[i]);
		i++;
	}
	free_tabstr(envp);
	*envp = new_envp;
}

void		env_cmd(t_env env, char **envp)
{
	int		status;
		int		ret;
	pid_t	pid;

	pid = create_process();
	if (pid == 0)
	{
		if (env.tab[env.start_cmd])
			exec_cmd(env.tab[env.start_cmd], envp, status);
		exit(0);
	}
	else
	{
		ret = waitpid(pid, &status, 0);
		ft_printf("ret= %d\n", ret);
	}
}


void	ft_print_env(t_env env)
{
	int		i;

	ft_printf("i   : %d\n", env.i);
	ft_printf("u   : %d\n", env.u);
	ft_printf("null: %d\n", env.null);
	ft_printf("start_var= %d\n", env.start_var);
	ft_printf("start_cmd= %d\n", env.start_cmd);
	ft_printf("-------------------\n");
	i = -1;
	while (env.tab[++i])
		ft_putendl(env.tab[i]);
	ft_putstr("-------------------\n");
}

void		add_2_tab(char ***tab, char *elem)
{
	char	**new;
	int		len;
	int		i;

	len = len_tab(*tab);
	if (!(new = (char**)malloc(sizeof(char*) * (len + 2))))
		return ;
	new[len + 1] = NULL;
	i = -1;
	while (++i < len)
		new[i] = ft_strdup((*tab)[i]);
	new[len] = ft_strdup(elem);
	free_tabstr(tab);
	*tab = new;
}

char		**modify_env(char **envp, t_env env)
{
	char	**new_envp;
	int		i;

	if (env.i)
	{
		new_envp = (char**)malloc(sizeof(char*));
		*new_envp = NULL;
		return (new_envp);
	}
	new_envp = copy_char2(envp, 0);
	i = env.start_var;
	if (env.u)
		unset_var(&new_envp, env.tab[i++]);
	while (env.tab[i] && i < env.start_cmd)
		add_2_tab(&new_envp, env.tab[i++]);
	return (new_envp);
}

int		ft_env(char **envp, char *cmd)
{
	char	**new_envp;
	t_env	env;
	int		len_t;
	int		i;

	if (!fill_env(&env, cmd))
		return (1);
	len_t = len_tab(env.tab);
	if (adv_show_env(envp, &env, len_t))
		return(0);
	new_envp = modify_env(envp, env);
	env_cmd(env, new_envp);
	free_tabstr(&new_envp);
	return (0);
}
