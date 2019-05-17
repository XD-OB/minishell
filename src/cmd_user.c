/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_user.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 16:19:43 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/17 01:52:43 by obelouch         ###   ########.fr       */
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
	return (1);
}

static int		msg_usrerr(char *cmd, int n)
{
	ft_dprintf(2, "%{red}-obsh%{eoc}: ");
	ft_dprintf(2, "%{CYAN}%s%{eoc}: ", cmd);
	if (n == 0)
		ft_dprintf(2, "Unknown error\n");
	else if (n == 1)
		ft_dprintf(2, "Permission denied\n");
	return (1);
}

int				check_fx(char *str)
{
	struct stat		stats;

	if (stat(str, &stats) == -1)
		return (msg_usrerr(str, 0));
	if (!S_ISREG(stats.st_mode))
		return (msg_type(stats.st_mode, str));
	if (access(str, X_OK))
		return (msg_usrerr(str, 1));
	return (0);
}

int				cmd_user(char ***tab, char **envp, char **full_path)
{
	char		*cmd;

	cmd = (full_path) ? *full_path : (*tab)[0];
	if (check_fx(cmd))
		return (1);
	if (execve(cmd, *tab, envp) == -1)
	{
		ft_printf("%s: Execution error\n", cmd);
		free_tabstr(tab);
		return (1);
	}
	if (full_path)
		free(*full_path);
	free_tabstr(tab);
	return (0);
}
