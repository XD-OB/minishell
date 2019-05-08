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

void	display_prompt(void)
{
	ft_printf("%{cyan}obelouch%{eoc}");
	ft_printf("%{GREEN}$%{eoc} ");
}

int	exec_cmd(char *cmd, char *envp[])
{
	char	**tab;

	tab = ft_strsplit(cmd, ' ');
	ft_printf("\ncommande: %s|size: %d\n", cmd, ft_strlen(cmd));
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
		display_prompt();
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
