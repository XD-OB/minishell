/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_user.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 16:19:43 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/11 16:59:59 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			msg_type(mode_t mode, char *cmd)
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
}

static void			msg_usrerr(char *cmd, int n)
{
	ft_dprintf(2, "%{red}-obsh%{eoc}: ");
	ft_dprintf(2, "%{CYAN}%s%{eoc}: ", cmd);
	if (n == 0)
		ft_dprintf(2, "file not found\n");
	else if (n == 1)	
		ft_dprintf(2, "Unknown error\n");
	else if (n == 2)	
		ft_dprintf(2, "Permission denied\n");
}

int					cmd_user(char **tab, char *envp[])
{
	struct stat		status;
	int				ret;

	if (ft_strchr(tab[0], '/'))
	{
		if (access(tab[0], F_OK))
			msg_usrerr(tab[0], 0);
		else if (stat(tab[0], &status) == -1)
			msg_usrerr(tab[0], 1);
		else if (!S_ISREG(status.st_mode))
			msg_type(status.st_mode, tab[0]);
		else if (access(tab[0], X_OK))
			msg_usrerr(tab[0], 2);
		else
		{
			if (execve(tab[0], tab, envp) != -1)
				return (0);
			ft_printf("%s: Execution error\n", tab[0]);
		}
		return (1);
	}
	return (0);
}
