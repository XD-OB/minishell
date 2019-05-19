/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:14:17 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/18 23:45:45 by obelouch         ###   ########.fr       */
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
		if (!ms.sig_int)
			display_prompt(ms.envp);
		ms.sig_int = 0;
		ms.tab_cmd = get_tab_cmd();
		i = -1;
		while (ms.tab_cmd[++i])
		{
			ms.cmd = ms.tab_cmd[i];
			if (cmd_lancher(&ms))
			{
				free_ms(&ms, NULL);
				return (1);
			}
		}
		free_tabstr(&(ms.tab_cmd));
		ft_printf("----------last-ret [%d]---------\n", ms.last);
	}
	free_ms(&ms, NULL);
	return (EXIT_SUCCESS);
}
