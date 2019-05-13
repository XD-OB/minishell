#include "minishell.h"

char		**copy_char2(char **tab, int start)
{
	char	**new;
	int		len_t;
	int		i;

	len_t = len_tab(tab);
	if (!(new = (char**)malloc(sizeof(char*) * (len_t + 1))))
		return NULL;
	new[len_t] = NULL;
	i = start;
	while (tab[i])
	{
		new[i] = ft_strdup(tab[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

static void	init_env(t_env *env)
{
	env->i = 0;
	env->u = 0;
	env->null = 0;
	env->tab = NULL;
}

static void	fill_env(t_env *env, char *cmd)
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
			(tab[i][j] == 'i') ? env->i = 1 : 0;
			(tab[i][j] == 'u') ? env->u = 1 : 0;
			(tab[i][j] == '0') ? env->null = 1 : 0;
		}
		(j == 1) ? env->i = 1 : 0;
	}
	env->start_var = i;
	while (tab[i] && ft_strchr(tab[i], '='))
		i++;
	env->start_cmd = i;
	env->tab = copy_char2(tab, env->start_var);
	free_tabstr(&tab);
}

int			adv_show_env(char **envp, t_env *env, int len_t)
{
	int		i;

	if (len_t == 1)
	{
		show_env(envp);
		return (1);
	}
	if (len_t == 2 && env->null && !env->i && !env->u)
	{
		i = 0;
		while (envp[i])
			ft_putstr(envp[i++]);
		ft_putchar('\n');
		return (1);
	}
	return (0);
}

void		env_cmd(char **envp, t_env env)
{
	char	*cmd;
	pid_t	pid;
	int		i;

	cmd = ft_strnew(0);
	//i = env.start_var;
	//if (i != -1)
	//{
	//	ft_putstr("remember\n");
		//while (i < env.start_cmd)
		//	set_env_cmd(envp, env.tab[i++]);
	//}
	//else
	i = 0;
	while (env.tab[i])
	{
		ft_strcombin(&cmd, env.tab[i]);
		ft_strcombin(&cmd, " ");
		i++;
	}
	ft_putendl(cmd);
	/*pid = create_process();
	if (pid == 0)
	{
		ft_putendl(cmd);
		if (!cmd_mybuilt(cmd, envp))
			exec_cmd(cmd, envp, 0);
	}
	else
		waitpid(pid, NULL, pid);*/
	//free(cmd);
}


int		ft_env(char **envp, char *cmd)
{
	char	**new_envp;
	t_env	env;
	int		len_t;
	int		i;

	fill_env(&env, cmd);
	len_t = len_tab(env.tab);
	if (adv_show_env(envp, &env, len_t))
		return(0);
	//affect_envar(&env);
	if (!env.i)
	{
		new_envp = copy_char2(envp, 0);
		if (env.u)
			ft_unsetenv(new_envp, env.tab[0]);
		free_tabstr(&new_envp);
	}
	//env_cmd(new_envp, env);
	//free_tabstr(&(env.tab));
	return (0);
}
