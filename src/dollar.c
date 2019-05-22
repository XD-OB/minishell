/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 21:10:08 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/22 23:29:48 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*ft_search_value(t_minishell *ms, char *var)
{
	char		*tmp;
	int			len_var;
	int			i;

	i = -1;
	tmp = ft_strjoin(var, "=");
	len_var = ft_strlen(tmp);
	while (ms->envp[++i])
		if (!ft_strncmp(ms->envp[i], tmp, len_var))
		{
			free(tmp);
			return (ft_strdup(&ms->envp[i][len_var]));
		}
	free(tmp);
	if (ms->tab_var)
	{
		i = -1;
		while (ms->tab_var[++i].var)
			if (!ft_strcmp(ms->tab_var[i].var, var))
				return (ft_strdup(ms->tab_var[i].value));
	}
	ft_printf("%{RED}-obsh%{eoc}: %s: Undefined variable\n", var);
	return (ft_strnew(0));
}

static void		dollar_echange(t_minishell *ms, char **str, int start, int end)
{
	char		*str_start;
	char		*str_end;
	char		*var;
	char		*value;

	str_start = ft_strndup(*str, start);
	var = ft_strsub(*str, start + 1, end - start - 1);
	str_end = ft_strdup(&(*str)[end]);
	value = ft_search_value(ms, var);
	(ms->cmd_freable) ? free(*str) : (ms->cmd_freable = 1);
	*str = ft_strjoin(str_start, value);
	ft_strcombin(str, str_end);
	free(str_start);
	free(str_end);
	free(var);
}

void			replace_dollar(t_minishell *ms)
{
	int			start;
	int			end;
	int			i;

	i = 0;
	end = -1;
	start = -1;
	while (ms->cmd[i])
	{
		if ((i == 0 || (ms->cmd[i - 1] != '"' && ms->cmd[i - 1] != '\'')) &&
				ms->cmd[i] == '$' && end == -1 && start == -1  &&
				(ms->cmd[i] != '(' || !ft_strchr(&ms->cmd[i], ')')))
			start = i;
		if ((!ms->cmd[i + 1] || ms->cmd[i + 1] == '$' || ms->cmd[i + 1] == ' ')
				&& start >= 0)
			end = i + 1;
		if (end > 0 && start >= 0)
		{
			dollar_echange(ms, &ms->cmd, start, end);
			end = -1;
			start = -1;
			i = -1;
		}
		i++;
	}
}
