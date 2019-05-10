/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:14:17 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/10 00:22:18 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**get_paths(char *envp[])
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

int			cmd_mybuilt(char **tab, char *envp[], int status)
{
	if (!ft_strcmp(tab[0], "echo"))
		ft_echo(tab, envp, status);
	else if (!ft_strcmp(tab[0], "cd"))
		ft_cd(tab, envp);
	//else if (!ft_strcmp(tab[0], "env"))
	//	ft_env(tab, envp);
	//else if (!ft_strcmp(tab[0], "setenv"))
	//	ft_setenv(tab, envp);
	//else if (!ft_strcmp(tab[0], "unsetenv"))
	//	ft_unsetenv(tab, envp);
	else
		return (0);
	return (1);
}

void		exec_cmd(char *cmd, char *envp[], int status)
{
	char	*full_path;
	char	**tab_path;
	char	**tab;
	int		i;

	if (well_quoted(cmd))
		tab = ft_split_quote(cmd);
	else
		tab = ft_split_invquote(cmd);
	if (cmd_mybuilt(tab, envp, status))
		exit(0);
	if (cmd_user(tab, envp))
		exit(0);
	tab_path = get_paths(envp);
	i = -1;
	while(tab_path[++i])
	{
		full_path = ft_strjoin(tab_path[i], "/");
		ft_strcombin(&full_path, tab[0]);
		if (execve(full_path, tab, envp) != -1)
		{
			free(full_path);
			exit(0);
		}
		free(full_path);
	}
	ft_printf("%s: commande not found\n", tab[0]);
	free_tabstr(tab_path);
	exit (1);
}

int			ret_exit(char *str)
{
	char	**tab;
	int		ret;

	tab = ft_strsplit(str, ' ');
	if (tab[1])
		ret = ft_atoi(tab[1]);
	else
		ret = 0;
	free_tabstr(tab);
	return (ret);
}

int			main(int ac, char **av, char *envp[])
{
	pid_t	pid;
	char	*line;
	char	**cmd;
	int		status;
	int		i;

	(void)av;
	i = -1;
	status = 0;
	while (ac)
	{
		display_prompt(envp);
		get_next_line(0, &line);
		cmd = cmdsplit(line);
		i = -1;
		while (cmd[++i])
		{
			if (!ft_strncmp(cmd[i], "exit", 4))
				exit(ret_exit(cmd[i]));
			pid = create_process();
			if (pid == 0)
			{
				exec_cmd(cmd[i], envp, status);
				exit(0);
			}
			else
				waitpid(pid, &status, 0);
		}
		free_tabstr(cmd);
	}
	return (EXIT_SUCCESS);
}
