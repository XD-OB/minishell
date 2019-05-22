/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <obelouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 00:50:12 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/22 22:52:11 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		env_cmd(t_minishell *ms, t_env env)
{
	ms->cmd = join_from_tab(env.tab, env.start_cmd, " ");
	if (!env.tab[env.start_cmd])
		return (0);
	if (builtin_parent(ms))
		return (0);
	if ((ms->pid = create_process()) == -1)
		return (fork_error());
	if (ms->pid == 0)
	{
		if (builtin_child(ms))
			exit(ms->last);
		else
			exit(exec_cmd(ms));
	}
	else
	{
		waitpid(ms->pid, &ms->status, 0);
		return (exit_val(ms->status));
	}
}

static char		**env_u(char **envp, char *var)
{
	char		**new_envp;
	int			i;
	int			j;

	new_envp = (char**)malloc(sizeof(char*) * (len_tab(envp)));
	new_envp[len_tab(envp) - 1] = NULL;
	i = 0;
	j = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)))
			new_envp[j++] = ft_strdup(envp[i]);
		i++;
	}
	return (new_envp);
}

static char		**modify_env(char **envp, t_env env)
{
	char		**new_envp;
	int			k;

	if (env.i)
	{
		new_envp = (char**)malloc(sizeof(char*));
		*new_envp = NULL;
		return (new_envp);
	}
	k = env.start_var;
	if (env.u)
	{
		if (env.start_var >= len_tab(env.tab))
		{
			usage_env("env: argument for unset not found");
			new_envp = NULL;
			return (new_envp);
		}
		new_envp = env_u(envp, env.tab[k++]);
	}
	else
		new_envp = copy_2_char(envp);
	while (env.tab[k] && k < env.start_cmd)
		add_2_tab(&new_envp, env.tab[k++]);
	return (new_envp);
}

static int		free_envtab_ret(char ***tab, int ret)
{
	free_tabstr(tab);
	return (ret);
}

int				ft_env(t_minishell *ms)
{
	t_minishell		new_ms;
	t_env			env;
	int				len_t;

	if (!fill_env(&env, ms->cmd))
		return (1);
	fill_new_ms(&new_ms, *ms);
	len_t = len_tab(env.tab);
	if (adv_show_env(ms->envp, &env, len_t))
		return (free_envtab_ret(&(env.tab), 0));
	new_ms.envp = modify_env(ms->envp, env);
	if (!new_ms.envp)
		return (free_envtab_ret(&(env.tab), 1));
	new_ms.last = env_cmd(&new_ms, env);
	free_tabstr(&(env.tab));
	free_ms(&new_ms, ms->cmd);
	return (new_ms.last);
}
