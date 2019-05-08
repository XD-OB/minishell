#include "minishell.h"

void	free_tabstr(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

pid_t	create_process(void)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid != -1)
		return (child_pid);
	write(2, "fork: Error\n", 12);
	exit(EXIT_FAILURE);
}

void	display_prompt(char *envp[])
{
	char	curr_dir[500];
	char	*user;
	int	i;

	i = -1;
	user = NULL;
	while (envp[++i])
		if (!ft_strncmp(envp[i], "USER=", 5))
			user = ft_strdup(&(envp[i][5]));
	if (!user)
		user = ft_strdup("user");
	getcwd(curr_dir, 500);
	ft_printf("%{GREEN}%s%{eoc}", user);
	ft_printf("%{RED}:%{cyan} %s%{eoc}$ ", curr_dir);
	free(user);
}

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

void	exec_cmd(char *cmd, char *envp[])
{
	int		i;
	char		**tab;
	char		**tab_path;
	char		*full_path;
	struct stat	status;

	tab = ft_strsplit(cmd, ' ');
	//if (ft_strchr(tab[0], '/'))
	//	return (cmd_user(cmd, envp));
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
			if (pid == 0)
				exec_cmd(cmd[i], envp);
			else
				wait(NULL);
		}
		free_tabstr(cmd);
	}
	return (EXIT_SUCCESS);
}
