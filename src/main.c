/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:14:17 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/15 19:12:59 by obelouch         ###   ########.fr       */
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

int			exec_cmd(char *cmd, char **envp)
{
	char	*full_path;
	char	**tab_path;
	char	**tab;
	int		i;

	tab = ft_strsplit(cmd, ' ');
	if ((i = cmd_user(tab, envp)))
	{
		free_tabstr(&tab);
		exit(i);
	}
	tab_path = get_paths(envp);
	i = -1;
	while(tab_path[++i])
	{
		full_path = ft_strjoin(tab_path[i], "/");
		ft_strcombin(&full_path, tab[0]);
		if (!access(full_path, F_OK))
		{
			if (!access(full_path, X_OK))
			{
				if (execve(full_path, tab, envp) != -1)
				{
					free(full_path);
					free_tabstr(&tab);
					return(0);
				}
			}
			ft_dprintf(2, "%{red}-obsh%{eoc}: ");
			ft_dprintf(2, "%{CYAN}%s%{eoc}: ", cmd);
			ft_dprintf(2, "Permission denied\n");
			free(full_path);
			free_tabstr(&tab);
			return (1);
		}
		free(full_path);
	}
	ft_dprintf(2, "%{red}-obsh%{eoc}: %{CYAN}%s%{eoc}", tab[0]);
	ft_dprintf(2, ": commande not found\n");
	free_tabstr(&tab_path);
	free_tabstr(&tab);
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

int			cmd_mybuilt(char *cmd, char *envp[], int *last)
{
	char	**tab;
	int		status;

	if (well_quoted(cmd))
		tab = ft_split_quote(cmd);
	else
		tab = ft_split_invquote(cmd);
	if (!ft_strcmp(cmd, "exit") || !ft_strncmp(cmd, "exit ", 5))
		exit(ret_exit(cmd));
	if (!ft_strcmp(cmd, "echo") || !ft_strncmp(cmd, "echo ", 5))
	{
		ft_echo(len_tab(tab), tab, envp, last);
		free_tabstr(&tab);
		return(1);
	}
	if (!ft_strcmp(cmd, "cd") || !ft_strncmp(cmd,  "cd ", 3))
	{
		ft_cd(cmd, envp, last);
		return(1);
	}
	if (!ft_strcmp(cmd, "setenv") || !ft_strncmp(cmd, "setenv ", 7))
	{
		ft_setenv(envp, cmd, last);
		return (1);
	}
	if (!ft_strcmp(cmd, "unsetenv") || !ft_strncmp(cmd, "unsetenv ", 8))
	{
		ft_unsetenv(envp, cmd, last);
		return (1);
	}
	if (!ft_strcmp(cmd, "env") || !ft_strncmp(cmd, "env ", 4))
	{
		ft_env(envp, cmd, last);
		return (1);
	}
	return (-1);
}

int			main(int ac, char **av, char **envp)
{
	t_minishell		ms;
	char			*line;
	sighandler_t	old;

	set_oldpath(&envp, "");
	ms.status = 0;
	ms.last_ret = 0;
	old = signal(SIGINT, SIG_IGN);
	while (ac)
	{
		display_prompt(envp);
		get_next_line(0, &line);
		ms.cmd = cmdsplit(line);
		free(line);
		ms.i = -1;
		while (ms.cmd[++(ms.i)])
		{
			if (cmd_mybuilt(ms.cmd[ms.i], envp, &ms.last_ret) == -1)
			{
				if ((ms.pid = create_process()) == -1)
				{
					ft_dprintf(2, "%{red}-obsh%{eoc}: ");
					ft_dprintf(2, "%{CYAN}fork%{eoc}: error\n");
					return(1);
				}
				if (ms.pid == 0)
				{
					signal(SIGINT, old);
					exec_cmd(ms.cmd[ms.i], envp);
				}
				else
				{
					waitpid(ms.pid, &(ms.status), 0);
					if (ac == 2 && !ft_strcmp(av[1], "--signals"))
						gest_signal(&ms, ac, av);
					else
						ms.last_ret = exit_val(ms.status);
				}
			}
		}
		free_tabstr(&(ms.cmd));
	}
	return (EXIT_SUCCESS);
}
