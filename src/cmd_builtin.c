/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_buitin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 07:33:09 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/16 07:40:39 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			ret_exit(char *str)
{
	char			**tab;
	int				ret;

	tab = ft_strsplit(str, ' ');
	if (tab[1])
		ret = ft_atoi(tab[1]);
	else
		ret = 0;
	free_tabstr(&tab);
	return (ret);
}

int					cmd_builtin(char *cmd, char *envp[], int *last)
{
	char			**tab;

	tab = (well_quoted(cmd)) ? ft_split_quote(cmd) : ft_split_invquote(cmd);
	if (!ft_strcmp(cmd, "exit") || !ft_strncmp(cmd, "exit ", 5))
		exit(ret_exit(cmd));
	if (!ft_strcmp(cmd, "echo") || !ft_strncmp(cmd, "echo ", 5))
	{
		ft_echo(len_tab(tab), tab, envp, last);
		free_tabstr(&tab);
	}
	else if (!ft_strcmp(cmd, "cd") || !ft_strncmp(cmd, "cd ", 3))
		ft_cd(cmd, envp, last);
	else if (!ft_strcmp(cmd, "setenv") || !ft_strncmp(cmd, "setenv ", 7))
		ft_setenv(envp, cmd, last);
	else if (!ft_strcmp(cmd, "unsetenv") || !ft_strncmp(cmd, "unsetenv ", 8))
		ft_unsetenv(envp, cmd, last);
	else if (!ft_strcmp(cmd, "env") || !ft_strncmp(cmd, "env ", 4))
		ft_env(envp, cmd, last);
	else
		return (-1);
	return (1);
}
