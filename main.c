#include "minishell.h"

char	**get_paths(char *envp[])
{
	char	**tab_path;
	char	*path;
	int	i;

	i = -1;
	while (envp[++i])
		if (!ft_strncmp(envp[i], "PATH=", 5))
			path = ft_strdup(&(envp[i][5]));
	tab_path = ft_strsplit(path, ':');
	free(path);
	return (tab_path);
}

int	cmd_mybuilt(char ***tab, char *envp[])
{
	if (!ft_strcmp((*tab)[0], "echo"))
		ft_echo(tab, envp);
	else if (!ft_strcmp((*tab)[0], "cd"))
		ft_cd(tab, envp);
	//else if (!ft_strcmp((*tab)[0], "env"))
	//	ft_env(tab, envp);
	else if (!ft_strcmp((*tab)[0], "exit"))
		ft_exit(tab, envp);
	//else if (!ft_strcmp((*tab)[0], "setenv"))
	//	ft_setenv(tab, envp);
	//else if (!ft_strcmp((*tab)[0], "unsetenv"))
	//	ft_unsetenv(tab, envp);
	else
	{
		free_tabstr(*tab);
		return (0);
	}
	free_tabstr(*tab);
	return (1);
}

void	exec_cmd(char *cmd, char *envp[])
{
	char		*full_path;
	char		**tab_path;
	char		**tab;
	int		i;

	tab = ft_strsplit(cmd, ' ');
	if (cmd_user(&tab, envp) ||
		cmd_mybuilt(&tab, envp))
		return ;
	tab_path = get_paths(envp);
	i = -1;
	while(tab_path[++i])
	{
		full_path = ft_strjoin(tab_path[i], "/");
		ft_strcombin(&full_path, tab[0]);
		if (execve(full_path, tab, envp) != -1)
		{
			free(full_path);
			return ;
		}
		free(full_path);
	}
	ft_printf("%s: commande not found\n", tab[0]);
	free_tabstr(tab_path);
	free_tabstr(tab);
}

int	main(int ac, char **av, char *envp[])
{
	pid_t	pid;
	char	*line;
	char	**cmd;
	int	i;

	while (1)
	{
		display_prompt(envp);
		get_next_line(0, &line);
		cmd = cmdsplit(line);
		i = -1;
		while (cmd[++i])
		{
			pid = create_process();
			(pid == 0) ? exec_cmd(cmd[i], envp) : wait(NULL);
		}
		free_tabstr(cmd);
	}
	return (EXIT_SUCCESS);
}
