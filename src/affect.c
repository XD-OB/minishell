/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affect.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 08:56:44 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/22 10:23:32 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		var_fnd_envp(char **envp, char *str, char *tmp)
{
	char		*var;
	int			len_var;
	int			i;

	i = 0;
	var = ft_strjoin(tmp, "=");
	len_var = ft_strlen(var);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, len_var))
		{
			free(envp[i]);
			envp[i] = ft_strdup(str);
			free(var);
			return (1);
		}
		i++;
	}
	free(var);
	return(0);
}

static void		fill_var(t_minishell *ms, char **str)
{
	char		*tmp;
	int			egal;

	egal = 0;
	while ((*str)[egal] && (*str)[egal] != '=')
		egal++;
	tmp = ft_strndup(*str, egal);
	if (var_fnd_envp(ms->envp, *str, tmp))
	{
		free(tmp);
		return ;
	}
	add_2_dicstr(&ms->tab_var, tmp, &(*str)[egal + 1]);
	free(tmp);
}

int				affect_vars(t_minishell *ms)
{
	char			**tab;
	int				len;
	int				i;

	tab = ft_strsplit(ms->cmd, ' ');
	len = len_tab(tab);
	i = -1;
	while (++i < len)
	{
		ft_trimstr(&tab[i]);
		if (!ft_strchr(tab[i], '=') || tab[i][0] == '=')
			break ;
		fill_var(ms, &tab[i]);
	}
	if (i < len)
	{
		(ms->cmd_freable) ? free(ms->cmd) : (ms->cmd_freable = 1);
		ms->cmd = join_from_tab(tab, i, " ");
		free_tabstr(&tab);
		return (1);
	}
	free_tabstr(&tab);
	return (0);
}
