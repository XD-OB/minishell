/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 21:24:15 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/18 07:25:22 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			fndspace(char *str)
{
	int				i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

static int			fnd2parth(char *str)
{
	int				open;
	int				close;
	int				i;

	i = 0;
	open = 0;
	close = 0;
	if (str[1] == 40 && str[ft_strlen(str) - 1] == 41)
		return (1);
	else
		return (0);
}

static char			*ft_clean_parthes(char *cmd)
{
	char			*new;
	int				i;
	int				j;

	if (cmd[1] != '(')
		return (ft_strdup(&cmd[1]));
	j = 0;
	i = 2;
	new = (char*)malloc(sizeof(char) * (ft_strlen(cmd) - 2));
	while (cmd[i] && cmd[i] != ')')
		new[j++] = cmd[i++];
	new[j] = '\0';
	return (new);
}

int					ft_dollarenv(t_minishell *ms)
{
	char			*cl_cmd;
	char			*var;
	int				i;

	if (!ms->cmd[1] || (ms->cmd[1] == '(' && !fnd2parth(ms->cmd)) ||
		ms->cmd[1] == ')' || (fndspace(ms->cmd) && !fnd2parth(ms->cmd)))
	{
		ft_dprintf(2, "usage: $var or $(var)\n");
		return (1);
	}
	i = -1;
	cl_cmd = ft_clean_parthes(ms->cmd);
	var = ft_strjoin(cl_cmd, "=");
	while (ms->envp[++i])
		if (!ft_strncmp(ms->envp[i], var, ft_strlen(var)))
		{
			ft_putendl(&(ms->envp)[i][ft_strlen(var)]);
			free(var);
			free(cl_cmd);
			return (0);
		}
	ft_dprintf(2, "%{red}%s: not found%{eoc}\n", cl_cmd);
	free(var);
	free(cl_cmd);
	return (1);
}
