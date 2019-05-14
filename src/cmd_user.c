/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_user.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 16:19:43 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/14 22:21:00 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		msg_type(mode_t mode, char *cmd)
{
	ft_dprintf(2, "%{red}-obsh%{eoc}: ");
	ft_dprintf(2, "%{CYAN}%s%{eoc}: ", cmd);
	if (S_ISDIR(mode))
		ft_dprintf(2, "is a Directory\n");
	else if (S_ISCHR(mode))
		ft_dprintf(2, "is a Device in character mode\n");
	else if (S_ISBLK(mode))
		ft_dprintf(2, "is a Device in block mode\n");
	else if (S_ISFIFO(mode))
		ft_dprintf(2, "is a Pipe\n");
	else if (S_ISSOCK(mode))
		ft_dprintf(2, "is a Socket\n");
	else
		ft_dprintf(2, "Unknown\n");
	return(1);	
}

static int		msg_usrerr(char *cmd, int n)
{
	ft_dprintf(2, "%{red}-obsh%{eoc}: ");
	ft_dprintf(2, "%{CYAN}%s%{eoc}: ", cmd);
	if (n == 0)
		ft_dprintf(2, "file not found\n");
	else if (n == 1)	
		ft_dprintf(2, "Unknown error\n");
	else if (n == 2)	
		ft_dprintf(2, "Permission denied\n");
	return (1);
}

int				cmd_user(char **tab, char *envp[])
{
	struct stat		stats;
	int				status;
	pid_t			pid;

	if (ft_strchr(tab[0], '/'))
	{
		if (access(tab[0], F_OK))
			return (msg_usrerr(tab[0], 0));
		if (stat(tab[0], &stats) == -1)
			return (msg_usrerr(tab[0], 1));
		if (!S_ISREG(stats.st_mode))
			return (msg_type(stats.st_mode, tab[0]));
		if (access(tab[0], X_OK))
			return (msg_usrerr(tab[0], 2));
		if ((pid = create_process()) == -1)
		{
			ft_dprintf(2, "fork: error\n");
			return(-1);
		}
		if (pid == 0)
		{
			if (execve(tab[0], tab, envp) == -1)
				ft_printf("%s: Execution error\n", tab[0]);
		}
		else;
		{
			waitpid(pid, &status, 0);
			return(exit_val(status));
		}
		return (1);
	}
	return(0);
}
