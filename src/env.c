/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 00:50:12 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/17 20:28:50 by obelouch         ###   ########.fr       */
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
	if (cmd_builtin(&envp, cmd, last) == -1)
	{
		pid = create_process();
		if (pid == 0)
		{
			exec_cmd(cmd, envp);
			exit(1);
		}
		else
		{
			waitpid(pid, &status, 0);
			*last = exit_val(status);
		}
	}
	free(cmd);
}

static char		**env_u(char **envp, t_env env, int *k)
{
	char		**new_envp;
	int			i;
	int			j;

	if (env.tab[*k])
	{
		new_envp = (char**)malloc(sizeof(char*) * (len_tab(envp)));
		new_envp[len_tab(envp) - 1] = NULL;
		i = 0;
		j = 0;
		while (envp[i])
		{
			if (ft_strncmp(envp[i], env.tab[*k], ft_strlen(env.tab[*k])))
				new_envp[j++] = ft_strdup(envp[i]);
			i++;
		}
		(*k)++;
		return (new_envp);
	}
	ft_dprintf(2, "env: argument for unset not found\n");
	usage_env();
	return (NULL);
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
		if (!(new_envp = env_u(envp, env, &k)))
			return (NULL);
	}
	else
		new_envp = copy_2_char(envp);
	while (env.tab[k] && k < env.start_cmd)
		add_2_tab(&new_envp, env.tab[k++]);
	return (new_envp);
}

int				ft_env(char **envp, char *cmd, int *last)
{
	char		**new_envp;
	t_env		env;
	int			len_t;

	if (!fill_env(&env, cmd))
		return ((*last = 1));
	*last = 0;
	len_t = len_tab(env.tab);
	if (adv_show_env(envp, &env, len_t))
	{
		free_tabstr(&(env.tab));
		return ((*last = 0));
	}
	new_envp = modify_env(envp, env);
	if (!new_envp)
	{
		free_tabstr(&(env.tab));
		return ((*last = 1));
	}
	env_cmd(env, new_envp, last);
	free_tabstr(&(env.tab));
	free_tabstr(&new_envp);
	return ((*last = 0));
}
