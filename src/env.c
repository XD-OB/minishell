/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 00:50:12 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/15 02:31:27 by obelouch         ###   ########.fr       */
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
		ft_dprintf(2, "env: illegal option -- %c\n", c);
		ft_dprintf(2, "usage: env [-i0] [-u name]");
		ft_dprintf(2, "[name=value ...] [utility [argument ...]]\n");
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

char		**modify_env(char **envp, t_env env)
{
	char	**new_envp;
	char	*tmp;
	int		i;
	int		j;

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
	{
		j = -1;
		while (new_envp[++j])
		{
			if (!ft_strncmp(new_envp[j], env.tab[i], ft_strlen(env.tab[i])))
			{
				tmp = new_envp[j];
				new_envp[j] = ft_strjoin(env.tab[i], "=");
				free(tmp);
				break;
			}
		}
		i++;
		if (!env.tab[i])
		{
			show_env(new_envp);
			free_tabstr(envp);
			return (NULL);
		}
	}
	while (env.tab[i] && i < env.start_cmd)
	{
		if (!ft_strchr(env.tab[i], '='))
		{
			ft_dprintf(2, "env: illegal affectaion!\n");
			ft_dprintf(2, "usage: env [-i0] [-u name]");
			ft_dprintf(2, "[name=value ...] [utility [argument ...]]\n");
			free_tabstr(&new_envp);
			return (NULL);
		}
		add_2_tab(&new_envp, env.tab[i++]);
	}
	j = -1;
	while (new_envp[++j])
		ft_printf("%s\n", new_envp[j]);
	ft_putstr("\n");
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
