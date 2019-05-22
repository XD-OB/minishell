/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <obelouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:14:17 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/22 10:22:23 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char			**get_tab_cmd(void)
{
	char			**tab_cmd;
	char			*line;

	get_next_line(0, &line);
	ft_trimstr(&line);
	tab_cmd = cmdsplit(line);
	free(line);
	return (tab_cmd);
}

/*
**	i:		0: i		1: j
*/

void				replace_tilda(t_minishell *ms)
{
	char		*a_cmd;
	int			len_cmd;
	int			len_home;
	int			i[2];
	int			k;

	len_cmd = ft_strlen(ms->cmd);
	len_home = ft_strlen(ms->home);
	a_cmd = ft_strnew(len_home + len_cmd - 1);
	i[0] = 0;
	k = 0;
	while (i[0] < len_cmd)
	{
		if (ms->cmd[i[0]] == '~')
		{
			i[0]++;
			i[1] = 0;
			while (i[1] < len_home)
				a_cmd[k++] = ms->home[i[1]++];
		}
		a_cmd[k++] = ms->cmd[i[0]++];
	}
	(ms->cmd_freable) ? free(ms->cmd) : (ms->cmd_freable = 1);
	ms->cmd = a_cmd;
}

char			*ft_search_value(t_minishell *ms, char *var)
{
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
	ft_putendl(str_start);
	ft_putendl(var);
	ft_putendl(str_end);
	value = ft_search_value(ms, var);
	free(*str);
	*str = ft_strjoin(str_start)
	free(str_start);
	free(str_end);
	free(value);
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
		if (ms->cmd[i] == '$' && end == -1 && start == -1  &&
			(ms->cmd[i] != '(' || !ft_strchr(&ms->cmd[i], ')')))
			start = i;
		if ((!ms->cmd[i + 1] || ms->cmd[i + 1] == '$' || ms->cmd[i + 1] == ' ') && start >= 0)
			end = i + 1;
		if (end > 0 && start >= 0)
		{
			ft_printf("found dollar int start=%d , end=%d\n", start, end);
			dollar_echange(ms, &ms->cmd, start, end);
			end = -1;
			start = -1;
		}
		i++;
	}
}

int				found_expans(t_minishell *ms)
{
	if (!ft_strcmp(ms->cmd, "cd"))
	{
		ms->cmd = ft_strdup("cd ~");
		ms->cmd_freable = 1;
	}
	if (ft_strchr(ms->cmd, '~'))
		replace_tilda(ms);
	if (ft_strchr(ms->cmd, '='))
		if (!affect_vars(ms))
			return(1);
	if (ft_strchr(ms->cmd, '$'))
		replace_dollar(ms);
	return (0);
}

int					main(int ac, char **av, char **envp)
{
	t_minishell		ms;
	int				i;

	init_minishell(&ms, envp, ac, av);
	while (ac)
	{
		(!ms.sig_int) ? display_prompt(ms.envp) : 0;
		ms.sig_int = 0;
		ms.tab_cmd = get_tab_cmd();
		i = -1;
		while (ms.tab_cmd[++i])
		{
			ms.cmd_freable = 0;
			ms.cmd = ms.tab_cmd[i];
			if (found_expans(&ms))
				continue ;
			if (wildcard(&ms))
				continue ;
			if (ft_strcmp(ms.cmd, ""))
				if (cmd_lancher(&ms))
					return (free_ms(&ms, NULL));
			(ms.cmd_freable) ? free_mscmd(&ms) : 0;
		}
		free_tabstr(&(ms.tab_cmd));
	}
	free_ms(&ms, NULL);
	return (EXIT_SUCCESS);
}
