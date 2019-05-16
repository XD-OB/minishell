/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 00:50:12 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/16 07:34:40 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		env_cmd(t_env env, char **envp, int *last)
{
	pid_t		pid;
	int			status;
	char		*cmd;

	if (!env.tab[env.start_cmd])
		return ;
	cmd = join_from_tab(env.tab, env.start_cmd, " ");
	if (cmd_builtin(cmd, envp, last) == -1)
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

static int		env_u(char ***envp, t_env env, int i)
{
	int			j;
	int			k;

	j = -1;
	while ((*envp)[++j])
	{
		if (!ft_strncmp((*envp)[j], env.tab[i], ft_strlen(env.tab[i])))
		{
			k = j - 1;
			while ((*envp)[++k + 1])
				ft_swap_env(&((*envp)[k]), &((*envp)[k + 1]));
			(*envp)[k] = NULL;
			break ;
		}
	}
	if (!env.tab[++i])
	{
		show_env(*envp);
		free_tabstr(envp);
		return (1);
	}
	return (0);
}

static char		**modify_env(char **envp, t_env env)
{
	char		**new_envp;
	int			i;

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

int				ft_env(char **envp, char *cmd, int *last)
{
	char		**new_envp;
	t_env		env;
	int			len_t;

	if (!fill_env(&env, cmd))
	{
		*last = 1;
		return (1);
	}
	*last = 0;
	len_t = len_tab(env.tab);
	if (adv_show_env(envp, &env, len_t))
		return (0);
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
