/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usages.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <obelouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 07:31:50 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/19 08:23:17 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		msg_type(mode_t mode, char *cmd)
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

int		msg_usrerr(char *cmd, int n)
{
	ft_dprintf(2, "%{red}-obsh%{eoc}: ");
	ft_dprintf(2, "%{CYAN}%s%{eoc}: ", cmd);
	if (n == 0)
		ft_dprintf(2, "Unknown error\n");
	else if (n == 1)
		ft_dprintf(2, "Permission denied\n");
	return (1);
}

void	usage_env(char *str)
{
	if (str)
		ft_dprintf(2, "%s\n", str);
	ft_dprintf(2, "usage: env [-i0] [-u name]\n");
	ft_dprintf(2, "options: -   -i  --ignore-environment\n");
	ft_dprintf(2, "         -0  --null-separator\n");
	ft_dprintf(2, "         -u  --unset\n");
}

int		fork_error(void)
{
	ft_dprintf(2, "%{red}-obsh%{eoc}: %{CYAN}fork%{eoc}: ");
	ft_dprintf(2, "Can't create a processus");
	return (1);
}

void	msg_cmd_nfound(char *str)
{
	ft_dprintf(2, "%{red}-obsh%{eoc}: ");
	ft_dprintf(2, "%{CYAN}%s%{eoc}", str);
	ft_dprintf(2, ": command not found\n");
}
