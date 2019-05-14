/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:14:17 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/14 02:08:05 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**get_paths(char **envp)
{
	char	**tab_path;
	char	*path;
	int	i;

	i = -1;
	path = ft_strnew(0);
	while (envp[++i])
		if (!ft_strncmp(envp[i], "PATH=", 5))
			ft_strcombin(&path, &(envp[i][5]));
	if (!path)
		path = ft_strdup(".");
	tab_path = ft_strsplit(path, ':');
	free(path);
	return (tab_path);
}


int			exec_cmd(char *cmd, char **envp, int status)
{
	char	*full_path;
	char	**tab_path;
	char	**tab;
	int		i;

	if (well_quoted(cmd))
		tab = ft_split_quote(cmd);
	else
		tab = ft_split_invquote(cmd);
	if (!ft_strncmp(cmd, "echo", 4))
	{
		ft_echo(len_tab(tab), tab, envp, status);
		exit(0);
	}
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
			return(0);
		}
		free(full_path);
	}
	ft_printf("obsh: commande not found: %s\n", tab[0]);
	free_tabstr(&tab_path);
	exit(1);
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
	free_tabstr(&tab);
	return (ret);
}

int			cmd_mybuilt(char *cmd, char *envp[])
{
	if (!ft_strncmp(cmd, "exit", 5))
		kill(0, SIGINT);
	if (!ft_strncmp(cmd, "cd", 2))
	{
		ft_cd(cmd, envp);
		return(1);
	}
	if (!ft_strncmp(cmd, "setenv", 6))
	{
		ft_setenv(envp, cmd);
		return (1);
	}
	if (!ft_strncmp(cmd, "unsetenv", 8))
	{
		ft_unsetenv(envp, cmd);
		return (1);
	}
	if (!ft_strncmp(cmd, "env", 3))
	{
		ft_env(envp, cmd);
		return (1);
	}
	return (-1);
}

void		gest_signal(int status)
{
	//ft_putstr("ana hna\n");
//	if (WIFEXITED(status))
//		ft_putstr("Terminated normally\n");
	/*else*/ if (WIFSIGNALED(status))
		ft_putstr("a Signal end the Processus\n");
}

int			main(int ac, char **av, char **envp)
{
	pid_t	pid;
	char	*line;
	char	**cmd;
	int		status;
	int		i;
	int		j;
		int		ret;

	(void)av;
	i = -1;
	status = 0;
	set_oldpath(&envp, "");
	while (ac)
	{
		display_prompt(envp);
		get_next_line(0, &line);
		cmd = cmdsplit(line);
		free(line);
		i = -1;
		while (cmd[++i])
		{
			if (cmd_mybuilt(cmd[i], envp) == -1)
			{
				if ((pid = create_process()) == -1)
				{
					ft_dprintf(2, "%{red}-obsh%{eoc}: ");
					ft_dprintf(2, "%{CYAN}fork%{eoc}: error\n");
					return(1);
				}
				if (pid == 0)
					exec_cmd(cmd[i], envp, status);
				else
				{
					ret = waitpid(pid, &status, 0);
						ft_printf("ret= %d\n", ret);
					gest_signal(status);
				}
			}
		}
		free_tabstr(&cmd);
	}
	return (EXIT_SUCCESS);
}
