/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <obelouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:14:17 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/20 08:31:59 by obelouch         ###   ########.fr       */
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
