/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <obelouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:14:17 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/19 09:55:45 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char			**get_tab_cmd(void)
{
	char			**tab_cmd;
	char			*line;

	get_next_line(0, &line);
	ft_epurstr(&line);
	tab_cmd = cmdsplit(line);
	free(line);
	return (tab_cmd);
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
			ms.cmd = ms.tab_cmd[i];
			if (!ft_strcmp(ms.cmd, ""))
				continue ;
			if (cmd_lancher(&ms))
			{
				free_ms(&ms, NULL);
				return (1);
			}
		}
		free_tabstr(&(ms.tab_cmd));
	}
	free_ms(&ms, NULL);
	return (EXIT_SUCCESS);
}
